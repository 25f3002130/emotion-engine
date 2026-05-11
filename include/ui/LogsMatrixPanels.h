#ifndef LOGS_MATRIX_PANELS_H
#define LOGS_MATRIX_PANELS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>

namespace emotion {

class EvolutionLogsPanel : public QWidget {
    Q_OBJECT
public:
    EvolutionLogsPanel(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *l = new QVBoxLayout(this);
        QLabel *title = new QLabel("EVOLUTION LOGS");
        title->setStyleSheet("font-size: 20px; font-weight: bold; color: #e6e0e9;");
        l->addWidget(title);
        
        QTableWidget *t = new QTableWidget(5, 4, this);
        t->setHorizontalHeaderLabels({"Timestamp", "Model", "Target", "Status"});
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->setStyleSheet("background-color: #1d1b20; color: #e6e0e9;");
        l->addWidget(t);
    }
};

class EmotionMatrixPanel : public QWidget {
    Q_OBJECT
public:
    EmotionMatrixPanel(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *l = new QVBoxLayout(this);
        QLabel *title = new QLabel("EMOTION MATRIX");
        title->setStyleSheet("font-size: 20px; font-weight: bold; color: #e6e0e9;");
        l->addWidget(title);
        
        l->addWidget(new QLabel("Neural Heatmap Visualization Placeholder"));
        l->addStretch();
    }
};

} // namespace emotion

#endif // LOGS_MATRIX_PANELS_H
