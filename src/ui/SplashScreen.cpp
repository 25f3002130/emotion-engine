#include "ui/SplashScreen.h"
#include <QtWidgets/QApplication>
#include <QtGui/QPixmap>
#include <QtCore/Qt>

namespace emotion {

SplashScreen::SplashScreen(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setupUI();
}

void SplashScreen::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QFrame *container = new QFrame(this);
    container->setStyleSheet("background-color: #141218; border: 1px solid #36343a; border-radius: 12px;");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(0, 0, 0, 20);
    containerLayout->setSpacing(0);

    // Custom Title Bar
    QFrame *titleBar = new QFrame(this);
    titleBar->setFixedHeight(30);
    titleBar->setStyleSheet("background-color: #1d1b20; border-top-left-radius: 12px; border-top-right-radius: 12px;");
    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(15, 0, 15, 0);
    QLabel *title = new QLabel("EMOTION ENGINE v4.0.2 // INITIALIZING NEURAL CORE");
    title->setStyleSheet("color: #cbc4d2; font-size: 10px; font-weight: bold; letter-spacing: 1px;");
    titleLayout->addWidget(title);
    containerLayout->addWidget(titleBar);

    // Image Art
    imageLabel = new QLabel(this);
    QPixmap pix("assets/splash.png");
    imageLabel->setPixmap(pix.scaled(600, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    containerLayout->addWidget(imageLabel);

    // Progress Area
    QVBoxLayout *progressArea = new QVBoxLayout();
    progressArea->setContentsMargins(30, 20, 30, 10);
    progressArea->setSpacing(10);

    statusLabel = new QLabel("INITIALIZING...");
    statusLabel->setStyleSheet("color: #cfbcff; font-size: 11px; font-family: 'JetBrains Mono';");
    progressArea->addWidget(statusLabel);

    QHBoxLayout *barRow = new QHBoxLayout();
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(6);
    progressBar->setStyleSheet(
        "QProgressBar { background-color: #1d1b20; border: none; border-radius: 3px; }"
        "QProgressBar::chunk { background-color: #cfbcff; border-radius: 3px; }"
    );
    barRow->addWidget(progressBar);

    percentLabel = new QLabel("0%");
    percentLabel->setFixedWidth(40);
    percentLabel->setStyleSheet("color: #e6e0e9; font-size: 11px; font-weight: bold;");
    percentLabel->setAlignment(Qt::AlignRight);
    barRow->addWidget(percentLabel);
    progressArea->addLayout(barRow);

    disclaimerLabel = new QLabel("NOTE: TRAINING FIDELITY MAY FLUCTUATE BASED ON CURRENT SYSTEM LOAD.");
    disclaimerLabel->setStyleSheet("color: #93000a; font-size: 8px; font-weight: bold;");
    disclaimerLabel->setAlignment(Qt::AlignCenter);
    progressArea->addWidget(disclaimerLabel);

    containerLayout->addLayout(progressArea);

    layout->addWidget(container);
    setFixedSize(602, 720); // Slightly smaller since diagPanel is gone
}

void SplashScreen::setProgress(int value, const QString& status) {
    progressBar->setValue(value);
    percentLabel->setText(QString("%1%").arg(value));
    statusLabel->setText(status.toUpper());
    QApplication::processEvents();
}

void SplashScreen::setHardwareInfo(const QString& cpu, int cores, long ram, int est_time) {
    // Hidden in the new sleek UI, but we could log it or show it in a tooltip
    Q_UNUSED(cpu);
    Q_UNUSED(cores);
    Q_UNUSED(ram);
    Q_UNUSED(est_time);
}

} // namespace emotion
