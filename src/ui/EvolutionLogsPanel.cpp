#include "ui/EvolutionLogsPanel.h"
#include "core/PersistenceEngine.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>

namespace emotion {

EvolutionLogsPanel::EvolutionLogsPanel(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(30, 20, 30, 20);
    l->setSpacing(20);

    QLabel *title = new QLabel("EVOLUTION LOGS");
    title->setStyleSheet("font-size: 20px; font-weight: 900; color: #ffffff; letter-spacing: 2px; border:none; background: transparent;");
    l->addWidget(title);
    
    auto logs = PersistenceEngine::getInstance().getLogs();
    
    QTableWidget *t = new QTableWidget(logs.size(), 4, this);
    t->setHorizontalHeaderLabels({"Timestamp", "Model", "Action", "Result"});
    
    for (int i = 0; i < (int)logs.size(); ++i) {
        t->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(logs[i].timestamp)));
        t->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(logs[i].model_name)));
        t->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(logs[i].action)));
        t->setItem(i, 3, new QTableWidgetItem(QString::number(logs[i].result, 'f', 2)));
    }

    t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    t->setStyleSheet(
        "QTableWidget { background-color: #141218; color: #e6e0e9; border: 1px solid #25232a; border-radius: 8px; }"
        "QHeaderView::section { background-color: #1d1b20; color: #cfbcff; font-weight: bold; border: none; padding: 5px; }"
        "QTableWidget::item { border-bottom: 1px solid #25232a; padding: 5px; }"
    );
    l->addWidget(t);

    l->addStretch();
}

} // namespace emotion
