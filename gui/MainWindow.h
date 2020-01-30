#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QtConcurrent/QtConcurrent>
#include "WorkerThread.h"
#include "Client.h"
#include "EditClient.h"

namespace Ui {
	class MainWindow;
};

class MainWindow : public QMainWindow {
	Q_OBJECT

private:
	double* workArray = nullptr; // Instead of using local variables and allocation space for them, use one global object
								 // This may increase register pressure but other methods (vector) were causing a memory leak
								// (the leak took a weekend to figure out)
	WorkerThread *abaciWorker;
	AbaciClient *abaciClient;
	QThread* clientThread;

	int workReqDelay = 0;
public: 
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
signals:
	void workSignal(double *range, size_t size);
	void onCloseEvent();
protected:
	void closeEvent(QCloseEvent* event);
public slots:
	void tryConnect();
	void socketMessage(const QString &message);
	void setClientID(QString clID);
	void setClientUsername(QString clUsername);
	void setClientWC(QString clWC);
	void setClientCPUInfo(QString clCPUInfo);
	void setClientCPUCount(QString clCPUCount);
	void setClientPlatform(QString clPlatform);
	void showEditClientForm();
	void workReady(double start, double end);
	void workCompleted(std::vector<double> primes);
	void updateWorkStatus(QString status);
	void updateNumRange(QString status);
	void chkShowPasswordClicked(bool clicked);
	void btnClearConLog();

	void socketDisconnected(const QString &reason);

	void chkAutoReqWorkClicked(bool checked);
	void numReqUpdated();
	void workReqHandler();
private:
	Ui::MainWindow* ui;
};