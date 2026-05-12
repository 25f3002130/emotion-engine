#ifndef EMOTION_SELECTOR_DIALOG_H
#define EMOTION_SELECTOR_DIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <vector>
#include <string>

#include <QtGui/QMouseEvent>

namespace emotion {

struct EmotionNode {
    std::string name;
    std::string icon;
    std::string description;
    bool is_locked;
    std::string prerequisite;
    std::string color;
};

class EmotionSelectorDialog : public QDialog {
    Q_OBJECT

public:
    explicit EmotionSelectorDialog(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void setupUI();
    QFrame* createEmotionCard(const EmotionNode& node);
    std::vector<EmotionNode> getEmotions();
    
    QPoint m_dragPosition;
};

} // namespace emotion

#endif // EMOTION_SELECTOR_DIALOG_H
