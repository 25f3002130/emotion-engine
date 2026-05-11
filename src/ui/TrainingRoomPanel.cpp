#include "ui/TrainingRoomPanel.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtCore/QDateTime>

namespace emotion {

TrainingRoomPanel::TrainingRoomPanel(QWidget *parent) : QWidget(parent) {
    setupUI();
    waveTimer = new QTimer(this);
    connect(waveTimer, &QTimer::timeout, this, &TrainingRoomPanel::updateWaveform);
    waveTimer->start(30);
}

void TrainingRoomPanel::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 20, 30, 20);
    mainLayout->setSpacing(20);

    // 1. Header
    mainLayout->addWidget(createHeader());

    // 2. Top Row: Model Selection & Emotion Library
    QHBoxLayout *topRow = new QHBoxLayout();
    topRow->setSpacing(20);
    topRow->addWidget(createModelSelector(), 1);
    topRow->addWidget(createEmotionLibrary(), 2);
    mainLayout->addLayout(topRow);

    // 3. Middle Row: Prerequisites, Waveform, Summary
    QHBoxLayout *midRow = new QHBoxLayout();
    midRow->setSpacing(20);
    midRow->addWidget(createPrerequisites(), 1);
    midRow->addWidget(createWaveformPreview(), 1);
    midRow->addWidget(createSummaryCard(), 1);
    mainLayout->addLayout(midRow);

    // 4. Bottom Row: Terminal
    mainLayout->addWidget(createTerminal());
}

QWidget* TrainingRoomPanel::createHeader() {
    QWidget *header = new QWidget();
    QHBoxLayout *l = new QHBoxLayout(header);
    l->setContentsMargins(0, 0, 0, 10);

    QLabel *title = new QLabel("TRAINING HUB");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #ffffff; letter-spacing: 2px; border:none;");
    l->addWidget(title);
    l->addSpacing(30);

    auto addStat = [&](const QString& label, const QString& val, const QString& color) {
        QLabel *s = new QLabel(QString("<span style='color:#938f99'>%1:</span> <span style='color:%3'>%2</span>").arg(label).arg(val).arg(color));
        s->setStyleSheet("font-size: 10px; font-weight: bold; border:none;");
        l->addWidget(s);
        l->addSpacing(15);
    };

    addStat("NEURAL SYNC", "OPERATIONAL", "#cfbcff");
    addStat("LATENCY", "4MS", "#2dd4bf");
    addStat("MODEL", "SENTI-9", "#cfbcff");

    l->addStretch();
    
    QPushButton *deployBtn = new QPushButton("Deploy Model");
    deployBtn->setFixedSize(110, 32);
    deployBtn->setStyleSheet("background-color: #cfbcff; color: #381e72; border-radius: 4px; font-weight: bold; font-size: 10px; border:none;");
    l->addWidget(deployBtn);

    return header;
}

QFrame* TrainingRoomPanel::createModelSelector() {
    QFrame *f = new QFrame();
    f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; border-radius: 12px; padding: 15px;");
    QVBoxLayout *l = new QVBoxLayout(f);

    QLabel *title = new QLabel("SELECT AI MODEL");
    title->setStyleSheet("font-weight: bold; font-size: 12px; color: #ffffff; border: none; margin-bottom: 5px;");
    l->addWidget(title);
    
    auto createCard = [](const QString& name, const QString& desc, bool active) {
        QFrame *c = new QFrame();
        c->setFixedHeight(55);
        QString border = active ? "1px solid #cfbcff" : "1px solid #25232a";
        c->setStyleSheet(QString("background-color: #1d1b20; border: %1; border-radius: 8px;").arg(border));
        QHBoxLayout *cl = new QHBoxLayout(c);
        
        QLabel *icon = new QLabel("⌬");
        icon->setStyleSheet("font-size: 18px; color: #cfbcff; border: none; background: transparent;");
        cl->addWidget(icon);
        
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *n = new QLabel(name);
        n->setStyleSheet("font-weight: bold; font-size: 11px; color: #ffffff; border: none; background: transparent;");
        QLabel *d = new QLabel(desc);
        d->setStyleSheet("font-size: 8px; color: #938f99; border: none; text-transform: uppercase; background: transparent;");
        vl->addWidget(n);
        vl->addWidget(d);
        cl->addLayout(vl);
        cl->addStretch();
        
        return c;
    };

    l->addWidget(createCard("SENTI-9", "Latest Stable Build", true));
    l->addSpacing(5);
    l->addWidget(createCard("NEURAL-X", "Experimental Alpha", false));
    l->addStretch();
    
    QLabel *readiness = new QLabel("Model Readiness 84%");
    readiness->setStyleSheet("font-size: 9px; color: #938f99; font-weight: bold; border: none;");
    l->addWidget(readiness);
    QProgressBar *pb = new QProgressBar();
    pb->setRange(0, 100);
    pb->setValue(84);
    pb->setFixedHeight(4);
    pb->setTextVisible(false);
    pb->setStyleSheet("QProgressBar { background-color: #25232a; border: none; border-radius: 2px; } QProgressBar::chunk { background-color: #cfbcff; }");
    l->addWidget(pb);

    return f;
}

