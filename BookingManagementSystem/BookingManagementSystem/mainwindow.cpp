#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::onRegisterButtonClicked);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);

    connect(ui->agentRegisterButton, &QPushButton::clicked, this, &MainWindow::onAgentRegisterButtonClicked);
    connect(ui->agentLoginButton, &QPushButton::clicked, this, &MainWindow::onAgentLoginButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRegisterButtonClicked() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не должны быть пустыми");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка при регистрации: " + query.lastError().text());
    }
}

void MainWindow::onLoginButtonClicked() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не должны быть пустыми");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QMessageBox::information(this, "Успех", "Вход выполнен успешно!");

            mainAppWindow = new MainAppWindow(query.value("login").toString());
            mainAppWindow->show();

            this->close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка запроса: " + query.lastError().text());
    }
}

void MainWindow::onAgentRegisterButtonClicked() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не должны быть пустыми");
        return;
    }

    QSqlQuery query(QSqlDatabase::database("AgentConnection"));
    query.prepare("INSERT INTO agents (login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Регистрация агента прошла успешно!");
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка при регистрации агента: " + query.lastError().text());
    }
}

void MainWindow::onAgentLoginButtonClicked() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не должны быть пустыми");
        return;
    }

    QSqlQuery query(QSqlDatabase::database("AgentConnection"));
    query.prepare("SELECT * FROM agents WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QMessageBox::information(this, "Успех", "Вход агента выполнен успешно!");
            //int agentId = query.value(0).toInt();
            //agentWindow->setAgentId(agentId);
            QString agentName = query.value("login").toString();

            AgentWindow *agentWindow = new AgentWindow(query.value(0).toInt());
            agentWindow->setWindowTitle("Agent Dashboard: " + agentName);
            agentWindow->show();
            this->close();

        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль агента");
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка запроса агента: " + query.lastError().text());
    }
}

