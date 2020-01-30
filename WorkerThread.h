#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QThread>
#include <QMetaType>
#include <QVector>

#include "Primes/PrimeClass.h"

class WorkerThread : public QObject{
	Q_OBJECT

private:
	AbaciHelpers::TDPrime* primeInstance = nullptr;

public:
	WorkerThread(QWidget* parent = nullptr) : QObject(parent) {};

signals:
	void ready();
	void finishedWork(std::vector<double> range);
	void workMessage(const QString &message);
public slots:

	void setThreads(unsigned int threads = std::thread::hardware_concurrency()) {
		if (!(primeInstance == nullptr))
			delete primeInstance;
		if(threads > 0)
		primeInstance = new AbaciHelpers::TDPrime(threads);
	}

	void work(double *range,size_t count) {
		
		if(primeInstance == nullptr)
		setThreads();
		emit workMessage("Starting work, testing " + QString::number(count) + " numbers");
		auto primesFound = primeInstance->findPrimesInRange(range,count);
		emit workMessage("Work finished, " + QString::number(primesFound.size()) + " prime numbers found");
		emit workMessage(QString::number(((double)primesFound.size() / count) * 100) + "% of numbers are primes!");
		emit finishedWork(primesFound);
		return;
	}
};