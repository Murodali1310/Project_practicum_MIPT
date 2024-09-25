#ifndef AGENTWINDOW_H
#define AGENTWINDOW_H

#include <QWidget>

namespace Ui {
class AgentWindow;
}

class AgentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AgentWindow(int AgentId, QWidget *parent = nullptr);
    ~AgentWindow();

private slots:
    void onAddServiceButtonClicked();
    void onEditServiceButtonClicked();
    void onDeleteServiceButtonClicked();
    void onExportBookingsButtonClicked();

private:
    int currentAgentId;
    Ui::AgentWindow *ui;
    void loadAgentServices(int agentId);
};

#endif // AGENTWINDOW_H
