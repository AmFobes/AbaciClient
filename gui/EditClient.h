#pragma once
#include <QApplication>
#include <QMainWindow>

namespace Ui {
	class EditClient;
}

struct ClientInfo {
	int clID; 
	QString clUsername;
	int clWorkCompleted;
	int clCPUCount;
	QString clCPUInfo;
	QString clPlatform;
	double padding; // 8 bytes of padding
};

class EditClient : public QMainWindow {
	Q_OBJECT

public:
	explicit EditClient(ClientInfo &clInfo,QWidget* parent = nullptr);
	~EditClient();

signals:
	void updateUsername(QString username);
	void updatePassword(QString password);
	void updateCPUCount(int cpuCount);
	void updateCPUInfo(QString CPUInfo);
	void updatePlatform(QString platform);
	void requestSocketFlush();

public slots:
	void updateClient();
	void btnExit();
	void btnShowDefaults();

private:
	Ui::EditClient* ui;
	ClientInfo curClient;
};