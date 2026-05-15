#include "ui/EmotionMatrixPanel.h"
#include <QVBoxLayout>
#include <QLabel>

namespace emotion {

EmotionMatrixPanel::EmotionMatrixPanel(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(30, 20, 30, 20);
    l->setSpacing(20);

    QLabel *title = new QLabel("EMOTION MATRIX");
    title->setStyleSheet("font-size: 20px; font-weight: 900; color: #ffffff; letter-spacing: 2px; border:none; background: transparent;");
    l->addWidget(title);
    
    QLabel *placeholder = new QLabel("Neural Heatmap Visualization Placeholder");
    placeholder->setAlignment(Qt::AlignCenter);
    placeholder->setStyleSheet(
        "background-color: #141218; border: 1px solid #25232a; border-radius: 12px; "
        "color: #49454f; font-weight: bold; font-size: 14px;"
    );
    placeholder->setFixedHeight(400);
    l->addWidget(placeholder);

    l->addStretch();
}

} // namespace emotion
