#ifndef DASHBOARD_PANEL_H
#define DASHBOARD_PANEL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QFrame>
#include <QtWidgets/QTextEdit>
#include <QtCore/QTimer>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include "core/SystemAudit.h"

#include "ui/EmotionSelectorDialog.h"

namespace emotion {

class DashboardPanel : public QWidget {
    Q_OBJECT

public:
    DashboardPanel(const std::vector<ModelInfo>& models, QWidget *parent = nullptr);

private slots:
    void updateWaveform();
    void openEmotionSelector();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void setupUI();
    
    // UI Helpers
    QWidget* createHeader();
    QFrame* createModelSelector(const std::vector<ModelInfo>& models);
    QFrame* createEmotionLibrary();
    QFrame* createPrerequisites();
    QFrame* createWaveformPreview();
    QFrame* createSummaryCard();
    QFrame* createTerminal();

    // Components
    QFrame *waveformCanvas;
    QTextEdit *terminalOutput;
    QTimer *waveTimer;
    float waveOffset = 0.0f;
    std::vector<ModelInfo> availableModels;
};

} // namespace emotion

#endif // DASHBOARD_PANEL_H
