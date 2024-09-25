/********************************************************************************
** Form generated from reading UI file 'mainappwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINAPPWINDOW_H
#define UI_MAINAPPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainAppWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *serviceSearchLineEdit;
    QLabel *label;
    QPushButton *searchButton;
    QListWidget *searchResultsListWidget;
    QDateEdit *bookingDateEdit;
    QLabel *label_2;
    QTimeEdit *bookingTimeEdit;
    QLabel *label_3;
    QLineEdit *peopleCountLineEdit;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QPushButton *bookButton;
    QLabel *label_6;
    QPushButton *loadBookingsButton;
    QTableWidget *bookingsTableWidget;
    QPushButton *cancelBookingButton;
    QPushButton *editBookingButton;
    QLineEdit *newPeopleCountLineEdit;
    QDateEdit *newBookingDateEdit;
    QTimeEdit *newBookingTimeEdit;
    QPushButton *viewHistoryButton;
    QListWidget *historyListWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainAppWindow)
    {
        if (MainAppWindow->objectName().isEmpty())
            MainAppWindow->setObjectName("MainAppWindow");
        MainAppWindow->resize(839, 687);
        centralwidget = new QWidget(MainAppWindow);
        centralwidget->setObjectName("centralwidget");
        serviceSearchLineEdit = new QLineEdit(centralwidget);
        serviceSearchLineEdit->setObjectName("serviceSearchLineEdit");
        serviceSearchLineEdit->setGeometry(QRect(50, 20, 161, 21));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 58, 16));
        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(70, 40, 100, 32));
        searchResultsListWidget = new QListWidget(centralwidget);
        searchResultsListWidget->setObjectName("searchResultsListWidget");
        searchResultsListWidget->setGeometry(QRect(10, 80, 281, 231));
        bookingDateEdit = new QDateEdit(centralwidget);
        bookingDateEdit->setObjectName("bookingDateEdit");
        bookingDateEdit->setGeometry(QRect(180, 390, 110, 22));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 390, 131, 16));
        bookingTimeEdit = new QTimeEdit(centralwidget);
        bookingTimeEdit->setObjectName("bookingTimeEdit");
        bookingTimeEdit->setGeometry(QRect(180, 420, 111, 22));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 420, 141, 20));
        peopleCountLineEdit = new QLineEdit(centralwidget);
        peopleCountLineEdit->setObjectName("peopleCountLineEdit");
        peopleCountLineEdit->setGeometry(QRect(180, 450, 51, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 450, 131, 20));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 480, 171, 16));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(180, 480, 101, 21));
        bookButton = new QPushButton(centralwidget);
        bookButton->setObjectName("bookButton");
        bookButton->setGeometry(QRect(80, 340, 111, 32));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(390, 230, 151, 20));
        loadBookingsButton = new QPushButton(centralwidget);
        loadBookingsButton->setObjectName("loadBookingsButton");
        loadBookingsButton->setGeometry(QRect(370, 190, 161, 32));
        bookingsTableWidget = new QTableWidget(centralwidget);
        bookingsTableWidget->setObjectName("bookingsTableWidget");
        bookingsTableWidget->setGeometry(QRect(390, 250, 311, 192));
        cancelBookingButton = new QPushButton(centralwidget);
        cancelBookingButton->setObjectName("cancelBookingButton");
        cancelBookingButton->setGeometry(QRect(710, 240, 81, 32));
        editBookingButton = new QPushButton(centralwidget);
        editBookingButton->setObjectName("editBookingButton");
        editBookingButton->setGeometry(QRect(390, 460, 81, 32));
        newPeopleCountLineEdit = new QLineEdit(centralwidget);
        newPeopleCountLineEdit->setObjectName("newPeopleCountLineEdit");
        newPeopleCountLineEdit->setGeometry(QRect(390, 520, 51, 21));
        newBookingDateEdit = new QDateEdit(centralwidget);
        newBookingDateEdit->setObjectName("newBookingDateEdit");
        newBookingDateEdit->setGeometry(QRect(390, 490, 110, 22));
        newBookingTimeEdit = new QTimeEdit(centralwidget);
        newBookingTimeEdit->setObjectName("newBookingTimeEdit");
        newBookingTimeEdit->setGeometry(QRect(510, 490, 118, 22));
        viewHistoryButton = new QPushButton(centralwidget);
        viewHistoryButton->setObjectName("viewHistoryButton");
        viewHistoryButton->setGeometry(QRect(370, 20, 131, 31));
        historyListWidget = new QListWidget(centralwidget);
        historyListWidget->setObjectName("historyListWidget");
        historyListWidget->setGeometry(QRect(510, 20, 251, 161));
        MainAppWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainAppWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 839, 24));
        MainAppWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainAppWindow);
        statusbar->setObjectName("statusbar");
        MainAppWindow->setStatusBar(statusbar);

        retranslateUi(MainAppWindow);

        QMetaObject::connectSlotsByName(MainAppWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainAppWindow)
    {
        MainAppWindow->setWindowTitle(QCoreApplication::translate("MainAppWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainAppWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        searchButton->setText(QCoreApplication::translate("MainAppWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        label_2->setText(QCoreApplication::translate("MainAppWindow", "\320\224\320\260\321\202\320\260 \320\261\321\200\320\276\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("MainAppWindow", "\320\222\321\200\320\265\320\274\321\217 \320\261\321\200\320\276\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_4->setText(QCoreApplication::translate("MainAppWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\207\320\265\320\273\320\276\320\262\320\265\320\272", nullptr));
        label_5->setText(QCoreApplication::translate("MainAppWindow", "\320\237\321\200\320\270\320\274\320\265\321\207\320\260\320\275\320\270\321\217 (\320\277\320\276 \320\266\320\265\320\273\320\260\320\275\320\270\321\216)", nullptr));
        bookButton->setText(QCoreApplication::translate("MainAppWindow", "\320\227\320\260\320\261\321\200\320\276\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        label_6->setText(QCoreApplication::translate("MainAppWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\261\321\200\320\276\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\271", nullptr));
        loadBookingsButton->setText(QCoreApplication::translate("MainAppWindow", "\320\234\320\276\320\270 \320\261\321\200\320\276\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        cancelBookingButton->setText(QCoreApplication::translate("MainAppWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        editBookingButton->setText(QCoreApplication::translate("MainAppWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        viewHistoryButton->setText(QCoreApplication::translate("MainAppWindow", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200 \320\270\321\201\321\202\320\276\321\200\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainAppWindow: public Ui_MainAppWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINAPPWINDOW_H
