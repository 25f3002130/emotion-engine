#include "ui/DashboardPanel.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtCore/QString>

namespace emotion {

DashboardPanel::DashboardPanel(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void DashboardPanel::setupUI() {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(25);

    QLabel *header = new QLabel("SYSTEM OVERVIEW");
    header->setStyleSheet("font-size: 22px; font-weight: bold; color: #ffffff; letter-spacing: 2px;");
    mainLayout->addWidget(header);

    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(25);

    // Left Column: System Integrity
    QVBoxLayout *leftCol = new QVBoxLayout();
    leftCol->addWidget(new QLabel("CORE INTEGRITY"));
    
    auto createStatCard = [](const QString& label, const QString& val, const QString& color) {
        QFrame *f = new QFrame();
        f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; border-radius: 12px; padding: 15px;");
        QVBoxLayout *l = new QVBoxLayout(f);
        QLabel *lb = new QLabel(label);
        lb->setStyleSheet("font-size: 10px; color: #938f99; text-transform: uppercase; border:none;");
        QLabel *v = new QLabel(val);
        v->setStyleSheet(QString("font-size: 18px; font-weight: bold; color: %1; border:none;").arg(color));
        l->addWidget(lb);
        l->addWidget(v);
        return f;
    };

    leftCol->addWidget(createStatCard("NEURAL SYNC", "98.4%", "#cfbcff"));
    leftCol->addWidget(createStatCard("EPU LOAD", "42.8 TFLOPS", "#2dd4bf"));
    leftCol->addWidget(createStatCard("STABILITY", "OPTIMAL", "#cfbcff"));
    leftCol->addStretch();
    
    // Right Column: Active Matrix
    QVBoxLayout *rightCol = new QVBoxLayout();
    rightCol->addWidget(new QLabel("EMOTIONAL MATURITY MATRIX"));
    
    QFrame *matrix = new QFrame();
    matrix->setStyleSheet("background-color: #141218; border: 1px solid #25232a; border-radius: 12px;");
    QGridLayout *grid = new QGridLayout(matrix);
    grid->setSpacing(10);
    
    QStringList headers = {"SERENITY", "JOY", "EMPATHY", "RESIL", "CURIOS"};
    for (int i = 0; i < 5; ++i) {
        QLabel *h = new QLabel(headers[i]);
        h->setStyleSheet("font-size: 8px; color: #938f99; border:none;");
        grid->addWidget(h, 0, i + 1);
    }
    
    QStringList models = {"SENTI-9", "VAL-X", "AFF-3"};
    for (int i = 0; i < 3; ++i) {
        QLabel *m = new QLabel(models[i]);
        m->setStyleSheet("font-size: 10px; font-weight: bold; border:none;");
        grid->addWidget(m, i + 1, 0);
        for (int j = 0; j < 5; ++j) {
            QFrame *cell = new QFrame();
            int val = 40 + (rand() % 60);
            cell->setStyleSheet(QString("background-color: rgba(207, 188, 255, %1); border-radius: 4px;").arg(val / 100.0f));
            cell->setFixedSize(40, 40);
            grid->addWidget(cell, i + 1, j + 1);
        }
    }

    rightCol->addWidget(matrix);
    rightCol->addStretch();

    contentLayout->addLayout(leftCol, 1);
    contentLayout->addLayout(rightCol, 2);
    mainLayout->addLayout(contentLayout);
}

} // namespace emotion
