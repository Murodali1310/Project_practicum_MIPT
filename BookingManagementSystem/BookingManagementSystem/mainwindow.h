#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainappwindow.h"
#include "agentwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRegisterButtonClicked();
    void onLoginButtonClicked();
    void onAgentRegisterButtonClicked();
    void onAgentLoginButtonClicked();

private:
    Ui::MainWindow *ui;
    MainAppWindow *mainAppWindow;
    AgentWindow *agentWindow;
};

#endif // MAINWINDOW_H
