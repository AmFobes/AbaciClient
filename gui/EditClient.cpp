#pragma once
#include "EditClient.h"

#include "ui_editclient.h"

EditClient::EditClient(ClientInfo &clInfo,QWidget* parent) : ui(new Ui::EditClient) ,curClient(clInfo){
	ui->setupUi(this);
	ui->numClientID->setValue(clInfo.clID);
	ui->txtClientUsername->setText(clInfo.clUsername);
	ui->numWorkCompleted->setValue(clInfo.clWorkCompleted);
	ui->numCPUCount->setValue(clInfo.clCPUCount);
	ui->txtCPUInfo->setText(clInfo.clCPUInfo);
	ui->txtPlatform->setText(clInfo.clPlatform);

	connect(ui->btnUpdate, &QPushButton::clicked, this, &EditClient::updateClient);
	connect(ui->btnExit, &QPushButton::clicked, this, &EditClient::btnExit);
	connect(ui->btnLoadDefaults, &QPushButton::clicked, this, &EditClient::btnShowDefaults);
}

EditClient::~EditClient() {
	delete ui;
	delete this;
}

void EditClient::updateClient() {
	if (curClient.clUsername != ui->txtClientUsername->text()) {
		emit updateUsername(ui->txtClientUsername->text());
		emit requestSocketFlush();
	}
	if (!ui->txtClientPassword->text().isEmpty()) {
		emit updatePassword(ui->txtClientPassword->text());
		emit requestSocketFlush();
	}
	if (curClient.clCPUCount != ui->numCPUCount->value()) {
		emit updateCPUCount(ui->numCPUCount->value());
		emit requestSocketFlush();
	}
	if (curClient.clCPUInfo != ui->txtCPUInfo->text()) {
		emit updateCPUInfo(ui->txtCPUInfo->text());
		emit requestSocketFlush();
	}
	if (curClient.clPlatform != ui->txtPlatform->text()) {
		emit updatePlatform(ui->txtPlatform->text());
		emit requestSocketFlush();
	}
}

void EditClient::btnExit() {
	this->close();
}

void EditClient::btnShowDefaults() {
#if defined(WIN32)
	// MSVC specific functions used here, only compile this block of code on windows systems
	int regs[4] = { 0 };
	char vendor[13];
	__cpuid(regs, 0);				// mov eax,0; cpuid
	memcpy(vendor, &regs[1], 4);	// copy EBX
	memcpy(vendor + 4, &regs[3], 4);// copy EDX
	memcpy(vendor + 8, &regs[2], 4);// copy ECX
	vendor[12] = '\0'; // add null terminator for string
	QString cpuINFO = QSysInfo::currentCpuArchitecture() + " " + QString::fromUtf8(vendor);
	ui->txtCPUInfo->setText(cpuINFO);
#else
	ui->txtPlatform->setText(QSysInfo::currentCpuArchitecture());
#endif
	ui->txtPlatform->setText(QSysInfo::prettyProductName());


}