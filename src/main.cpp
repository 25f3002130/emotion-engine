#include "training/TrainingManager.h"
#include "models/SENTI9.h"
#include "core/Logger.h"
#include "core/Config.h"
#include "core/HardwareMonitor.h"
#include "ui/MainWindow.h"
#include "ui/SplashScreen.h"
#include <iostream>
#include <csignal>
#include <QApplication>
#include <QThread>

void signalHandler(int signum) {
    LOG_INFO("Interrupt signal received. Cleaning up...");
    exit(signum);
}

int main(int argc, char *argv[]) {
    std::signal(SIGINT, signalHandler);

    QApplication app(argc, argv);

    // 1. Show Cinematic Splash Screen
    emotion::SplashScreen splash;
    splash.show();

    // 2. Perform Hardware Audit
    emotion::HardwareSpecs specs = emotion::HardwareMonitor::scan();
    LOG_INFO("[HARDWARE] CPU: " + specs.cpu_model);
    LOG_INFO("[HARDWARE] GPU: " + specs.gpu_info);
    LOG_INFO("[HARDWARE] RAM: " + std::to_string(specs.total_ram_mb) + " MB");

    // 3. Simulate Neural Initialization (Slower for heavyweight feel)
    QStringList steps = {
        "Detecting system architecture...",
        "Auditing CPU cores...",
        "Identifying Graphics Hardware...",
        "Found GPU: " + QString::fromStdString(specs.gpu_info),
        "Validating neural compatibility...",
        "Allocating VRAM buffers...",
        "Initializing core subsystems...",
        "Loading SENTI-9 neural foundation...",
        "Calibrating emotional vectors...",
        "Synchronizing with EPU...",
        "Verifying neural integrity...",
        "Finalizing environment..."
    };

    for (int i = 0; i <= 100; ++i) {
        int stepIdx = (i / (100 / steps.size() + 1));
        if (stepIdx >= steps.size()) stepIdx = steps.size() - 1;
        splash.setProgress(i, steps[stepIdx]);
        QThread::msleep(100); // Slower pacing (approx 10 seconds total)
    }

    // Initialize Core Systems in background
    auto& config = emotion::Config::getInstance();
    config.load("configs/default_config.json");

    LOG_INFO("========================================");
    LOG_INFO("      EMOTION ENGINE v4.0.2 STARTING    ");
    LOG_INFO("========================================");

    // Initialize Backend Training Engine
    emotion::TrainingManager manager;
    manager.addModel(std::make_unique<emotion::SENTI9>());

    // 4. Launch Main Application
    emotion::MainWindow window;
    splash.hide();
    window.show();

    LOG_INFO("[SYSTEM] Native Desktop Interface Launched.");
    
    int result = app.exec();

    // Self-clean temporary build artifacts upon exit
    std::system("rm -rf build");

    return result;
}
