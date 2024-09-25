#include "mainappwindow.h"
#include "ui_mainappwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QShowEvent>
#include <QTimer>

MainAppWindow::MainAppWindow(QString userName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainAppWindow),
    currentUserName(userName)
{
    ui->setupUi(this);

    this->setWindowTitle("Пользователь: " + currentUserName);


    ui->bookingsTableWidget->setColumnCount(4);
    ui->bookingsTableWidget->setHorizontalHeaderLabels(QStringList() << "Услуга" << "Дата" << "Время" << "Кол-во человек");

    connect(ui->searchButton, &QPushButton::clicked, this, &MainAppWindow::searchServices);

    connect(ui->bookButton, &QPushButton::clicked, this, &MainAppWindow::bookService);

    connect(ui->loadBookingsButton, &QPushButton::clicked, this, &MainAppWindow::loadBookings);

    connect(ui->cancelBookingButton, &QPushButton::clicked, this, &MainAppWindow::cancelBooking);

    connect(ui->editBookingButton, &QPushButton::clicked, this, &MainAppWindow::editBooking);

    connect(ui->viewHistoryButton, &QPushButton::clicked, this, &MainAppWindow::loadBookingHistory);

    initializeDatabase();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainAppWindow::checkForUpcomingBookings);
    timer->start(120000);

    QTimer *historyTimer = new QTimer(this);
    connect(historyTimer, &QTimer::timeout, this, &MainAppWindow::movePastBookingsToHistory);
    historyTimer->start(60000);
}

MainAppWindow::~MainAppWindow()
{
    delete ui;
}

void MainAppWindow::initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/murodali/Projects/BookingManagementSystem/database.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS services ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "name TEXT NOT NULL, "
                               "description TEXT, "
                               "date DATE, "
                               "time TIME, "
                               "capacity INTEGER, "
                               "agent_id INTEGER NOT NULL, "
                               "FOREIGN KEY (agent_id) REFERENCES agents(id))";

    if (!query.exec(createTableQuery)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу: " + query.lastError().text());
    } else {
        qDebug() << "Таблица 'services' успешно создана или уже существует.";
    }

    QString createBookingsTableQuery = "CREATE TABLE IF NOT EXISTS bookings ("
                                       "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                       "user_name TEXT NOT NULL, "
                                       "service_id INTEGER NOT NULL, "
                                       "booking_date DATE NOT NULL, "
                                       "booking_time TIME NOT NULL, "
                                       "people_count INTEGER, "
                                       "FOREIGN KEY(service_id) REFERENCES services(id), "
                                       "FOREIGN KEY(user_name) REFERENCES users(username))";
    if (!query.exec(createBookingsTableQuery)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу bookings: " + query.lastError().text());
    } else {
        qDebug() << "Таблица 'bookings' успешно создана или уже существует.";
    }
    QString createHistoryTableQuery = "CREATE TABLE IF NOT EXISTS booking_history ("
                                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                      "user_name TEXT, "
                                      "service_name TEXT, "
                                      "booking_date TEXT, "
                                      "booking_time TEXT, "
                                      "people_count INTEGER, "
                                      "notes TEXT)";
    if (!query.exec(createHistoryTableQuery)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу booking_history: " + query.lastError().text());
    } else {
        qDebug() << "Таблица 'booking_history' успешно создана или уже существует.";
    }
}

void MainAppWindow::searchServices() {
    QString searchText = ui->serviceSearchLineEdit->text();

    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите текст для поиска.");
        return;
    }

    ui->searchResultsListWidget->clear();

    QSqlQuery query;
    query.prepare(
        "SELECT services.name, services.description, services.capacity, services.date, services.time, "
        "(SELECT COUNT(*) FROM bookings WHERE bookings.service_id = services.id) AS is_booked "
        "FROM services "
        "WHERE services.name LIKE :search OR services.description LIKE :search"
        );
    query.bindValue(":search", "%" + searchText + "%");

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка поиска: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        QString name = query.value(0).toString();
        QString description = query.value(1).toString();
        //int capacity = query.value(2).toInt();
        //QString serviceDate = query.value(3).toString();
        //QTime serviceTime = query.value(4).toTime();
        int isBooked = query.value(5).toInt();

        QString bookingStatus = (isBooked > 0) ? "Забронирована" : "Не забронирована";

        //QString formattedTime = serviceTime.toString("HH-mm");

        QString resultString = QString("%1: %2, Статус- %3")
                                   .arg(name)
                                   .arg(description)
                                   //.arg(capacity)
                                   //.arg(serviceDate)
                                   //.arg(formattedTime)
                                   .arg(bookingStatus);

        ui->searchResultsListWidget->addItem(resultString);
    }

    if (ui->searchResultsListWidget->count() == 0) {
        QMessageBox::information(this, "Результаты", "Ничего не найдено.");
    }
}


