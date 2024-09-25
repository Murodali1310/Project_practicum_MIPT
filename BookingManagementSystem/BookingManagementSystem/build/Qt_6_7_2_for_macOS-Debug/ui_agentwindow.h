/********************************************************************************
** Form generated from reading UI file 'agentwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGENTWINDOW_H
#define UI_AGENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AgentWindow
{
public:
    QLineEdit *serviceNameLineEdit;
    QLineEdit *descriptionLineEdit;
    QLabel *label;
    QLabel *label_2;
    QDateEdit *serviceDateEdit;
    QTimeEdit *serviceTimeEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *capacityLineEdit;
    QLabel *label_5;
    QTableWidget *serviceTableWidget;
    QLabel *label_6;
    QPushButton *addServiceButton;
    QPushButton *editServiceButton;
    QPushButton *deleteServiceButton;
    QPushButton *exportBookingsButton;

    void setupUi(QWidget *AgentWindow)
    {
        if (AgentWindow->objectName().isEmpty())
            AgentWindow->setObjectName("AgentWindow");
        AgentWindow->resize(745, 544);
        serviceNameLineEdit = new QLineEdit(AgentWindow);
        serviceNameLineEdit->setObjectName("serviceNameLineEdit");
        serviceNameLineEdit->setGeometry(QRect(130, 40, 113, 31));
        descriptionLineEdit = new QLineEdit(AgentWindow);
        descriptionLineEdit->setObjectName("descriptionLineEdit");
        descriptionLineEdit->setGeometry(QRect(380, 40, 113, 31));
        label = new QLabel(AgentWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 111, 31));
        label_2 = new QLabel(AgentWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 40, 111, 31));
        serviceDateEdit = new QDateEdit(AgentWindow);
        serviceDateEdit->setObjectName("serviceDateEdit");
        serviceDateEdit->setGeometry(QRect(120, 100, 110, 22));
        serviceTimeEdit = new QTimeEdit(AgentWindow);
        serviceTimeEdit->setObjectName("serviceTimeEdit");
        serviceTimeEdit->setGeometry(QRect(370, 100, 118, 22));
        label_3 = new QLabel(AgentWindow);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 100, 81, 20));
        label_4 = new QLabel(AgentWindow);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(270, 100, 91, 20));
        capacityLineEdit = new QLineEdit(AgentWindow);
        capacityLineEdit->setObjectName("capacityLineEdit");
        capacityLineEdit->setGeometry(QRect(120, 140, 51, 21));
        label_5 = new QLabel(AgentWindow);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(27, 140, 91, 20));
        serviceTableWidget = new QTableWidget(AgentWindow);
        serviceTableWidget->setObjectName("serviceTableWidget");
        serviceTableWidget->setGeometry(QRect(30, 280, 256, 192));
        label_6 = new QLabel(AgentWindow);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 260, 91, 16));
        addServiceButton = new QPushButton(AgentWindow);
        addServiceButton->setObjectName("addServiceButton");
        addServiceButton->setGeometry(QRect(570, 50, 121, 32));
        editServiceButton = new QPushButton(AgentWindow);
        editServiceButton->setObjectName("editServiceButton");
        editServiceButton->setGeometry(QRect(570, 100, 131, 32));
        deleteServiceButton = new QPushButton(AgentWindow);
        deleteServiceButton->setObjectName("deleteServiceButton");
        deleteServiceButton->setGeometry(QRect(300, 280, 121, 32));
        exportBookingsButton = new QPushButton(AgentWindow);
        exportBookingsButton->setObjectName("exportBookingsButton");
        exportBookingsButton->setGeometry(QRect(600, 240, 100, 32));

        retranslateUi(AgentWindow);

        QMetaObject::connectSlotsByName(AgentWindow);
    } // setupUi

    void retranslateUi(QWidget *AgentWindow)
    {
        AgentWindow->setWindowTitle(QCoreApplication::translate("AgentWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("AgentWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\203\321\201\320\273\321\203\320\263\320\270:", nullptr));
        label_2->setText(QCoreApplication::translate("AgentWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \321\203\321\201\320\273\321\203\320\263\320\270:", nullptr));
        label_3->setText(QCoreApplication::translate("AgentWindow", "\320\224\320\260\321\202\320\260 \321\203\321\201\320\273\321\203\320\263\320\270:", nullptr));
        label_4->setText(QCoreApplication::translate("AgentWindow", "\320\222\321\200\320\265\320\274\321\217 \321\203\321\201\320\273\321\203\320\263\320\270:", nullptr));
        label_5->setText(QCoreApplication::translate("AgentWindow", "\320\222\320\274\320\265\321\201\321\202\320\270\320\274\320\276\321\201\321\202\321\214: ", nullptr));
        label_6->setText(QCoreApplication::translate("AgentWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \321\203\321\201\320\273\321\203\320\263", nullptr));
        addServiceButton->setText(QCoreApplication::translate("AgentWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\321\201\320\273\321\203\320\263\321\203 ", nullptr));
        editServiceButton->setText(QCoreApplication::translate("AgentWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \321\203\321\201\320\273\321\203\320\263\321\203", nullptr));
        deleteServiceButton->setText(QCoreApplication::translate("AgentWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\203\321\201\320\273\321\203\320\263\321\203", nullptr));
        exportBookingsButton->setText(QCoreApplication::translate("AgentWindow", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AgentWindow: public Ui_AgentWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGENTWINDOW_H
