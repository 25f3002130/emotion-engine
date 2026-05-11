#ifndef TRAINING_ROOM_PANEL_H
#define TRAINING_ROOM_PANEL_H

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

namespace emotion {

class TrainingRoomPanel : public QWidget {
    Q_OBJECT

public:
    TrainingRoomPanel(QWidget *parent = nullptr);

private slots:
    void updateWaveform();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void setupUI();
    
    // UI Helpers
    QWidget* createHeader();
    QFrame* createModelSelector();
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
};

} // namespace emotion

#endif // TRAINING_ROOM_PANEL_H