QFrame* TrainingRoomPanel::createEmotionLibrary() {
    QFrame *f = new QFrame();
    f->setStyleSheet("background-color: transparent; border: none;");
    QVBoxLayout *l = new QVBoxLayout(f);
    l->setContentsMargins(0, 0, 0, 0);

    QLabel *title = new QLabel("Emotion Library");
    title->setStyleSheet("font-weight: bold; font-size: 18px; color: #ffffff; border:none; margin-bottom: 5px;");
    l->addWidget(title);

    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(12);
    
    auto createCard = [](const QString& name, const QString& status, const QString& color) {
        QFrame *c = new QFrame();
        c->setFixedHeight(120);
        c->setStyleSheet(QString("background-color: #141218; border: 1px solid %1; border-radius: 10px;").arg(color));
        QVBoxLayout *cl = new QVBoxLayout(c);
        
        QLabel *tag = new QLabel(status);
        tag->setStyleSheet(QString("color: %1; font-size: 8px; font-weight: bold; text-transform: uppercase; border:none; background:transparent;").arg(color));
        tag->setAlignment(Qt::AlignRight);
        cl->addWidget(tag);
        
        QLabel *n = new QLabel(name);
        n->setStyleSheet("font-size: 15px; font-weight: bold; color: #ffffff; border:none; background:transparent;");
        cl->addWidget(n);
        
        QLabel *d = new QLabel("Recursive emotional resonance and shared perspective.");
        d->setStyleSheet("font-size: 9px; color: #938f99; border:none; background:transparent;");
        d->setWordWrap(true);
        cl->addWidget(d);
        
        return c;
    };

    grid->addWidget(createCard("Calm", "Calibrated", "#2dd4bf"), 0, 0);
    grid->addWidget(createCard("Empathy", "Selecting...", "#cfbcff"), 0, 1);
    grid->addWidget(createCard("Joy", "68% Ready", "#e7c365"), 1, 0);
    grid->addWidget(createCard("Melancholy", "Locked", "#938f99"), 1, 1);

    l->addLayout(grid);
    return f;
}

QFrame* TrainingRoomPanel::createPrerequisites() {
    QFrame *f = new QFrame();
    f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; border-radius: 12px; padding: 15px;");
    QVBoxLayout *l = new QVBoxLayout(f);

    QLabel *title = new QLabel("EMOTION PREREQUISITES: EMPATHY");
    title->setStyleSheet("font-weight: bold; font-size: 9px; color: #938f99; letter-spacing: 1px; border: none;");
    l->addWidget(title);

    auto addRow = [&](const QString& text, const QString& status, bool locked) {
        QWidget *w = new QWidget();
        w->setStyleSheet("background: transparent; border: none;");
        QHBoxLayout *hl = new QHBoxLayout(w);
        hl->setContentsMargins(0, 5, 0, 5);
        QLabel *check = new QLabel(locked ? "🔒" : "✔");
        check->setStyleSheet("color: #cfbcff; font-size: 10px; border: none;");
        QLabel *t = new QLabel(text);
        t->setStyleSheet("font-size: 10px; color: #ffffff; border: none;");
        QLabel *s = new QLabel(status);
        s->setStyleSheet("font-size: 8px; color: #938f99; text-transform: uppercase; border: none;");
        hl->addWidget(check);
        hl->addWidget(t);
        hl->addStretch();
        hl->addWidget(s);
        l->addWidget(w);
    };

    addRow("Recognition", "Calibrated", false);
    addRow("Tone Sensitivity", "Calibrated", false);
    addRow("Abstract Context", "Optional", true);
    
    return f;
}

