#ifndef EMOTION_MATRIX_PANEL_H
#define EMOTION_MATRIX_PANEL_H

#include <QWidget>

namespace emotion {

class EmotionMatrixPanel : public QWidget {
    Q_OBJECT
public:
    explicit EmotionMatrixPanel(QWidget *parent = nullptr);
};

} // namespace emotion

#endif // EMOTION_MATRIX_PANEL_H
