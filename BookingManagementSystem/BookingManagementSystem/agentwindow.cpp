#include "agentwindow.h"
#include "ui_agentwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QFileDialog>
AgentWindow::AgentWindow(int AgentId, QWidget *parent)
    : QWidget(parent)
    , currentAgentId(AgentId), ui(new Ui::AgentWindow)
{
    ui->setupUi(this);
    connect(ui->addServiceButton, &QPushButton::clicked, this, &AgentWindow::onAddServiceButtonClicked);

    //connect(ui->addServiceButton, &QPushButton::clicked, this, &AgentWindow::onAddServiceButtonClicked);

    connect(ui->editServiceButton, &QPushButton::clicked, this, &AgentWindow::onEditServiceButtonClicked);
    connect(ui->deleteServiceButton, &QPushButton::clicked, this, &AgentWindow::onDeleteServiceButtonClicked);
    connect(ui->exportBookingsButton, &QPushButton::clicked, this, &AgentWindow::onExportBookingsButtonClicked);

    loadAgentServices(currentAgentId);

}

AgentWindow::~AgentWindow()
{
    delete ui;
}
void AgentWindow::onAddServiceButtonClicked() {
    QString serviceName = ui->serviceNameLineEdit->text();
    QString description = ui->descriptionLineEdit->text();
    QDate serviceDate = ui->serviceDateEdit->date();
    QTime serviceTime = ui->serviceTimeEdit->time();
    int capacity = ui->capacityLineEdit->text().toInt();

    if (serviceName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название услуги не может быть пустым");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO services (name, description, date, time, capacity, agent_id) "
                  "VALUES (:name, :description, :date, :time, :capacity, :agent_id)");
    query.bindValue(":name", serviceName);
    query.bindValue(":description", description);
    query.bindValue(":date", serviceDate);
    query.bindValue(":time", serviceTime);
    query.bindValue(":capacity", capacity);
    query.bindValue(":agent_id", currentAgentId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при добавлении услуги: " + query.lastError().text());
    } else {
        loadAgentServices(currentAgentId);
    }
}

void AgentWindow::loadAgentServices(int agentId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM services WHERE agent_id = :agent_id");
    query.bindValue(":agent_id", agentId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при загрузке услуг: " + query.lastError().text());
        return;
    }

    qDebug() << "Загрузка услуг для агента с ID:" << agentId;

    ui->serviceTableWidget->setRowCount(0);
    ui->serviceTableWidget->setColumnCount(6);

    QStringList headers = {"Id", "Название", "Описание", "Дата", "Время", "Вместимость"};
    ui->serviceTableWidget->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->serviceTableWidget->insertRow(row);
        ui->serviceTableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->serviceTableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->serviceTableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->serviceTableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->serviceTableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->serviceTableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        row++;
    }

    if (row == 0) {
        QMessageBox::information(this, "Информация", "Услуги не найдены для этого агента");
    }
}

void AgentWindow::onDeleteServiceButtonClicked() {
    int selectedRow = ui->serviceTableWidget->currentRow();
    if (selectedRow == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите услугу для удаления");
        return;
    }

    QString serviceName = ui->serviceTableWidget->item(selectedRow, 1)->text();

    if (QMessageBox::question(this, "Удаление услуги", "Вы уверены, что хотите удалить услугу " + serviceName + "?") == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM services WHERE name=:name AND agent_id=:agentId");
        query.bindValue(":name", serviceName);
        query.bindValue(":agentId", currentAgentId);

        if (!query.exec()) {
            QMessageBox::critical(this, "Ошибка", "Ошибка при удалении услуги: " + query.lastError().text());
        } else {
            loadAgentServices(currentAgentId);
        }
    }
}

void AgentWindow::onEditServiceButtonClicked() {
    int selectedRow = ui->serviceTableWidget->currentRow();
    if (selectedRow == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите услугу для сохранения изменений");
        return;
    }

    QString newServiceName = ui->serviceNameLineEdit->text();
    QString newDescription = ui->descriptionLineEdit->text();
    QDate newServiceDate = ui->serviceDateEdit->date();
    QTime newServiceTime = ui->serviceTimeEdit->time();
    int newCapacity = ui->capacityLineEdit->text().toInt();

    if (newServiceName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название услуги не может быть пустым");
        return;
    }

    QString serviceId = ui->serviceTableWidget->item(selectedRow, 0)->text();

    QSqlQuery query;
    query.prepare("UPDATE services SET name=:name, description=:description, date=:date, time=:time, capacity=:capacity "
                  "WHERE id=:serviceId AND agent_id=:agentId");
    query.bindValue(":name", newServiceName);
    query.bindValue(":description", newDescription);
    query.bindValue(":date", newServiceDate);
    query.bindValue(":time", newServiceTime);
    query.bindValue(":capacity", newCapacity);
    query.bindValue(":serviceId", serviceId);
    query.bindValue(":agentId", currentAgentId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при сохранении изменений: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Успех", "Услуга успешно обновлена!");
        loadAgentServices(currentAgentId);
    }
}


void AgentWindow::onExportBookingsButtonClicked() {
    int selectedRow = ui->serviceTableWidget->currentRow();
    if (selectedRow == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите услугу для выгрузки списка пользователей");
        return;
    }

    QString serviceName = ui->serviceTableWidget->item(selectedRow, 1)->text();

    qDebug() << "Выг Выбранная услуга:" << serviceName;

    QSqlQuery query;
    query.prepare("SELECT users.user_name, bookings.booking_date, bookings.booking_time, bookings.people_count "
                  "FROM bookings "
                  "JOIN users ON bookings.user_name = users.user_name "
                  "JOIN services ON bookings.service_id = services.id "
                  "WHERE services.name = :serviceName AND services.agent_id = :agentId");
    query.bindValue(":serviceName", serviceName);
    query.bindValue(":agentId", currentAgentId);

    qDebug() << "SQL-запрос: SELECT users.user_name, bookings.booking_date, bookings.booking_time, bookings.people_count "
                "FROM bookings JOIN users ON bookings.user_name = users.user_name "
                "JOIN services ON bookings.service_id = services.id "
                "WHERE services.name =" << serviceName << "AND services.agent_id =" << currentAgentId;

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при выгрузке данных: " + query.lastError().text());
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        return;
    }

    QFile file(QFileDialog::getSaveFileName(this, "Сохранить файл", "", "CSV Files (*.csv)"));
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "Имя пользователя,Дата бронирования,Время бронирования,Количество людей\n";

        while (query.next()) {
            QString userName = query.value(0).toString();
            QString bookingDate = query.value(1).toString();
            QString bookingTime = query.value(2).toString();
            QString peopleCount = query.value(3).toString();

            stream << userName << "," << bookingDate << "," << bookingTime << "," << peopleCount << "\n";
        }

        file.close();
        QMessageBox::information(this, "Успешно", "Список пользователей успешно выгружен");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи");
    }
}
