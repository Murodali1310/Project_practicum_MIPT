#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dbPath = "/Users/murodali/Projects/BookingManagementSystem/database.db";

    QFileInfo dbFileInfo(dbPath);
    if (!dbFileInfo.exists()) {
        QMessageBox::critical(nullptr, "Ошибка", "Файл базы данных не существует: " + dbPath);
        return -1;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось подключиться к базе данных");
        return -1;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "login TEXT UNIQUE, "
                    "password TEXT)")) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось создать таблицу пользователей");
        return -1;
    }

    QSqlDatabase agentDb = QSqlDatabase::addDatabase("QSQLITE", "AgentConnection");
    agentDb.setDatabaseName(dbPath);

    if (!agentDb.open()) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось подключиться к базе данных агентов");
        return -1;
    }

    QSqlQuery agentQuery(QSqlDatabase::database("AgentConnection"));
    if (!agentQuery.exec("CREATE TABLE IF NOT EXISTS agents ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "login TEXT UNIQUE, "
                         "password TEXT)")) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось создать таблицу агентов");
    }

    MainWindow w;
    w.show();

    return a.exec();
}
