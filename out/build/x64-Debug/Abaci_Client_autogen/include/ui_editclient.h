/********************************************************************************
** Form generated from reading UI file 'editclient.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCLIENT_H
#define UI_EDITCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditClient
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QSpinBox *numCPUCount;
    QPushButton *btnUpdate;
    QLabel *label;
    QLabel *label_6;
    QSpinBox *numClientID;
    QLabel *label_2;
    QLineEdit *txtCPUInfo;
    QPushButton *btnExit;
    QSpinBox *numWorkCompleted;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *txtPlatform;
    QLineEdit *txtClientUsername;
    QLabel *label_7;
    QLineEdit *txtClientPassword;
    QCheckBox *chkShowPassword;
    QPushButton *btnLoadDefaults;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EditClient)
    {
        if (EditClient->objectName().isEmpty())
            EditClient->setObjectName(QString::fromUtf8("EditClient"));
        EditClient->resize(374, 287);
        centralwidget = new QWidget(EditClient);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        numCPUCount = new QSpinBox(centralwidget);
        numCPUCount->setObjectName(QString::fromUtf8("numCPUCount"));
        numCPUCount->setMinimum(1);
        numCPUCount->setMaximum(128);
        numCPUCount->setValue(1);

        gridLayout->addWidget(numCPUCount, 5, 1, 1, 1);

        btnUpdate = new QPushButton(centralwidget);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));

        gridLayout->addWidget(btnUpdate, 6, 2, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        numClientID = new QSpinBox(centralwidget);
        numClientID->setObjectName(QString::fromUtf8("numClientID"));
        numClientID->setReadOnly(true);

        gridLayout->addWidget(numClientID, 0, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        txtCPUInfo = new QLineEdit(centralwidget);
        txtCPUInfo->setObjectName(QString::fromUtf8("txtCPUInfo"));

        gridLayout->addWidget(txtCPUInfo, 6, 1, 1, 1);

        btnExit = new QPushButton(centralwidget);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout->addWidget(btnExit, 7, 2, 1, 1);

        numWorkCompleted = new QSpinBox(centralwidget);
        numWorkCompleted->setObjectName(QString::fromUtf8("numWorkCompleted"));
        numWorkCompleted->setReadOnly(true);

        gridLayout->addWidget(numWorkCompleted, 4, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        txtPlatform = new QLineEdit(centralwidget);
        txtPlatform->setObjectName(QString::fromUtf8("txtPlatform"));

        gridLayout->addWidget(txtPlatform, 7, 1, 1, 1);

        txtClientUsername = new QLineEdit(centralwidget);
        txtClientUsername->setObjectName(QString::fromUtf8("txtClientUsername"));

        gridLayout->addWidget(txtClientUsername, 2, 1, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        txtClientPassword = new QLineEdit(centralwidget);
        txtClientPassword->setObjectName(QString::fromUtf8("txtClientPassword"));

        gridLayout->addWidget(txtClientPassword, 3, 1, 1, 1);

        chkShowPassword = new QCheckBox(centralwidget);
        chkShowPassword->setObjectName(QString::fromUtf8("chkShowPassword"));

        gridLayout->addWidget(chkShowPassword, 3, 2, 1, 1);

        btnLoadDefaults = new QPushButton(centralwidget);
        btnLoadDefaults->setObjectName(QString::fromUtf8("btnLoadDefaults"));

        gridLayout->addWidget(btnLoadDefaults, 5, 2, 1, 1);

        EditClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EditClient);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 374, 26));
        EditClient->setMenuBar(menubar);
        statusbar = new QStatusBar(EditClient);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        EditClient->setStatusBar(statusbar);

        retranslateUi(EditClient);

        QMetaObject::connectSlotsByName(EditClient);
    } // setupUi

    void retranslateUi(QMainWindow *EditClient)
    {
        EditClient->setWindowTitle(QApplication::translate("EditClient", "MainWindow", nullptr));
        label_5->setText(QApplication::translate("EditClient", "CPU Info", nullptr));
        btnUpdate->setText(QApplication::translate("EditClient", "Update", nullptr));
        label->setText(QApplication::translate("EditClient", "Client ID", nullptr));
        label_6->setText(QApplication::translate("EditClient", "Platform", nullptr));
        label_2->setText(QApplication::translate("EditClient", "Client Username", nullptr));
        btnExit->setText(QApplication::translate("EditClient", "Exit", nullptr));
        label_3->setText(QApplication::translate("EditClient", "Work Completed", nullptr));
        label_4->setText(QApplication::translate("EditClient", "CPU Count", nullptr));
        label_7->setText(QApplication::translate("EditClient", "Client Password", nullptr));
        chkShowPassword->setText(QApplication::translate("EditClient", "Show", nullptr));
        btnLoadDefaults->setText(QApplication::translate("EditClient", "Defaults", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditClient: public Ui_EditClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCLIENT_H
