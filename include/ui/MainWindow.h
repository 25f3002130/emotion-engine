#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include "ui/DashboardPanel.h"
#include "ui/TrainingRoomPanel.h"

namespace emotion {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void setupUI();

    QStackedWidget *stack;
    DashboardPanel *dashPanel;
    TrainingRoomPanel *trainPanel;
};

} // namespace emotion

#endif // MAIN_WINDOW_H
