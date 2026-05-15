#ifndef DASHBOARD_PANEL_H
#define DASHBOARD_PANEL_H

#include "core/SystemAudit.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <vector>

namespace emotion {

class DashboardPanel : public QWidget {
  Q_OBJECT

public:
  explicit DashboardPanel(const std::vector<ModelInfo> &models,
                          QWidget *parent = nullptr);

private slots:
  void updateWaveform();
  void openEmotionSelector();
  void onStartTraining();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  void setupUI();
  QWidget *createHeader();
  QFrame *createModelSelector(const std::vector<ModelInfo> &models);
  QFrame *createEmotionLibrary();
  QFrame *createPrerequisites();
  QFrame *createWaveformPreview();
  QFrame *createSummaryCard();
  QFrame *createTerminal();

  std::vector<ModelInfo> availableModels;
  QTimer *waveTimer;
  float waveOffset = 0.0f;

  // Dynamic Training State
  bool isTraining;
  int currentSelectedModel = -1;
  QFrame *waveformCanvas;
  QLabel *previewMsg;
  QVBoxLayout *previewMsgLayout;
  QTextEdit *terminalOutput;
};

} // namespace emotion

#endif
