#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <thread>
#include <QMessageBox>
#include "Client.h"
#include <QtConcurrent/qtconcurrent_global.h>

MainWindow::MainWindow(QWidget* parent) : ui(new Ui::MainWindow) {
	ui->setupUi(this);

	connect(ui->btnServerConnect, &QPushButton::clicked, this, &MainWindow::tryConnect);
	connect(ui->btnEditClientInfo, &QPushButton::clicked, this, &MainWindow::showEditClientForm);
	connect(ui->chkShowPassword, &QCheckBox::clicked, this, &MainWindow::chkShowPasswordClicked);
	connect(ui->btnClearConnectionLog, &QCheckBox::clicked, this, &MainWindow::btnClearConLog);
	connect(ui->chkautoReqWork, &QCheckBox::clicked, this, &MainWindow::chkAutoReqWorkClicked);
	connect(ui->numRequest, qOverload<int>(&QSpinBox::valueChanged), this, &MainWindow::numReqUpdated);
	abaciWorker = new WorkerThread();
	QThread* abaciWorkerThread = new QThread();
	abaciWorker->moveToThread(abaciWorkerThread);
	connect(this, &MainWindow::workSignal, abaciWorker, &WorkerThread::work);
//	connect(abaciWorker, &WorkerThread::workMessage, this, &MainWindow::workMessage); CAUSES WORK DELAY 

	abaciWorkerThread->start();
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::tryConnect() {
	socketMessage("Trying to connect, timeout is 30 seconds..");
	if (ui->txtHostname->text().isEmpty())
		QMessageBox(QMessageBox::Icon::Critical, "Invalid input", "Hostname cannot be empty when connecting to server", QMessageBox::Ok, this).exec();
	else if(ui->txtUsername->text().isEmpty())
		QMessageBox(QMessageBox::Icon::Critical, "Invalid input", "Username cannot be empty when connecting to server", QMessageBox::Ok, this).exec();
	else if(ui->txtPassword->text().isEmpty())
		QMessageBox(QMessageBox::Icon::Critical, "Invalid input", "Password cannot be empty when connecting to server", QMessageBox::Ok, this).exec();
	else {
		ConnectionArgs conArgs;
		conArgs.hostname = ui->txtHostname->text();
		conArgs.port = ui->numPort->value();
		conArgs.username = ui->txtUsername->text();
		conArgs.password = ui->txtPassword->text();

		this->abaciClient = new AbaciClient(conArgs);
		connect(abaciClient, &AbaciClient::clientIDcb, this, &MainWindow::setClientID);
		connect(abaciClient, &AbaciClient::clientWorkCompletedcb, this, &MainWindow::setClientWC);
		connect(abaciClient, &AbaciClient::clientUsernamecb, this, &MainWindow::setClientUsername);
		connect(abaciClient, &AbaciClient::clientCPUCountcb, this, &MainWindow::setClientCPUCount);
		connect(abaciClient, &AbaciClient::clientCPUInfocb, this, &MainWindow::setClientCPUInfo);
		connect(abaciClient, &AbaciClient::clientPlatformcb, this, &MainWindow::setClientPlatform);
		connect(abaciClient, &AbaciClient::workReady, this, &MainWindow::workReady);
		connect(abaciClient, &AbaciClient::message, this, &MainWindow::socketMessage);
		connect(abaciClient, &AbaciClient::socketDisconnected, this, &MainWindow::socketDisconnected);
		connect(abaciWorker, &WorkerThread::finishedWork, abaciClient, &AbaciClient::completeWork);
		connect(abaciWorker, &WorkerThread::finishedWork, this, &MainWindow::workCompleted);
		connect(abaciWorker, &WorkerThread::ready, abaciClient, &AbaciClient::askForWork);
		connect(ui->btnRequestWork, &QPushButton::clicked, abaciClient, &AbaciClient::askForWork);
		connect(this, &MainWindow::onCloseEvent, abaciClient, &AbaciClient::shutdown);
		

		clientThread = new QThread(this);
		abaciClient->moveToThread(clientThread);
		clientThread->start();
	}
	return;
}

void MainWindow::socketMessage(const QString &message) {
	ui->lstConnectionLog->addItem(message);
	ui->lstConnectionLog->scrollToBottom();
}

void MainWindow::setClientID(QString clID) {
	ui->lblStatus->setText("Connected");
	ui->btnEditClientInfo->setEnabled(true);
	ui->btnRequestWork->setEnabled(true);
	ui->chkautoReqWork->setEnabled(true);
	ui->numRequest->setEnabled(true);
	ui->lblClientID->setText(clID);
}

void MainWindow::setClientUsername(QString clUsername) {
	ui->lblClientUsername->setText(clUsername);
}

void MainWindow::setClientWC(QString clWC) {
	ui->lblClientWorkCompleted->setText(clWC);
}

void MainWindow::setClientCPUCount(QString clCPUC) {
	ui->lblClientCPUCount->setText(clCPUC);
	abaciWorker->setThreads(clCPUC.toInt());
}

void MainWindow::setClientCPUInfo(QString clCPUInfo) {
	ui->lblClientCPUInfo->setText(clCPUInfo);
}

void MainWindow::setClientPlatform(QString clPlatform) {
	ui->lblClientPlatform->setText(clPlatform);
}

void MainWindow::showEditClientForm() {
	ClientInfo info;
	info.clID = ui->lblClientID->text().toInt();
	info.clUsername = ui->lblClientUsername->text();
	info.clWorkCompleted = ui->lblClientWorkCompleted->text().toInt();
	info.clCPUCount = ui->lblClientCPUCount->text().toInt();
	info.clCPUInfo = ui->lblClientCPUInfo->text();
	info.clPlatform = ui->lblClientPlatform->text();

	EditClient *editClient = new EditClient(info, this);
	connect(editClient, &EditClient::updateUsername, abaciClient, &AbaciClient::changeUsername);
	connect(editClient, &EditClient::updatePassword, abaciClient, &AbaciClient::changePassword);
	connect(editClient, &EditClient::updateCPUInfo, abaciClient, &AbaciClient::changeCPUInfo);
	connect(editClient, &EditClient::updatePlatform, abaciClient, &AbaciClient::changePlatform);
	connect(editClient, &EditClient::requestSocketFlush, abaciClient, &AbaciClient::forceFlush);
	editClient->setWindowModality(Qt::WindowModality::ApplicationModal);
	editClient->show();
}

void MainWindow::workReady(double start, double end) {
	updateWorkStatus("Preparing to work");
	size_t size = 0;
	if(workArray == nullptr)
	 workArray = new double[(size_t)(end-start) / 2];
	
	if (trunc(std::remainder(start, 2)) == 0) 
		start += 1;
	int iteration = 0;
	for (double num = start; num <= end; num += 2) {
		workArray[iteration] = num;
		size += 1;
		iteration++;
	}

	emit workSignal(workArray,size); 
	updateWorkStatus("Working");
	updateNumRange("Start: " + QString::number(start) + " End: " +QString::number(end));
}

void MainWindow::workCompleted(std::vector<double> primes) {
	updateWorkStatus("Finished working, " + QString::number(primes.size()) + " primes found in batch");
	updateNumRange("");
}

void MainWindow::updateWorkStatus(QString status) {
	ui->lblWorkStatus->setText(status);
}
void MainWindow::updateNumRange(QString range) {
	ui->lblWorkNumRange->setText(range);
}
void MainWindow::chkShowPasswordClicked(bool clicked) {
	if (clicked)
		ui->txtPassword->setEchoMode(QLineEdit::EchoMode::Normal);
	else
		ui->txtPassword->setEchoMode(QLineEdit::EchoMode::Password);
}

void MainWindow::btnClearConLog() {
	ui->lstConnectionLog->clear();
}

void MainWindow::socketDisconnected(const QString &reason) {
	ui->lblStatus->setText("Disconnected");
	ui->btnEditClientInfo->setEnabled(false);
	ui->btnRequestWork->setEnabled(false);
	workReqDelay = 0;
	ui->chkautoReqWork->setEnabled(false);
	ui->numRequest->setEnabled(false);
	QMessageBox(QMessageBox::Icon::Warning, "Abaci Socket Client", "Got disconnected from Abaci Server. \n Reason (if any): " + reason,QMessageBox::Button::Ok).exec();
}

void MainWindow::closeEvent(QCloseEvent* event) {
	emit onCloseEvent();
}

void MainWindow::numReqUpdated() {
	workReqDelay = ui->numRequest->value();
}

void MainWindow::chkAutoReqWorkClicked(bool checked) {
	if (checked) {
		workReqDelay = ui->numRequest->value();
		QtConcurrent::run(this,&MainWindow::workReqHandler);
	}
	else {
		workReqDelay = 0;
	}
}
void MainWindow::workReqHandler() {
	while (workReqDelay != 0) {
		QMetaObject::invokeMethod(abaciClient, "askForWork");
		QThread::sleep(workReqDelay);
	}
}