void MainAppWindow::bookService() {
    QListWidgetItem* selectedItem = ui->searchResultsListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Выберите услугу из списка.");
        return;
    }

    QString selectedService = selectedItem->text();

    QStringList serviceParts = selectedService.split(": ");
    if (serviceParts.size() < 2) {
        QMessageBox::warning(this, "Ошибка", "Невозможно извлечь название услуги.");
        return;
    }

    QString serviceName = serviceParts[0];
    QString bookingDate = ui->bookingDateEdit->date().toString("yyyy-MM-dd");
    QString bookingTime = ui->bookingTimeEdit->time().toString("HH:mm:ss");
    int peopleCount = ui->peopleCountLineEdit->text().toInt();

    if (serviceName.isEmpty() || peopleCount <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные данные для бронирования.");
        return;
    }

    qDebug() << "Service name:" << serviceName;
    qDebug() << "Booking date:" << bookingDate;
    qDebug() << "Booking time:" << bookingTime;
    qDebug() << "People count:" << peopleCount;

    QSqlQuery query;
    query.prepare("SELECT id FROM services WHERE name = :service_name");
    query.bindValue(":service_name", serviceName);

    if (!query.exec()) {
        qDebug() << "SQL error while selecting service:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось найти услугу: " + query.lastError().text());
        return;
    }

    if (!query.next()) {
        qDebug() << "No service found with name:" << serviceName;
        QMessageBox::critical(this, "Ошибка", "Услуга не найдена.");
        return;
    }

    int serviceId = query.value(0).toInt();
    qDebug() << "Service ID:" << serviceId;
    query.prepare("INSERT INTO bookings (user_name, service_id, booking_date, booking_time, people_count) "
                  "VALUES (:user_name, :service_id, :booking_date, :booking_time, :people_count)");
    query.bindValue(":user_name", currentUserName);
    query.bindValue(":service_id", serviceId);
    query.bindValue(":booking_date", bookingDate);
    query.bindValue(":booking_time", bookingTime);
    query.bindValue(":people_count", peopleCount);

    if (!query.exec()) {
        qDebug() << "SQL error while inserting booking:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось забронировать услугу: " + query.lastError().text());
        return;
    }

    qDebug() << "Service successfully booked.";
    QMessageBox::information(this, "Успех", "Услуга успешно забронирована.");
}

void MainAppWindow::loadBookings() {
    ui->bookingsTableWidget->clearContents();
    ui->bookingsTableWidget->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT services.name, bookings.booking_date, bookings.booking_time, bookings.people_count "
                  "FROM bookings JOIN services ON bookings.service_id = services.id "
                  "WHERE bookings.user_name = :user_name");
    query.bindValue(":user_name", currentUserName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить бронирования: " + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        QString serviceName = query.value(0).toString();
        QString bookingDate = query.value(1).toString();
        QString bookingTime = query.value(2).toString();
        int peopleCount = query.value(3).toInt();

        ui->bookingsTableWidget->insertRow(row);
        ui->bookingsTableWidget->setItem(row, 0, new QTableWidgetItem(serviceName));
        ui->bookingsTableWidget->setItem(row, 1, new QTableWidgetItem(bookingDate));
        ui->bookingsTableWidget->setItem(row, 2, new QTableWidgetItem(bookingTime));
        ui->bookingsTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(peopleCount)));

        row++;
    }
}

void MainAppWindow::cancelBooking() {
    int selectedRow = ui->bookingsTableWidget->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите бронирование для отмены.");
        return;
    }

    QString serviceName = ui->bookingsTableWidget->item(selectedRow, 0)->text();
    QString bookingDate = ui->bookingsTableWidget->item(selectedRow, 1)->text();

    QSqlQuery query;
    query.prepare("DELETE FROM bookings WHERE service_id = (SELECT id FROM services WHERE name = :service_name) "
                  "AND booking_date = :booking_date AND user_name = :user_name");
    query.bindValue(":service_name", serviceName);
    query.bindValue(":booking_date", bookingDate);
    query.bindValue(":user_name", currentUserName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось отменить бронирование: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Успех", "Бронирование отменено.");
    loadBookings();
}

void MainAppWindow::editBooking() {
    int selectedRow = ui->bookingsTableWidget->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите бронирование для изменения.");
        return;
    }

    QString serviceName = ui->bookingsTableWidget->item(selectedRow, 0)->text();
    QString oldBookingDate = ui->bookingsTableWidget->item(selectedRow, 1)->text();
    QString oldBookingTime = ui->bookingsTableWidget->item(selectedRow, 2)->text();
    //int oldPeopleCount = ui->bookingsTableWidget->item(selectedRow, 3)->text().toInt();

    QString newBookingDate = ui->newBookingDateEdit->date().toString("yyyy-MM-dd");
    QString newBookingTime = ui->newBookingTimeEdit->time().toString("HH:mm:ss");
    int newPeopleCount = ui->newPeopleCountLineEdit->text().toInt();

    QSqlQuery query;
    query.prepare("UPDATE bookings SET booking_date = :new_date, booking_time = :new_time, people_count = :new_count "
                  "WHERE service_id = (SELECT id FROM services WHERE name = :service_name) "
                  "AND booking_date = :old_date AND booking_time = :old_time AND user_name = :user_name");
    query.bindValue(":new_date", newBookingDate);
    query.bindValue(":new_time", newBookingTime);
    query.bindValue(":new_count", newPeopleCount);
    query.bindValue(":service_name", serviceName);
    query.bindValue(":old_date", oldBookingDate);
    query.bindValue(":old_time", oldBookingTime);
    query.bindValue(":user_name", currentUserName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось изменить бронирование: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Успех", "Бронирование успешно изменено.");
    loadBookings();
}

