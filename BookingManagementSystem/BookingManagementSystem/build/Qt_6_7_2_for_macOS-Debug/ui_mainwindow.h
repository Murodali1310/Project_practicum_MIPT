/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *loginButton;
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QLabel *label_2;
    QLabel *label;
    QPushButton *registerButton;
    QPushButton *agentRegisterButton;
    QPushButton *agentLoginButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(698, 379);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setEnabled(true);
        loginButton->setGeometry(QRect(310, 140, 100, 31));
        loginLineEdit = new QLineEdit(centralwidget);
        loginLineEdit->setObjectName("loginLineEdit");
        loginLineEdit->setEnabled(true);
        loginLineEdit->setGeometry(QRect(230, 60, 161, 21));
        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEnabled(true);
        passwordLineEdit->setGeometry(QRect(230, 100, 161, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(130, 100, 61, 16));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setEnabled(true);
        label->setGeometry(QRect(130, 60, 71, 30));
        registerButton = new QPushButton(centralwidget);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(200, 140, 100, 31));
        agentRegisterButton = new QPushButton(centralwidget);
        agentRegisterButton->setObjectName("agentRegisterButton");
        agentRegisterButton->setGeometry(QRect(410, 100, 181, 31));
        agentLoginButton = new QPushButton(centralwidget);
        agentLoginButton->setObjectName("agentLoginButton");
        agentLoginButton->setGeometry(QRect(420, 50, 121, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 698, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        agentRegisterButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217 \320\260\320\263\320\265\320\275\321\202\320\260", nullptr));
        agentLoginButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\271\321\202\320\270 \320\272\320\260\320\272 \320\260\320\263\320\265\320\275\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
