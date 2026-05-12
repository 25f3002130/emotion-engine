#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include "ui/DashboardPanel.h"
#include "ui/TrainingRoomPanel.h"
#include "core/SystemAudit.h"

namespace emotion {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(const std::vector<ModelInfo>& models, QWidget *parent = nullptr);

private:
    void setupUI();

    QStackedWidget *stack;
    DashboardPanel *dashPanel;
    TrainingRoomPanel *trainPanel;
    std::vector<ModelInfo> discoveredModels;
};

} // namespace emotion

#endif // MAIN_WINDOW_H