QFrame* TrainingRoomPanel::createWaveformPreview() {
    QFrame *f = new QFrame();
    f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; border-radius: 12px;");
    QVBoxLayout *l = new QVBoxLayout(f);
    l->setContentsMargins(15, 15, 15, 15);

    QLabel *title = new QLabel("NEURAL WAVEFORM PREVIEW");
    title->setStyleSheet("font-weight: bold; font-size: 9px; color: #938f99; border: none;");
    l->addWidget(title);
    
    waveformCanvas = new QFrame();
    waveformCanvas->setMinimumHeight(80);
    waveformCanvas->setStyleSheet("border: 1px solid rgba(255,255,255,0.05); border-radius: 8px; background-color: #0d0c10;");
    l->addWidget(waveformCanvas);
    
    return f;
}

QFrame* TrainingRoomPanel::createSummaryCard() {
    QFrame *f = new QFrame();
    f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; border-radius: 12px; padding: 15px;");
    QVBoxLayout *l = new QVBoxLayout(f);

    QLabel *msg = new QLabel("Training empathy will utilize 4.2GB of neural memory and is expected to take 14 cycles of reinforcement.");
    msg->setStyleSheet("color: #e7c365; font-size: 10px; border: none;");
    msg->setWordWrap(true);
    l->addWidget(msg);
    
    l->addStretch();
    
    QPushButton *startBtn = new QPushButton("START TRAINING PHASE →");
    startBtn->setFixedHeight(40);
    startBtn->setStyleSheet("background-color: #cfbcff; color: #381e72; border-radius: 6px; font-weight: bold; border:none; font-size: 10px;");
    l->addWidget(startBtn);

    return f;
}

QFrame* TrainingRoomPanel::createTerminal() {
    QFrame *f = new QFrame();
    f->setFixedHeight(120);
    f->setStyleSheet("background-color: #0d0c10; border: 1px solid #25232a; border-radius: 8px;");
    QVBoxLayout *l = new QVBoxLayout(f);
    l->setContentsMargins(10, 5, 10, 5);

    terminalOutput = new QTextEdit();
    terminalOutput->setReadOnly(true);
    terminalOutput->setStyleSheet("background-color: transparent; border: none; color: #2dd4bf; font-family: 'JetBrains Mono', monospace; font-size: 9px;");
    
    QString ts = QDateTime::currentDateTime().toString("hh:mm:ss");
    terminalOutput->append(QString("<span style='color:#938f99'>[%1]</span> <span style='color:#cfbcff'>[SYSTEM]</span> SENTI-9 kernel verified. Handshake success.").arg(ts));
    terminalOutput->append(QString("<span style='color:#938f99'>[%1]</span> <span style='color:#2dd4bf'>[NEURAL]</span> Pre-requisite check for 'Empathy' initiated...").arg(ts));
    terminalOutput->append(QString("<span style='color:#938f99'>[%1]</span> <span style='color:#2dd4bf'>[NEURAL]</span> Recognition module: <span style='color:#ffffff'>OPTIMAL (0.992 fidelity)</span>").arg(ts));
    terminalOutput->append(QString("<span style='color:#938f99'>[%1]</span> <span style='color:#e7c365'>[WAIT]</span> Awaiting user initialization signal...").arg(ts));

    l->addWidget(terminalOutput);
    return f;
}

void TrainingRoomPanel::updateWaveform() {
    waveOffset += 0.1f;
    update();
}

void TrainingRoomPanel::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dynamic coordinate mapping
    QPoint globalPos = waveformCanvas->mapTo(this, QPoint(0, 0));
    QRect rect(globalPos, waveformCanvas->size());

    painter.setPen(QPen(QColor("#cfbcff"), 2));
    
    QPainterPath path;
    int centerY = rect.center().y();
    path.moveTo(rect.left(), centerY);
    
    for (int x = rect.left(); x < rect.right(); ++x) {
        float y = centerY + std::sin((x * 0.05f) + waveOffset) * 15.0f;
        path.lineTo(x, y);
    }
    painter.drawPath(path);

    painter.setPen(QPen(QColor(207, 188, 255, 60), 1));
    QPainterPath path2;
    path2.moveTo(rect.left(), centerY);
    for (int x = rect.left(); x < rect.right(); ++x) {
        float y = centerY + std::sin((x * 0.03f) - waveOffset * 0.5f) * 12.0f;
        path2.lineTo(x, y);
    }
    painter.drawPath(path2);
}

} // namespace emotion
