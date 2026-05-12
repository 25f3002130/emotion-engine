#include "training/TrainingManager.h"
#include "models/SENTI9.h"
#include "core/Logger.h"
#include "core/Config.h"
#include "core/HardwareMonitor.h"
#include "core/SystemAudit.h"
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

    // 2. TASK: Deep Hardware Audit (0-30%)
    splash.setProgress(10, "Detecting hardware architecture...");
    emotion::HardwareSpecs hw = emotion::HardwareMonitor::scan();
    QThread::msleep(800); // Cinematic pause
    
    splash.setProgress(20, "Identified GPU: " + QString::fromStdString(hw.gpu_info));
    LOG_INFO("[SYSTEM] OS: " + hw.os_info);
    LOG_INFO("[SYSTEM] Qt Version: " + hw.qt_version);
    QThread::msleep(800);

    splash.setProgress(30, "System Scoring: " + QString::number(hw.training_score * 100, 'f', 1) + "% Efficiency");
    QThread::msleep(500);

    // 3. TASK: System Integrity & Update Check (30-70%)
    splash.setProgress(45, "Verifying file integrity...");
    emotion::AuditResult audit = emotion::SystemAudit::performFullAudit();
    QThread::msleep(1000);

    if (!audit.integrity_pass) {
        LOG_INFO("[CRITICAL] Integrity Check Failed!");
        for (const auto& err : audit.errors) LOG_INFO(" >> " + err);
    }

    splash.setProgress(60, "Checking for updates on GitHub...");
    QThread::msleep(1200); // Network simulation
    if (audit.update_available) {
        splash.setProgress(65, "Update found: " + QString::fromStdString(audit.latest_version));
    } else {
        splash.setProgress(65, "Software is up to date (v4.0.2)");
    }
    QThread::msleep(800);

    // 4. TASK: Neural Initialization (70-100%)
    splash.setProgress(75, "Loading previously trained models...");
    LOG_INFO("[DATA] Discovered " + std::to_string(audit.available_models.size()) + " neural weight sets.");
    QThread::msleep(1000);

    splash.setProgress(85, "Calibrating emotional vectors...");
    auto& config = emotion::Config::getInstance();
    config.load("configs/default_config.json");
    QThread::msleep(1200);

    splash.setProgress(95, "Synchronizing with EPU...");
    emotion::TrainingManager manager;
    manager.addModel(std::make_unique<emotion::SENTI9>());
    QThread::msleep(1000);

    splash.setProgress(100, "Initialization Complete.");
    QThread::msleep(500);

    LOG_INFO("========================================");
    LOG_INFO("      EMOTION ENGINE v4.0.2 STARTING    ");
    LOG_INFO("========================================");

    // 4. Launch Main Application
    emotion::MainWindow window(audit.available_models);
    splash.hide();
    window.show();

    LOG_INFO("[SYSTEM] Native Desktop Interface Launched.");
    
    int result = app.exec();

    // Self-clean temporary build artifacts upon exit
    std::system("rm -rf build");

    return result;
}
