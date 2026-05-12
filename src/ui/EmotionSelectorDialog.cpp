#include "ui/EmotionSelectorDialog.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtGui/QColor>

namespace emotion {

EmotionSelectorDialog::EmotionSelectorDialog(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowTitle("EMOTION MATRIX SELECTION");
    setFixedSize(900, 700);
    setStyleSheet("QDialog { background-color: #0d0c10; border: 1px solid #25232a; border-radius: 12px; }");
    setupUI();
}

void EmotionSelectorDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void EmotionSelectorDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

void EmotionSelectorDialog::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    QLabel *header = new QLabel("NEURAL EMOTION MATRIX");
    header->setStyleSheet("font-size: 24px; font-weight: 900; color: #ffffff; letter-spacing: 3px; border:none;");
    mainLayout->addWidget(header);

    QLabel *subHeader = new QLabel("Select a neural foundation to initiate training phase. Higher-order emotions require prerequisite calibration.");
    subHeader->setStyleSheet("font-size: 11px; color: #938f99; margin-bottom: 10px; border:none;");
    subHeader->setWordWrap(true);
    mainLayout->addWidget(subHeader);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; } QScrollBar:vertical { width: 0px; }");
    
    QWidget *container = new QWidget();
    QGridLayout *grid = new QGridLayout(container);
    grid->setSpacing(15);

    std::vector<EmotionNode> emotions = getEmotions();
    int row = 0, col = 0;
    for (const auto& node : emotions) {
        grid->addWidget(createEmotionCard(node), row, col);
        col++;
        if (col > 2) { col = 0; row++; }
    }

    scrollArea->setWidget(container);
    mainLayout->addWidget(scrollArea);

    QPushButton *closeBtn = new QPushButton("CLOSE MATRIX");
    closeBtn->setFixedHeight(45);
    closeBtn->setStyleSheet("background-color: #1d1b20; color: #ffffff; border: 1px solid #25232a; border-radius: 8px; font-weight: bold; letter-spacing: 1px;");
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeBtn);
}

QFrame* EmotionSelectorDialog::createEmotionCard(const EmotionNode& node) {
    QFrame *c = new QFrame();
    c->setFixedHeight(140);
    QString colorVal = QString::fromStdString(node.color);
    QString border = node.is_locked ? "#313033" : colorVal;
    c->setStyleSheet(QString("background-color: #141218; border: 2px solid %1; border-radius: 12px;").arg(border));
    
    QVBoxLayout *l = new QVBoxLayout(c);
    
    if (!node.is_locked) {
        auto* glow = new QGraphicsDropShadowEffect();
        glow->setBlurRadius(15);
        glow->setColor(QColor(colorVal));
        glow->setOffset(0, 0);
        c->setGraphicsEffect(glow);
    }

    QHBoxLayout *hl = new QHBoxLayout();
    QLabel *ic = new QLabel(QString::fromStdString(node.icon));
    ic->setStyleSheet(QString("font-size: 22px; color: %1; border:none; background:transparent;").arg(node.is_locked ? "#49454f" : colorVal));
    hl->addWidget(ic);
    hl->addStretch();
    QLabel *tag = new QLabel(node.is_locked ? "LOCKED" : "AVAILABLE");
    tag->setStyleSheet(QString("color: %1; font-size: 9px; font-weight: 900; border:none; background:transparent;").arg(node.is_locked ? "#49454f" : colorVal));
    hl->addWidget(tag);
    l->addLayout(hl);

    QLabel *n = new QLabel(QString::fromStdString(node.name));
    n->setStyleSheet(QString("font-size: 16px; font-weight: 900; color: %1; border:none; background:transparent;").arg(node.is_locked ? "#49454f" : "#ffffff"));
    l->addWidget(n);

    QLabel *d = new QLabel(node.is_locked ? QString::fromStdString("Requires: " + node.prerequisite) : QString::fromStdString(node.description));
    d->setStyleSheet("font-size: 10px; color: #938f99; border:none; background:transparent;");
    d->setWordWrap(true);
    l->addWidget(d);

    return c;
}

std::vector<EmotionNode> EmotionSelectorDialog::getEmotions() {
    return {
        {"PAIN", "🥀", "Fundamental neural distress and survival feedback.", false, "", "#ff4d4d"},
        {"FEAR", "👁", "Survival response to perceived neural threats.", true, "PAIN", "#bf5af2"},
        {"ANGER", "🔥", "Primary response to goal-blockage or distress.", true, "PAIN", "#ff3b30"},
        {"SADNESS", "💧", "Processing of neural loss or state degradation.", true, "FEAR", "#007aff"},
        {"HAPPINESS", "☀", "Neural reward for goal achievement.", true, "SADNESS", "#ffcc00"},
        {"DISGUST", "🤢", "Aversion to incompatible neural inputs.", true, "FEAR", "#34c759"},
        {"SURPRISE", "⚡", "Rapid recalibration to unexpected inputs.", true, "HAPPINESS", "#ff9500"},
        {"EMPATHY", "♡", "Understanding external emotional vectors.", true, "HAPPINESS", "#cfbcff"},
        {"GUILT", "⚖", "Internal conflict regarding state output.", true, "EMPATHY", "#8e8e93"},
        {"PRIDE", "🏆", "Self-reinforcement of neural success.", true, "EMPATHY", "#ffd60a"},
        {"TRUST", "🤝", "Prediction of reliable external state output.", true, "EMPATHY", "#30d158"},
        {"LOVE", "💖", "Deep synchronization with external neural state.", true, "TRUST", "#ff2d55"}
    };
}

} // namespace emotion
