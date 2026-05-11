#include "ui/MainWindow.h"
#include "ui/DashboardPanel.h"
#include "ui/TrainingRoomPanel.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QButtonGroup>
#include <QtGui/QIcon>

namespace emotion {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("EMOTION ENGINE v4.0.2");
    resize(1400, 900);
    setupUI();
    
    // Apply Global Dark Theme
    setStyleSheet(
        "QMainWindow { background-color: #0d0c10; }"
        "QWidget { color: #e6e0e9; font-family: 'Inter', 'Segoe UI', sans-serif; }"
        "QLabel { color: #e6e0e9; }"
    );
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // --- SIDEBAR ---
    QWidget *sidebar = new QWidget();
    sidebar->setFixedWidth(240);
    sidebar->setStyleSheet("background-color: #141218; border-right: 1px solid #25232a;");
    QVBoxLayout *sideLayout = new QVBoxLayout(sidebar);
    sideLayout->setContentsMargins(0, 30, 0, 30);
    sideLayout->setSpacing(5);

    // Logo Section
    QLabel *logo = new QLabel("EMOTION ENGINE");
    logo->setStyleSheet("font-weight: bold; font-size: 18px; color: #ffffff; padding: 0 20px; letter-spacing: 1px;");
    sideLayout->addWidget(logo);
    QLabel *version = new QLabel("v4.0.2 Operational");
    version->setStyleSheet("font-size: 10px; color: #938f99; padding: 0 20px 20px 20px;");
    sideLayout->addWidget(version);

    // Group buttons to ensure only one is active at a time
    QButtonGroup *navGroup = new QButtonGroup(this);
    navGroup->setExclusive(true);

    // Navigation Buttons
    auto createNavBtn = [this, navGroup](const QString& text, int index) {
        QPushButton *btn = new QPushButton(text);
        btn->setCheckable(true);
        btn->setFixedHeight(45);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
            "QPushButton { text-align: left; padding-left: 20px; border: none; font-size: 11px; font-weight: bold; color: #938f99; text-transform: uppercase; letter-spacing: 1px; }"
            "QPushButton:hover { background-color: #1d1b20; color: #ffffff; }"
            "QPushButton:checked { background-color: rgba(207, 188, 255, 0.1); color: #cfbcff; border-right: 3px solid #cfbcff; }"
        );
        connect(btn, &QPushButton::clicked, [this, index]() { stack->setCurrentIndex(index); });
        navGroup->addButton(btn);
        return btn;
    };

    sideLayout->addWidget(createNavBtn("⊞ Dashboard", 0));
    QPushButton *trainBtn = createNavBtn("⌬ Training Room", 1);
    trainBtn->setChecked(true); // Default
    sideLayout->addWidget(trainBtn);
    sideLayout->addWidget(createNavBtn("📊 Evolution Logs", 2));
    sideLayout->addWidget(createNavBtn("💠 Emotion Matrix", 3));
    
    sideLayout->addStretch();

    // Bottom Action
    QPushButton *initBtn = new QPushButton("Initialize Training");
    initBtn->setFixedHeight(40);
    initBtn->setContentsMargins(20, 0, 20, 0);
    initBtn->setStyleSheet(
        "QPushButton { background-color: #cfbcff; color: #381e72; border-radius: 4px; font-weight: bold; margin: 0 20px; }"
        "QPushButton:hover { background-color: #eaddff; }"
    );
    sideLayout->addWidget(initBtn);
    
    sideLayout->addSpacing(20);
    sideLayout->addWidget(createNavBtn("⚙ Neural Settings [In Progress]", 4));
    sideLayout->addWidget(createNavBtn("⌨ API Access [In Progress]", 5));

    mainLayout->addWidget(sidebar);

    // --- CONTENT AREA ---
    stack = new QStackedWidget();
    dashPanel = new DashboardPanel();
    trainPanel = new TrainingRoomPanel();
    
    stack->addWidget(dashPanel);
    stack->addWidget(trainPanel);
    stack->setCurrentIndex(1); // Start at Training Hub to match your image

    mainLayout->addWidget(stack);
}

} // namespace emotion
