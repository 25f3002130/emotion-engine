#ifndef DASHBOARD_PANEL_H
#define DASHBOARD_PANEL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFrame>

namespace emotion {

class DashboardPanel : public QWidget {
    Q_OBJECT

public:
    DashboardPanel(QWidget *parent = nullptr);

private:
    void setupUI();
    QFrame* createModelCard(const QString& name, const QString& status, bool active);
    QFrame* createEmotionCard(const QString& name, const QString& desc, const QString& color);

    QVBoxLayout *mainLayout;
};

} // namespace emotion

#endif // DASHBOARD_PANEL_H
