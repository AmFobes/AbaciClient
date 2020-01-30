/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_3;
    QLabel *lblWorkStatprmpt;
    QLabel *lblWorkStatus;
    QLabel *lblWorkNumRangeprmpt;
    QLabel *lblWorkNumRange;
    QListWidget *lstWorkLog;
    QPushButton *btnClearWorkLog;
    QFormLayout *formLayout_6;
    QPushButton *btnRequestWork;
    QLabel *label;
    QLabel *lblClientTitle;
    QFormLayout *formLayout_2;
    QLabel *lblClientIDPrmpt;
    QLabel *lblClientID;
    QLabel *lblClientUsernamePrmpt;
    QLabel *lblClientUsername;
    QLabel *lblClientWCPrmpt;
    QLabel *lblClientWorkCompleted;
    QLabel *lblClientCPUInfoprmpt;
    QLabel *lblClientCPUInfo;
    QLabel *lblCPUCountprmpt;
    QLabel *lblClientCPUCount;
    QLabel *lblClientPlatformPrmpt;
    QLabel *lblClientPlatform;
    QPushButton *btnEditClientInfo;
    QFormLayout *formLayout;
    QLabel *lblHostnamePrompt;
    QLineEdit *txtHostname;
    QLabel *lblPortPrompt;
    QSpinBox *numPort;
    QLabel *label_9;
    QLineEdit *txtUsername;
    QLabel *label_10;
    QLineEdit *txtPassword;
    QCheckBox *chkShowPassword;
    QPushButton *btnServerConnect;
    QHBoxLayout *horizontalLayout;
    QLabel *lblStatusPrompt;
    QLabel *lblStatus;
    QPushButton *btnClearConnectionLog;
    QListWidget *lstConnectionLog;
    QLabel *lblThreadTitle;
    QLabel *lblServerTitle;
    QLabel *lblConfigurationTitle;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(908, 632);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        lblWorkStatprmpt = new QLabel(centralwidget);
        lblWorkStatprmpt->setObjectName(QString::fromUtf8("lblWorkStatprmpt"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, lblWorkStatprmpt);

        lblWorkStatus = new QLabel(centralwidget);
        lblWorkStatus->setObjectName(QString::fromUtf8("lblWorkStatus"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lblWorkStatus);

        lblWorkNumRangeprmpt = new QLabel(centralwidget);
        lblWorkNumRangeprmpt->setObjectName(QString::fromUtf8("lblWorkNumRangeprmpt"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, lblWorkNumRangeprmpt);

        lblWorkNumRange = new QLabel(centralwidget);
        lblWorkNumRange->setObjectName(QString::fromUtf8("lblWorkNumRange"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, lblWorkNumRange);

        lstWorkLog = new QListWidget(centralwidget);
        lstWorkLog->setObjectName(QString::fromUtf8("lstWorkLog"));

        formLayout_3->setWidget(2, QFormLayout::SpanningRole, lstWorkLog);

        btnClearWorkLog = new QPushButton(centralwidget);
        btnClearWorkLog->setObjectName(QString::fromUtf8("btnClearWorkLog"));

        formLayout_3->setWidget(3, QFormLayout::SpanningRole, btnClearWorkLog);


        gridLayout->addLayout(formLayout_3, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 1);

        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        btnRequestWork = new QPushButton(centralwidget);
        btnRequestWork->setObjectName(QString::fromUtf8("btnRequestWork"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, btnRequestWork);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_6->setWidget(1, QFormLayout::LabelRole, label);


        gridLayout_2->addLayout(formLayout_6, 3, 1, 1, 1);

        lblClientTitle = new QLabel(centralwidget);
        lblClientTitle->setObjectName(QString::fromUtf8("lblClientTitle"));
        lblClientTitle->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblClientTitle, 2, 0, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        lblClientIDPrmpt = new QLabel(centralwidget);
        lblClientIDPrmpt->setObjectName(QString::fromUtf8("lblClientIDPrmpt"));
        QFont font;
        font.setPointSize(10);
        lblClientIDPrmpt->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, lblClientIDPrmpt);

        lblClientID = new QLabel(centralwidget);
        lblClientID->setObjectName(QString::fromUtf8("lblClientID"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lblClientID);

        lblClientUsernamePrmpt = new QLabel(centralwidget);
        lblClientUsernamePrmpt->setObjectName(QString::fromUtf8("lblClientUsernamePrmpt"));
        lblClientUsernamePrmpt->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lblClientUsernamePrmpt);

        lblClientUsername = new QLabel(centralwidget);
        lblClientUsername->setObjectName(QString::fromUtf8("lblClientUsername"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lblClientUsername);

        lblClientWCPrmpt = new QLabel(centralwidget);
        lblClientWCPrmpt->setObjectName(QString::fromUtf8("lblClientWCPrmpt"));
        lblClientWCPrmpt->setFont(font);
        lblClientWCPrmpt->setScaledContents(false);
        lblClientWCPrmpt->setWordWrap(false);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, lblClientWCPrmpt);

        lblClientWorkCompleted = new QLabel(centralwidget);
        lblClientWorkCompleted->setObjectName(QString::fromUtf8("lblClientWorkCompleted"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lblClientWorkCompleted);

        lblClientCPUInfoprmpt = new QLabel(centralwidget);
        lblClientCPUInfoprmpt->setObjectName(QString::fromUtf8("lblClientCPUInfoprmpt"));
        lblClientCPUInfoprmpt->setFont(font);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, lblClientCPUInfoprmpt);

        lblClientCPUInfo = new QLabel(centralwidget);
        lblClientCPUInfo->setObjectName(QString::fromUtf8("lblClientCPUInfo"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lblClientCPUInfo);

        lblCPUCountprmpt = new QLabel(centralwidget);
        lblCPUCountprmpt->setObjectName(QString::fromUtf8("lblCPUCountprmpt"));
        lblCPUCountprmpt->setFont(font);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, lblCPUCountprmpt);

        lblClientCPUCount = new QLabel(centralwidget);
        lblClientCPUCount->setObjectName(QString::fromUtf8("lblClientCPUCount"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, lblClientCPUCount);

        lblClientPlatformPrmpt = new QLabel(centralwidget);
        lblClientPlatformPrmpt->setObjectName(QString::fromUtf8("lblClientPlatformPrmpt"));
        lblClientPlatformPrmpt->setFont(font);

        formLayout_2->setWidget(5, QFormLayout::LabelRole, lblClientPlatformPrmpt);

        lblClientPlatform = new QLabel(centralwidget);
        lblClientPlatform->setObjectName(QString::fromUtf8("lblClientPlatform"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, lblClientPlatform);

        btnEditClientInfo = new QPushButton(centralwidget);
        btnEditClientInfo->setObjectName(QString::fromUtf8("btnEditClientInfo"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(50);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnEditClientInfo->sizePolicy().hasHeightForWidth());
        btnEditClientInfo->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(6, QFormLayout::LabelRole, btnEditClientInfo);


        gridLayout_2->addLayout(formLayout_2, 3, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lblHostnamePrompt = new QLabel(centralwidget);
        lblHostnamePrompt->setObjectName(QString::fromUtf8("lblHostnamePrompt"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblHostnamePrompt);

        txtHostname = new QLineEdit(centralwidget);
        txtHostname->setObjectName(QString::fromUtf8("txtHostname"));

        formLayout->setWidget(0, QFormLayout::FieldRole, txtHostname);

        lblPortPrompt = new QLabel(centralwidget);
        lblPortPrompt->setObjectName(QString::fromUtf8("lblPortPrompt"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblPortPrompt);

        numPort = new QSpinBox(centralwidget);
        numPort->setObjectName(QString::fromUtf8("numPort"));
        numPort->setMaximum(65535);
        numPort->setValue(5123);

        formLayout->setWidget(2, QFormLayout::FieldRole, numPort);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_9);

        txtUsername = new QLineEdit(centralwidget);
        txtUsername->setObjectName(QString::fromUtf8("txtUsername"));

        formLayout->setWidget(3, QFormLayout::FieldRole, txtUsername);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_10);

        txtPassword = new QLineEdit(centralwidget);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(4, QFormLayout::FieldRole, txtPassword);

        chkShowPassword = new QCheckBox(centralwidget);
        chkShowPassword->setObjectName(QString::fromUtf8("chkShowPassword"));

        formLayout->setWidget(5, QFormLayout::FieldRole, chkShowPassword);

        btnServerConnect = new QPushButton(centralwidget);
        btnServerConnect->setObjectName(QString::fromUtf8("btnServerConnect"));

        formLayout->setWidget(6, QFormLayout::LabelRole, btnServerConnect);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblStatusPrompt = new QLabel(centralwidget);
        lblStatusPrompt->setObjectName(QString::fromUtf8("lblStatusPrompt"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblStatusPrompt->sizePolicy().hasHeightForWidth());
        lblStatusPrompt->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lblStatusPrompt);

        lblStatus = new QLabel(centralwidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(100);
        sizePolicy2.setHeightForWidth(lblStatus->sizePolicy().hasHeightForWidth());
        lblStatus->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(lblStatus);

        btnClearConnectionLog = new QPushButton(centralwidget);
        btnClearConnectionLog->setObjectName(QString::fromUtf8("btnClearConnectionLog"));

        horizontalLayout->addWidget(btnClearConnectionLog);


        formLayout->setLayout(6, QFormLayout::FieldRole, horizontalLayout);

        lstConnectionLog = new QListWidget(centralwidget);
        lstConnectionLog->setObjectName(QString::fromUtf8("lstConnectionLog"));
        lstConnectionLog->setAutoFillBackground(false);
        lstConnectionLog->setFlow(QListView::TopToBottom);

        formLayout->setWidget(8, QFormLayout::SpanningRole, lstConnectionLog);


        gridLayout_2->addLayout(formLayout, 1, 0, 1, 1);

        lblThreadTitle = new QLabel(centralwidget);
        lblThreadTitle->setObjectName(QString::fromUtf8("lblThreadTitle"));
        lblThreadTitle->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblThreadTitle, 0, 1, 1, 1);

        lblServerTitle = new QLabel(centralwidget);
        lblServerTitle->setObjectName(QString::fromUtf8("lblServerTitle"));
        lblServerTitle->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblServerTitle, 0, 0, 1, 1);

        lblConfigurationTitle = new QLabel(centralwidget);
        lblConfigurationTitle->setObjectName(QString::fromUtf8("lblConfigurationTitle"));
        lblConfigurationTitle->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblConfigurationTitle, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 908, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Abaci Client", nullptr));
        lblWorkStatprmpt->setText(QApplication::translate("MainWindow", "Work Status:", nullptr));
        lblWorkStatus->setText(QString());
        lblWorkNumRangeprmpt->setText(QApplication::translate("MainWindow", "Trial range:", nullptr));
        lblWorkNumRange->setText(QString());
        btnClearWorkLog->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        btnRequestWork->setText(QApplication::translate("MainWindow", "Request Work", nullptr));
        label->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lblClientTitle->setText(QApplication::translate("MainWindow", "Client info", nullptr));
        lblClientIDPrmpt->setText(QApplication::translate("MainWindow", "Client ID", nullptr));
        lblClientID->setText(QString());
        lblClientUsernamePrmpt->setText(QApplication::translate("MainWindow", "Username", nullptr));
        lblClientUsername->setText(QString());
        lblClientWCPrmpt->setText(QApplication::translate("MainWindow", "Work Completed", nullptr));
        lblClientWorkCompleted->setText(QString());
        lblClientCPUInfoprmpt->setText(QApplication::translate("MainWindow", "CPU Info", nullptr));
        lblClientCPUInfo->setText(QString());
        lblCPUCountprmpt->setText(QApplication::translate("MainWindow", "CPU Count", nullptr));
        lblClientCPUCount->setText(QString());
        lblClientPlatformPrmpt->setText(QApplication::translate("MainWindow", "Platform", nullptr));
        lblClientPlatform->setText(QString());
        btnEditClientInfo->setText(QApplication::translate("MainWindow", "Edit", nullptr));
        lblHostnamePrompt->setText(QApplication::translate("MainWindow", "Hostname", nullptr));
        lblPortPrompt->setText(QApplication::translate("MainWindow", "Port", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Username", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Password", nullptr));
        chkShowPassword->setText(QApplication::translate("MainWindow", "Show password", nullptr));
        btnServerConnect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        lblStatusPrompt->setText(QApplication::translate("MainWindow", "Status:", nullptr));
        lblStatus->setText(QString());
        btnClearConnectionLog->setText(QApplication::translate("MainWindow", "Clear Log", nullptr));
        lblThreadTitle->setText(QApplication::translate("MainWindow", "Work", nullptr));
        lblServerTitle->setText(QApplication::translate("MainWindow", "Server Connection", nullptr));
        lblConfigurationTitle->setText(QApplication::translate("MainWindow", "Configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
