#ifndef MAINAPPWINDOW_H
#define MAINAPPWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSqlDatabase>

namespace Ui {
class MainAppWindow;
}

class MainAppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainAppWindow(QString userName, QWidget *parent = nullptr);
    ~MainAppWindow();

private slots:
    void searchServices();

    void bookService();

    void loadBookings();

    void cancelBooking();

    void editBooking();

    void loadBookingHistory();

private:
    void initializeDatabase();

    void loadServices();

    void checkForUpcomingBookings();

    void movePastBookingsToHistory();

    Ui::MainAppWindow *ui;
    QString currentUserName;
    QSqlDatabase db;
};

#endif // MAINAPPWINDOW_H
