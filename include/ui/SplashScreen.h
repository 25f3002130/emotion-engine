#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

namespace emotion {

class SplashScreen : public QWidget {
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);
    void setProgress(int value, const QString& status);
    void setHardwareInfo(const QString& cpu, int cores, long ram, int est_time);

private:
    void setupUI();

    QLabel *imageLabel;
    QLabel *statusLabel;
    QProgressBar *progressBar;
    QLabel *percentLabel;
    
    // Hardware info labels
    QLabel *cpuLabel;
    QLabel *ramLabel;
    QLabel *timeLabel;
    QLabel *disclaimerLabel;
};

} // namespace emotion

#endif // SPLASH_SCREEN_H
