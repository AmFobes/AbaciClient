#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QTcpSocket>
#include <bitset>
#include <QThread>

struct ConnectionArgs {
	QString hostname;
	short port;
	QString username;
	QString password;
};

class AbaciClient : public QObject {
	Q_OBJECT

	enum class ServerPacketType {
		SHUTTINGDOWN = 0XF0,
		AUTHRESP = 0XF1,
		AVAILABLEREQUEST = 0XF2,
		RESETPASSWORD = 0XF3,
		CLIENTID = 0XF4,
		CLIENTUSERNAME = 0XF5,
		CLIENTWORKCOMPLETED = 0XF6,
		CLIENTCPUINFO = 0XF7,
		CLIENTCPUCOUNT = 0XF8,
		CLIENTPLATFORM = 0XF9,
		DATABASELESS = 0XFA,
		NOTAUTHED = 0XFB,
		// UNDEFINED = 0XFC,
		// UNDEFINED = 0XFD,
		SERVERONLINE = 0XFE,
		HEARTBEAT = 0XFF

	};
	enum ClientPacketType {
		DISCONNECTING = 0X00,
		AUTHREQ = 0X01,
		WORKREQ = 0X02,
		RESETPASSWORD = 0X03,
		REQCLIENTDETAILS = 0X04,
		SETCLIENTUSERNAME = 0X05,
		SETCLIENTCPU = 0X06,
		SETCLIENTPLATFOM = 0X07,
		REQRESULT = 0X08,
		CLIENTDELETEME = 0X09,
		REQCLIENTCOUNT = 0X0A,
		CLIENTWORKCOMPLETED = 0X0B,
		// UNDEFINED = 0X0C,
		// UNDEFINED = 0X0D,
		// UNDEFINED = 0X0E,
		HEARTBEAT = 0X0F
	};
	enum PacketSuccess {
		FAILURE = 0X0,
		SUCCESS = 0X01,
		UNKNOWN = 0X02,
		ERROR = 0X03,
		CRITICAL = 0X04
	};

	// We reuse the code, it works so why not
	QByteArray GeneratePacket(ClientPacketType packetType, PacketSuccess pSuccess = UNKNOWN, QByteArray data = nullptr) {

		QByteArray packetData;

		packetData.append(0xAB); // Abaci Signature

		packetData.append(packetType);
		packetData.append(pSuccess);

		if (data != nullptr) {
			uint16_t size = data.size();
			uint8_t lsize = size; // Implicit cast, drops the high bits from bytes and only fetches the low bits
			uint8_t hsize = size >> 8; // Shift the size, 8 bits to the right to get the high bits
									   // The implicit cast to 16 bits -> 8 bits will ignore the high bits
			packetData.append(hsize);
			packetData.append(lsize);
			packetData.append(data);
		}
		else {
			packetData.append(2, (int8_t)0);
		}

		packetData.append(0xAB); // Abaci signature

		return packetData;
	}
	ConnectionArgs conArgs;
	QTcpSocket* client = nullptr;
	bool properShutdown = false; // A bool that is set when the socket is prepared to be disconnected
signals:
	void socketDisconnected(const QString &reason);
	void socketConnected();
	void workReady(double start, double end);
	void message(const QString &messaage); // Used as a callback to log what the client is doing at the socket level
	void clientIDcb(QString clientID);
	void clientUsernamecb(QString clientUsername);
	void clientWorkCompletedcb(QString clientWorkCompleted);
	void clientCPUInfocb(QString clientCPUInfo);
	void clientCPUCountcb(QString clientCPUCount);
	void clientPlatformcb(QString clientPlatform);

public slots:
	void connected() {
		emit message("Socket connected");
		emit socketConnected();
		client->write(GeneratePacket(AUTHREQ, SUCCESS, QByteArray::fromStdString(QString(conArgs.username + ":" + conArgs.password).toStdString())));
	}

