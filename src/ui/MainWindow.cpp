#include "ui/MainWindow.h"
#include "ui/DashboardPanel.h"
#include "ui/TrainingRoomPanel.h"
#include "ui/EvolutionLogsPanel.h"
#include "ui/EmotionMatrixPanel.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QButtonGroup>
#include <QtGui/QIcon>

namespace emotion {

MainWindow::MainWindow(const std::vector<ModelInfo>& models, QWidget *parent) 
    : QMainWindow(parent), discoveredModels(models) {
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
    sidebar->setFixedWidth(260);
    sidebar->setStyleSheet(
        "QWidget { background-color: #0d0c10; border-right: 1px solid #1d1b20; }"
    );
    QVBoxLayout *sideLayout = new QVBoxLayout(sidebar);
    sideLayout->setContentsMargins(15, 40, 15, 30);
    sideLayout->setSpacing(8);

    // Logo Section
    QLabel *logo = new QLabel("EMOTION ENGINE");
    logo->setStyleSheet("font-weight: 900; font-size: 22px; color: #ffffff; letter-spacing: 2px; margin-bottom: 0px;");
    sideLayout->addWidget(logo);
    QLabel *version = new QLabel("V4.0.2 OPERATIONAL");
    version->setStyleSheet("font-size: 9px; color: #cfbcff; font-weight: bold; margin-bottom: 30px; letter-spacing: 1px;");
    sideLayout->addWidget(version);

    QButtonGroup *navGroup = new QButtonGroup(this);
    navGroup->setExclusive(true);

    // Enhanced Navigation Buttons
    auto createNavBtn = [this, navGroup](const QString& text, int index) {
        QPushButton *btn = new QPushButton(text);
        btn->setCheckable(true);
        btn->setFixedHeight(50);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
            "QPushButton { text-align: left; padding-left: 20px; border: 1px solid transparent; border-radius: 8px; font-size: 11px; font-weight: bold; color: #938f99; text-transform: uppercase; letter-spacing: 1px; }"
            "QPushButton:hover { background-color: #141218; color: #ffffff; border: 1px solid #25232a; }"
            "QPushButton:checked { background-color: #1d1b20; color: #cfbcff; border: 1px solid rgba(207, 188, 255, 0.2); }"
        );
        connect(btn, &QPushButton::clicked, [this, index]() { stack->setCurrentIndex(index); });
        navGroup->addButton(btn);
        return btn;
    };

    QPushButton *dashBtn = createNavBtn("⊞ Dashboard", 0);
    dashBtn->setChecked(true);
    sideLayout->addWidget(dashBtn);
    
    sideLayout->addWidget(createNavBtn("⌬ Training Room", 1));
    sideLayout->addWidget(createNavBtn("📊 Evolution Logs", 2));
    sideLayout->addWidget(createNavBtn("💠 Emotion Matrix", 3));
    
    sideLayout->addStretch();

    // Initialize Button Overhaul
    QPushButton *initBtn = new QPushButton("INITIALIZE TRAINING");
    initBtn->setFixedHeight(45);
    initBtn->setStyleSheet(
        "QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #cfbcff, stop:1 #b69df8); color: #381e72; border-radius: 8px; font-weight: 900; font-size: 11px; letter-spacing: 1px; border: none; }"
        "QPushButton:hover { background-color: #eaddff; }"
        "QPushButton:pressed { background-color: #b69df8; }"
    );
    sideLayout->addWidget(initBtn);
    
    sideLayout->addSpacing(25);
    
    auto createInProgBtn = [&](const QString& text) {
        QLabel *l = new QLabel(text);
        l->setStyleSheet("color: #49454f; font-size: 10px; font-weight: bold; text-transform: uppercase; padding-left: 20px; letter-spacing: 1px;");
        return l;
    };
    
    sideLayout->addWidget(createInProgBtn("⚙ Neural Settings [In Progress]"));
    sideLayout->addWidget(createInProgBtn("⌨ API Access [In Progress]"));

    mainLayout->addWidget(sidebar);

    // --- CONTENT AREA ---
    stack = new QStackedWidget();
    dashPanel = new DashboardPanel(discoveredModels);
    trainPanel = new TrainingRoomPanel(discoveredModels);
    evolutionPanel = new EvolutionLogsPanel();
    matrixPanel = new EmotionMatrixPanel();
    
    stack->addWidget(dashPanel);
    stack->addWidget(trainPanel);
    stack->addWidget(evolutionPanel);
    stack->addWidget(matrixPanel);
    stack->setCurrentIndex(0);

    mainLayout->addWidget(stack);
}

} // namespace emotion
