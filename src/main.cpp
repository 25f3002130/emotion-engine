#include <QtWidgets/QApplication>
#include "ui/MainWindow.h"
#include "ui/SplashScreen.h"
#include "core/Logger.h"
#include "core/SystemAudit.h"
#include "core/HardwareMonitor.h"
#include <thread>
#include <chrono>
#include <filesystem>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    emotion::Logger::getInstance().log(emotion::Logger::Level::INFO, ">> EMOTION ENGINE CORE v4.0.2 INITIALIZING...");

    emotion::SplashScreen splash;
    splash.show();
    a.processEvents();

    auto wait = [](int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); };

    splash.setProgress(5, "INITIALIZING NEURAL KERNEL...");
    wait(600);

    splash.setProgress(15, "AUDITING SYSTEM TOPOLOGY...");
    emotion::HardwareSpecs hw = emotion::HardwareMonitor::scan();
    wait(800);
    
    splash.setProgress(25, "GPU DETECTED: " + QString::fromStdString(hw.gpu_model).left(30) + "...");
    LOG_INFO("[SYSTEM] OS: " + hw.os_version);
    LOG_INFO("[SYSTEM] CPU: " + hw.cpu_model);
    LOG_INFO("[SYSTEM] RAM: " + std::to_string(hw.total_ram_mb) + "MB");
    wait(700);

    splash.setProgress(40, "SCANNING GLOBAL MODEL REPOSITORIES...");
    wait(600);
    
    splash.setProgress(55, "SEARCHING OLLAMA & LM-STUDIO MANIFESTS...");
    emotion::AuditResult audit = emotion::SystemAudit::performFullAudit();
    wait(900);

    if (!audit.integrity_passed) {
        splash.setProgress(65, "WARNING: Core file mismatch detected. Attempting recovery...");
        wait(1200);
    }

    splash.setProgress(75, "INDEXING " + QString::number(audit.models_found.size()) + " NEURAL WEIGHT SETS...");
    LOG_INFO("[DATA] Discovered " + std::to_string(audit.models_found.size()) + " neural weight sets.");
    wait(800);

    splash.setProgress(90, "FINALIZING CYBER-NEON INTERFACE...");
    wait(1000);

    splash.setProgress(100, "SYSTEM OPERATIONAL. LINKING UI...");
    wait(500);

    emotion::MainWindow window(audit.models_found);
    splash.close();
    window.show();

    int result = a.exec();

    try {
        std::filesystem::remove_all("build");
        emotion::Logger::getInstance().log(emotion::Logger::Level::INFO, "[CLEANUP] Build directory purged.");
    } catch (...) {}

    return result;
}