	void disconnected() {
		emit message("Socket disconnected");
		if(!properShutdown) // If the socket is not prepared for this shutdown
		emit socketDisconnected(client->errorString());
		
	}
	void shutdown() {
		properShutdown = true;
		client->write(GeneratePacket(DISCONNECTING, SUCCESS));
		client->flush();
		client->abort();
		QThread::currentThread()->quit();
	}
	void readyRead() {
		recvData:
		uint8_t signature;
		client->read((char*)&signature,sizeof(uint8_t)); // The signature is the size of short (int8)
		if (signature == (uint8_t)0xAB) {
			// Valid signature
			uint8_t functionByte;
			client->read((char*)&functionByte, sizeof(uint8_t));
			std::bitset<8> functionBitset = functionByte;
			
			uint8_t successByte;
			client->read((char*)&successByte, sizeof(uint8_t));

			uint16_t payloadSize;
			uint8_t hPayloadSize, lPayloadSize;
			client->read((char*)&hPayloadSize, sizeof(uint8_t));
			client->read((char*)&lPayloadSize, sizeof(uint8_t));
			payloadSize = hPayloadSize << 8 | lPayloadSize; // Move the high bits to the right position and OR the low bits
															  // This forms our full payload size amount

			if (functionBitset.test(7)) { // Test highest bit, server should make all higher bits set
				// From server
				switch (functionByte) {
				case 0xF0:
					if (successByte == SUCCESS && payloadSize < 1)
						emit message("Sever shutting down gracefully");
					else if (successByte == SUCCESS && payloadSize > 1)
						emit message("Server shutting down, message: " + QString::fromStdString(client->read(payloadSize).toStdString()));
					else if (successByte == FAILURE || successByte == CRITICAL || successByte == ERROR)
						emit message("Server shutting down, not graceful");
					else
						emit message("Server shutting down, unknown reason");
					properShutdown = true;
					client->close();
					break;
				case 0xF1:
					emit message("Received authentication response");
					if (successByte == SUCCESS) {
						emit message("Successfully authorized, requesting client info");
						client->write(GeneratePacket(REQCLIENTDETAILS, SUCCESS));
						client->write(GeneratePacket(WORKREQ, SUCCESS));
					}
					else if (successByte == FAILURE) {
						emit message("Authentication failed, reason:");
						if (payloadSize <= 0)
							emit message("No authentication message received");
						else {
							QString payload = QString::fromStdString(client->read(payloadSize).toStdString());
							emit message(payload);
						}
					}
					else {
						// The server isn't programmed to send a critical or error status with this function
						emit message("Authentication failed, no known reason");
					}
					break;
				case 0xF2:
					if (successByte == SUCCESS) {
						if (payloadSize <= 0) {
							emit message("Server sent work request with no work");
						}
						else {
							QString payload = QString::fromStdString(client->read(payloadSize).toStdString());
							auto workSplit = payload.split(":");
							double startIter = workSplit[0].toDouble();
							double endIter = workSplit[1].toDouble();
							emit workReady(startIter, endIter);
						}
					}
					else if(successByte == UNKNOWN) {
						client->write(GeneratePacket(WORKREQ, SUCCESS));
					}
					break;
				case 0xF3:
					emit message("Reset password result received");
					if (successByte == SUCCESS) {
						emit message("Password successfully changed");
					}
					else if (successByte == FAILURE) {
						emit message("Password change failed");
						if (payloadSize <= 0)
							emit message("Unknown reason");
						else {
							QString payload = QString::fromStdString(client->read(payloadSize).toStdString());
							emit message(payload);
						}
					}
					else {
						emit message("Unknown result");
					}
					break;
				case 0xF4:
					// Client ID response

					if (successByte == SUCCESS) {
						emit message("Client ID received from server");
						if (payloadSize >= 1) {
							QString clientID = QString::fromStdString(client->read(payloadSize).toStdString());
							emit message("Client ID is " + clientID);
							emit clientIDcb(clientID);
						}
						else
							emit message("Server returned empty result but successful status");
					}
					else{
						emit message("Server was unable to fetch our clientID");
					}	
					break;
				case 0xF5:
					// Client username response
					if (successByte == SUCCESS) {
						emit message("Client username received from server");
						if (payloadSize >= 1) {
							QString clientUsername = QString::fromStdString(client->read(payloadSize).toStdString());
							emit message("Client username is " + clientUsername);
							emit clientUsernamecb(clientUsername);
						}
						else
							emit message("Server returned empty result but successful status");
					}
					else
						emit message("Server was unable to fetch our client username");
					break;
				case 0xF6:
					if (successByte == SUCCESS) {
						emit message("Client work completed count received from server");
						if (payloadSize >= 0) {
							QString workCompleted = QString::fromStdString(client->read(payloadSize).toStdString());
							emit message("Client work completed count is " + workCompleted);
							emit clientWorkCompletedcb(workCompleted);
						}
						else
							emit message("Server returned empty result but successful status");
					}
					else
						emit message("Server was unable to fetch our client work completed count");
					break;
				case 0xF7:
					if (successByte == SUCCESS) {
						emit message("Client CPU Info received from server");
						if (payloadSize >= 0) {
							QString CPUInfo = QString::fromStdString(client->read(payloadSize).toStdString());
							emit message("Client work completed count is " + CPUInfo);
							emit clientCPUInfocb(CPUInfo);
						}
						else
							emit message("Server returned empty result but successful status, assuming empty cpu info");
					}
					else
						emit message("Server was unable to fetch our client CPU Info");
					break;
				case 0xF8:
					if (successByte == SUCCESS) {
						emit message("Client CPU count received from server");
						if (payloadSize >= 0) {
							QString CPUCount = QString::fromStdString(client->read(payloadSize).toStdString());
							emit message("Client CPU count is " + CPUCount);
							emit clientCPUCountcb(CPUCount);
						}
						else
							emit message("Server returned empty result but successful status");
					}
					else
						emit message("Server was unable to fetch our CPU count");
					break;
				case 0xF9:
					if (successByte == SUCCESS) {
						emit message("Client Platform received from server");
						if (payloadSize >= 0) {
							QString Platform = QString::fromStdString(client->read(payloadSize).toStdString());
							emit message("Client platform is " + Platform);
							emit clientPlatformcb(Platform);
						}
						else
							emit message("Server returned empty result but successful status, assuming empty platform");
					}
					else
						emit message("Server was unable to fetch our platform");
					break;
				case 0xFE:
					// Server telling us that it is online

					break;
				case 0xFF:
					client->write(GeneratePacket(HEARTBEAT, SUCCESS)); // Send back a heartbeat
					break;
				}
			}
			else {
				// From client
				emit message("Socket received request from client?");
			}
			client->read(1); // Read ending signature
			if (client->bytesAvailable() >= 6)
				goto recvData; // We received a packet while reading the last packet
		}
		else {
			emit message("Invalid socket signature");
		}
	}
	void changeUsername(QString newUsername) {
		emit message("Setting client username to " + newUsername);
		client->write(GeneratePacket(SETCLIENTUSERNAME, SUCCESS, QByteArray::fromStdString(newUsername.toStdString())));
	}
	void changePassword(QString newPassword) {
		emit message("Changing client password");
		client->write(GeneratePacket(RESETPASSWORD, SUCCESS, QByteArray::fromStdString(newPassword.toStdString())));
	}
	void changeCPUInfo(QString newCPUInfo) {
		emit message("Setting client CPU Info to " + newCPUInfo);
		client->write(GeneratePacket(SETCLIENTCPU, SUCCESS, QByteArray::fromStdString(newCPUInfo.toStdString())));
	}
	void changePlatform(QString newPlatform) {
		emit message("Setting client platform to " + newPlatform);
		client->write(GeneratePacket(SETCLIENTPLATFOM, SUCCESS, QByteArray::fromStdString(newPlatform.toStdString())));
	}
	void forceFlush() {
		client->flush();
	}
	/*
	
	Sending doubles via TCP is very hard work 
	
	*/
	void completeWork(std::vector<double> primes) {
		QByteArray primesToSend;

		short pCount = 0;
		size_t initCount = primes.size();
		auto primeIter = primes.data();
		while (1 == 1) {
			if (initCount >= 1000) {
				
				primesToSend.append(QByteArray::number((double)1000));
				primesToSend.append(":");
				for (size_t iter = 0; iter < 1000; iter++) {
					primesToSend.append(QByteArray::number((double)*primeIter,'f'));
					primesToSend.append(":");
					primeIter++; // Increment the iteration
				}
				client->write(GeneratePacket(CLIENTWORKCOMPLETED, SUCCESS, primesToSend));
				client->flush();
				initCount -= 1000; // Subtract the 1000 doubles we just read
				primesToSend.clear();
			}
			else{
				primesToSend.append(QByteArray::number((double)initCount));
				primesToSend.append(":");
				for (size_t iter = 0; iter < initCount; iter++) {
					primesToSend.append(QByteArray::number((double)*primeIter,'f'));
					primesToSend.append(":");
					primeIter++;
				}
				client->write(GeneratePacket(CLIENTWORKCOMPLETED, SUCCESS, primesToSend));
				client->flush();
				break;
			}
		}
	}
	void askForWork() {
		client->write(GeneratePacket(WORKREQ, SUCCESS));
		client->flush();
	}
public:
	AbaciClient(ConnectionArgs args,QObject* parent = nullptr) : QObject(parent), conArgs(args){
		emit message("Attempting to connect");
		if (client == nullptr) {
			client = new QTcpSocket(this);
			connect(client, &QTcpSocket::connected, this, &AbaciClient::connected);
			connect(client, &QTcpSocket::disconnected, this, &AbaciClient::disconnected);
			connect(client, &QTcpSocket::readyRead, this, &AbaciClient::readyRead);
		}
		QApplication::processEvents();
		client->connectToHost(args.hostname, args.port);
	}
};