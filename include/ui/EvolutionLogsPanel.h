#ifndef EVOLUTION_LOGS_PANEL_H
#define EVOLUTION_LOGS_PANEL_H

#include <QWidget>

namespace emotion {

class EvolutionLogsPanel : public QWidget {
    Q_OBJECT
public:
    explicit EvolutionLogsPanel(QWidget *parent = nullptr);
};

} // namespace emotion

#endif // EVOLUTION_LOGS_PANEL_H