void MainAppWindow::checkForUpcomingBookings() {
    QSqlQuery query;
    query.prepare("SELECT services.name, bookings.booking_date, bookings.booking_time "
                  "FROM bookings JOIN services ON bookings.service_id = services.id "
                  "WHERE bookings.user_name = :user_name");
    query.bindValue(":user_name", currentUserName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить данные для напоминаний: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        QString serviceName = query.value(0).toString();
        QString bookingDate = query.value(1).toString();
        QString bookingTime = query.value(2).toString();

        QDateTime bookingDateTime = QDateTime::fromString(bookingDate + " " + bookingTime, "yyyy-MM-dd HH:mm:ss");
        QDateTime currentDateTime = QDateTime::currentDateTime();

        if (currentDateTime.secsTo(bookingDateTime) <= 3600) {
            QMessageBox::information(this, "Напоминание", "У вас бронирование меньше чем через час: " +
                                                              serviceName + " в " + bookingDate + " " + bookingTime);
        }
    }
}

void MainAppWindow::movePastBookingsToHistory() {
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();

    QSqlQuery query;
    query.prepare(
        "SELECT bookings.*, services.name AS service_name "
        "FROM bookings "
        "JOIN services ON bookings.service_id = services.id "
        "WHERE (bookings.booking_date < :current_date "
        "OR (bookings.booking_date = :current_date AND bookings.booking_time < :current_time)) "
        "AND bookings.user_name = :user_name"
        );
    query.bindValue(":current_date", currentDate.toString("yyyy-MM-dd"));
    query.bindValue(":current_time", currentTime.toString("HH:mm:ss"));
    query.bindValue(":user_name", currentUserName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось получить прошедшие бронирования: " + query.lastError().text());
        return;
    }

    QSqlQuery insertQuery;
    while (query.next()) {
        QString serviceName = query.value("service_name").toString();
        QString bookingDate = query.value("booking_date").toString();
        QString bookingTime = query.value("booking_time").toString();
        int peopleCount = query.value("people_count").toInt();
        QString notes = query.value("notes").toString();

        qDebug() << "Move Service Name:" << serviceName;
        qDebug() << "Move Booking Date:" << bookingDate;
        qDebug() << "Move Booking Time:" << bookingTime;
        qDebug() << "Move People Count:" << peopleCount;

        insertQuery.prepare(
            "INSERT INTO booking_history (user_name, service_name, booking_date, booking_time, people_count, notes) "
            "VALUES (:user_name, :service_name, :booking_date, :booking_time, :people_count, :notes)"
            );
        insertQuery.bindValue(":user_name", currentUserName);
        insertQuery.bindValue(":service_name", serviceName);
        insertQuery.bindValue(":booking_date", bookingDate);
        insertQuery.bindValue(":booking_time", bookingTime);
        insertQuery.bindValue(":people_count", peopleCount);
        insertQuery.bindValue(":notes", notes);

        if (!insertQuery.exec()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось переместить бронирование в историю: " + insertQuery.lastError().text());
        }
    }

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM bookings WHERE booking_date < :current_date "
                        "OR (booking_date = :current_date AND booking_time < :current_time) "
                        "AND user_name = :user_name");
    deleteQuery.bindValue(":current_date", currentDate.toString("yyyy-MM-dd"));
    deleteQuery.bindValue(":current_time", currentTime.toString("HH:mm:ss"));
    deleteQuery.bindValue(":user_name", currentUserName);

    if (!deleteQuery.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить прошедшие бронирования: " + deleteQuery.lastError().text());
    }

    loadBookings();
}

void MainAppWindow::loadBookingHistory() {
    QSqlQuery query;
    query.prepare("SELECT service_name, booking_date, booking_time, people_count, notes "
                  "FROM booking_history WHERE user_name = :user_name");
    query.bindValue(":user_name", currentUserName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить историю бронирований: " + query.lastError().text());
        return;
    }

    ui->historyListWidget->clear();

    while (query.next()) {
        QString serviceName = query.value(0).toString();
        QString bookingDate = query.value(1).toString();
        QString bookingTime = query.value(2).toString();
        int peopleCount = query.value(3).toInt();

        QString bookingInfo = QString("%1 - %2 %3 (Количество людей: %4)")
                                  .arg(serviceName, bookingDate, bookingTime, QString::number(peopleCount));

        ui->historyListWidget->addItem(bookingInfo);

        qDebug() << "Service Name:" << serviceName;
    }
}

