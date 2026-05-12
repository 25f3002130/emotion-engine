#include "ui/DashboardPanel.h"
#include "core/HardwareMonitor.h"
#include "ui/EmotionSelectorDialog.h"
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

namespace emotion {

// Helper to apply a vibrant glow effect
void applyGlow(QWidget *w, const QColor &color, int strength = 15) {
  auto *glow = new QGraphicsDropShadowEffect(w);
  glow->setBlurRadius(strength);
  glow->setColor(color);
  glow->setOffset(0, 0);
  w->setGraphicsEffect(glow);
}

DashboardPanel::DashboardPanel(const std::vector<ModelInfo> &models,
                               QWidget *parent)
    : QWidget(parent), availableModels(models) {
  setupUI();
  waveTimer = new QTimer(this);
  connect(waveTimer, &QTimer::timeout, this, &DashboardPanel::updateWaveform);
  waveTimer->start(30);

  isTraining = false;
}

void DashboardPanel::setupUI() {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(30, 20, 30, 20);
  mainLayout->setSpacing(20);

  mainLayout->addWidget(createHeader());

  QHBoxLayout *topRow = new QHBoxLayout();
  topRow->setSpacing(20);
  topRow->addWidget(createModelSelector(availableModels), 0);
  topRow->addWidget(createEmotionLibrary(), 2);
  mainLayout->addLayout(topRow);

  QHBoxLayout *midRow = new QHBoxLayout();
  midRow->setSpacing(20);
  midRow->addWidget(createPrerequisites(), 1);
  midRow->addWidget(createWaveformPreview(), 1);
  midRow->addWidget(createSummaryCard(), 1);
  mainLayout->addLayout(midRow);

  mainLayout->addWidget(createTerminal());
}

QWidget *DashboardPanel::createHeader() {
  QWidget *header = new QWidget();
  QHBoxLayout *l = new QHBoxLayout(header);
  l->setContentsMargins(0, 0, 0, 10);

  QLabel *title = new QLabel("TRAINING HUB");
  title->setStyleSheet("font-size: 20px; font-weight: 900; color: #ffffff; "
                       "letter-spacing: 2px; border:none;");
  l->addWidget(title);
  l->addSpacing(30);

  auto addStat = [&](const QString &label, const QString &val,
                     const QString &color) {
    QLabel *s = new QLabel(QString("<span style='color:#938f99'>%1:</span> "
                                   "<span style='color:%3'>%2</span>")
                               .arg(label)
                               .arg(val)
                               .arg(color));
    s->setStyleSheet("font-size: 10px; font-weight: bold; border:none;");
    l->addWidget(s);
    l->addSpacing(15);
  };

  addStat("NEURAL SYNC", "OPERATIONAL", "#cfbcff");
  addStat("LATENCY", "4MS", "#2dd4bf");
  addStat("MODEL",
          availableModels.empty()
              ? "NONE"
              : QString::fromStdString(availableModels[0].name),
          "#cfbcff");

  l->addStretch();

  QPushButton *deployBtn = new QPushButton("Deploy Model");
  deployBtn->setFixedSize(110, 32);
  deployBtn->setStyleSheet(
      "QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
      "stop:0 #cfbcff, stop:1 #b69df8); color: #381e72; border-radius: 8px; "
      "font-weight: 900; font-size: 11px; letter-spacing: 1px; border: none; }"
      "QPushButton:hover { background-color: #eaddff; }"
      "QPushButton:pressed { background-color: #b69df8; }");
  l->addWidget(deployBtn);

  return header;
}

QFrame *
DashboardPanel::createModelSelector(const std::vector<ModelInfo> &models) {
  QFrame *f = new QFrame();
  f->setFixedWidth(420);
  f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; "
                   "border-radius: 12px; padding: 15px;");
  QVBoxLayout *l = new QVBoxLayout(f);
  l->setSpacing(0);

  QLabel *title = new QLabel("Select AI Model");
  title->setStyleSheet(
      "font-weight: bold; font-size: 18px; color: #ffffff; border: none; "
      "margin: 0; padding: 0;");
  l->addWidget(title);

  QLabel *sub = new QLabel("Choose the neural foundation for calibration.");
  sub->setStyleSheet(
      "font-size: 11px; color: #938f99; border: none; margin-bottom: 15px;");
  l->addWidget(sub);

  if (models.empty()) {
    QLabel *empty = new QLabel("No local LLM model available.");
    empty->setStyleSheet(
        "color: #938f99; font-size: 10px; border: none; margin-top: 10px;");
    l->addWidget(empty);

    QString wikiUrl = "https://github.com/25f3002130/emotion-engine/wiki/"
                      "Dowload-LLM-Models-for-your-emotion-engine";
    QLabel *link = new QLabel(
        QString("<a href='%1' style='color: #cfbcff; text-decoration: "
                "none;'>Download models from GitHub Documentation</a>")
            .arg(wikiUrl));
    link->setStyleSheet("font-size: 10px; border: none;");
    link->setOpenExternalLinks(true);
    l->addWidget(link);
  } else {
    auto createCard = [](const ModelInfo &model, bool active) {
      QFrame *c = new QFrame();
      c->setFixedHeight(90);
      c->setCursor(Qt::PointingHandCursor);

      QString border = active ? "2px solid #cfbcff" : "1px solid #2b2930";
      c->setStyleSheet(QString("QFrame { background-color: #1d1b20; border: "
                               "%1; border-radius: 8px; }")
                           .arg(border));

      QHBoxLayout *cl = new QHBoxLayout(c);
      cl->setContentsMargins(15, 0, 15, 0);
      cl->setSpacing(15);

      // Icon Box
      QLabel *ic = new QLabel(model.is_experimental ? "⌬" : "◈");
      ic->setFixedSize(40, 40);
      ic->setAlignment(Qt::AlignCenter);
      ic->setStyleSheet(
          "background-color: #2b2930; border-radius: 8px; color: #cfbcff; "
          "font-size: 22px; border: none;");
      cl->addWidget(ic);

      // Text Area
      QVBoxLayout *tl = new QVBoxLayout();
      tl->setContentsMargins(0, 5, 0, 5);
      tl->setSpacing(2);
      tl->addStretch();

      QLabel *name = new QLabel(QString::fromStdString(model.name).toUpper());
      name->setWordWrap(true);
      name->setStyleSheet("font-weight: bold; font-size: 10px; color: white; "
                          "border: none; background: transparent;");
      tl->addWidget(name);

      QString statusText = model.is_experimental ? "EXPERIMENTAL ALPHA"
                                                 : "LATEST STABLE BUILD";
      if (model.name == "SENTI-9") {
        statusText = "EMOTIONAL INTELLIGENCE";
      }

      QLabel *desc = new QLabel(statusText);
      desc->setStyleSheet("font-size: 9px; color: #938f99; text-transform: "
                          "uppercase; border: none; background: transparent;");
      tl->addWidget(desc);
      tl->addStretch();
      cl->addLayout(tl, 1);

      // Selection Indicator (Radio style)
      QFrame *radio = new QFrame();
      radio->setFixedSize(18, 18);
      QString radioColor = active ? "#cfbcff" : "#49454f";
      QString radioBg = active ? "#cfbcff" : "transparent";
      radio->setStyleSheet(QString("QFrame { border: 2px solid %1; "
                                   "border-radius: 9px; background-color: %2; }")
                               .arg(radioColor)
                               .arg(radioBg));
      cl->addWidget(radio);

      return c;
    };

    for (size_t i = 0; i < models.size(); ++i) {
      l->addWidget(createCard(models[i], i == 0));
    }
  }

  l->addStretch();
  return f;
}

QFrame *DashboardPanel::createEmotionLibrary() {
  QFrame *f = new QFrame();
  f->setStyleSheet("background-color: transparent; border: none;");
  QVBoxLayout *l = new QVBoxLayout(f);
  l->setContentsMargins(0, 0, 0, 0);

  QHBoxLayout *hl = new QHBoxLayout();
  QLabel *title = new QLabel("Emotion Library");
  title->setStyleSheet(
      "font-weight: 900; font-size: 20px; color: #ffffff; border:none;");
  hl->addWidget(title);
  hl->addStretch();

  QPushButton *selBtn = new QPushButton("SELECT EMOTIONS");
  selBtn->setFixedSize(130, 30);
  selBtn->setStyleSheet(
      "background-color: #1d1b20; color: #cfbcff; border: 1px solid #cfbcff; "
      "border-radius: 4px; font-weight: bold; font-size: 9px;");
  connect(selBtn, &QPushButton::clicked, this,
          &DashboardPanel::openEmotionSelector);
  hl->addWidget(selBtn);
  l->addLayout(hl);

  QGridLayout *grid = new QGridLayout();
  grid->setSpacing(12);

  auto createCard = [](const QString &icon, const QString &name,
                       const QString &status, const QString &desc,
                       const QString &colorStr) {
    QFrame *c = new QFrame();
    c->setFixedHeight(130);
    bool locked = (status == "LOCKED");
    QColor baseColor(colorStr);
    c->setStyleSheet(QString("background-color: #0d0c10; border: 3px solid %1; "
                             "border-radius: 12px;")
                         .arg(locked ? "#313033" : colorStr));
    QVBoxLayout *cl = new QVBoxLayout(c);

    if (!locked)
      applyGlow(c, baseColor, 20);

    QHBoxLayout *hl = new QHBoxLayout();
    QLabel *ic = new QLabel(icon);
    ic->setStyleSheet(
        QString(
            "font-size: 20px; color: %1; border:none; background:transparent;")
            .arg(locked ? "#49454f" : colorStr));
    hl->addWidget(ic);
    hl->addStretch();
    QLabel *tag = new QLabel(status);
    tag->setStyleSheet(
        QString("color: %1; font-size: 9px; font-weight: 900; text-transform: "
                "uppercase; border:none; background:transparent;")
            .arg(locked ? "#49454f" : colorStr));
    hl->addWidget(tag);
    cl->addLayout(hl);

    QLabel *n = new QLabel(name);
    n->setStyleSheet(
        QString("font-size: 18px; font-weight: 900; color: %1; border:none; "
                "background:transparent; margin-top: 5px;")
            .arg(locked ? "#49454f" : "#ffffff"));
    cl->addWidget(n);

    QLabel *d = new QLabel(locked ? "Requires Neural Prerequisite." : desc);
    d->setStyleSheet(
        "font-size: 10px; color: #938f99; border:none; background:transparent; "
        "line-height: 1.2; font-weight: 500;");
    d->setWordWrap(true);
    cl->addWidget(d);

    return c;
  };

  grid->addWidget(
      createCard("🥀", "Pain", "PENDING",
                 "Fundamental neural distress and survival feedback.",
                 "#ff4d4d"),
      0, 0);
  grid->addWidget(
      createCard("♡", "Empathy", "LOCKED",
                 "Recursive emotional resonance and shared perspective.",
                 "#bf5af2"),
      0, 1);
  grid->addWidget(createCard("☀", "Joy", "LOCKED",
                             "High-valence, high-arousal positive affectation.",
                             "#ffcc00"),
                  1, 0);
  grid->addWidget(
      createCard("☁", "Melancholy", "LOCKED",
                 "Reflective sadness with a core of aesthetic appreciation.",
                 "#313033"),
      1, 1);

  l->addLayout(grid);
  return f;
}

void DashboardPanel::openEmotionSelector() {
  EmotionSelectorDialog dialog(this);
  dialog.exec();
}

QFrame *DashboardPanel::createPrerequisites() {
  QFrame *f = new QFrame();
  f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; "
                   "border-radius: 12px; padding: 15px;");
  QVBoxLayout *l = new QVBoxLayout(f);

  QLabel *title = new QLabel("⊞  EMOTION PREREQUISITES: EMPATHY");
  title->setStyleSheet(
      "font-weight: 900; font-size: 10px; color: #938f99; letter-spacing: 2px; "
      "border: none; margin-bottom: 10px;");
  l->addWidget(title);

  auto addRow = [&](const QString &icon, const QString &text,
                    const QString &status, const QString &color, bool locked) {
    QFrame *row = new QFrame();
    row->setFixedHeight(45);
    row->setStyleSheet(QString("background-color: #1d1b20; border: none; "
                               "border-radius: 6px; margin-bottom: 2px;"));
    QHBoxLayout *hl = new QHBoxLayout(row);
    hl->setContentsMargins(15, 0, 15, 0);

    QLabel *ic = new QLabel(icon);
    ic->setStyleSheet(QString("color: %1; font-size: 14px; border: none; "
                              "background: transparent;")
                          .arg(color));
    hl->addWidget(ic);

    QLabel *t = new QLabel(text);
    t->setStyleSheet(QString("font-size: 12px; font-weight: 600; color: %1; "
                             "border: none; background: transparent;")
                         .arg(locked ? "#49454f" : "#ffffff"));
    hl->addWidget(t);

    hl->addStretch();

    QLabel *s = new QLabel(status);
    s->setStyleSheet(QString("font-size: 9px; font-weight: 900; color: %1; "
                             "text-transform: uppercase; border: none; "
                             "background: transparent; letter-spacing: 1px;")
                         .arg(locked ? "#49454f" : "#938f99"));
    hl->addWidget(s);

    l->addWidget(row);
  };

  addRow("🔘", "Recognition", "CALIBRATED", "#00ffd5", false);
  addRow("🔘", "Tone Sensitivity", "CALIBRATED", "#00ffd5", false);
  addRow("🔒", "Abstract Context", "OPTIONAL", "#49454f", true);

  return f;
}

QFrame *DashboardPanel::createWaveformPreview() {
  QFrame *f = new QFrame();
  f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; "
                   "border-radius: 12px;");
  QVBoxLayout *l = new QVBoxLayout(f);
  l->setContentsMargins(15, 15, 15, 15);

  QLabel *title = new QLabel("NEURAL WAVEFORM PREVIEW");
  title->setStyleSheet(
      "font-weight: 900; font-size: 9px; color: #938f99; border: none;");
  l->addWidget(title);

  waveformCanvas = new QFrame();
  waveformCanvas->setMinimumHeight(100);
  waveformCanvas->setStyleSheet(
      "border: 1px solid rgba(255,255,255,0.05); border-radius: 8px; "
      "background-color: #0d0c10;");

  previewMsgLayout = new QVBoxLayout(waveformCanvas);
  previewMsg = new QLabel("START TRAINING A MODEL TO\nSEE THE NEURAL PREVIEW");
  previewMsg->setAlignment(Qt::AlignCenter);
  previewMsg->setStyleSheet(
      "color: #49454f; font-weight: 900; font-size: 10px; border: none; "
      "background: transparent; letter-spacing: 1px;");
  previewMsgLayout->addWidget(previewMsg);

  l->addWidget(waveformCanvas);

  return f;
}

QFrame *DashboardPanel::createSummaryCard() {
  QFrame *f = new QFrame();
  f->setStyleSheet("background-color: #141218; border: 1px solid #25232a; "
                   "border-radius: 12px; padding: 15px;");
  QVBoxLayout *l = new QVBoxLayout(f);

  QFrame *infoBox = new QFrame();
  infoBox->setStyleSheet(
      "background-color: rgba(231, 195, 101, 0.05); border: 1px solid #e7c365; "
      "border-radius: 8px; padding: 10px;");
  applyGlow(infoBox, QColor("#e7c365"), 15);
  QHBoxLayout *il = new QHBoxLayout(infoBox);

  QLabel *icon = new QLabel("ⓘ");
  icon->setStyleSheet("color: #e7c365; font-size: 18px; border: none; "
                      "background: transparent; font-weight: bold;");
  il->addWidget(icon);

  HardwareSpecs hw = HardwareMonitor::scan();
  int cycles = 30 - (hw.training_score * 20);
  float memory = 2.0f + (hw.total_ram_mb / 4096.0f);

  QLabel *msg =
      new QLabel(QString("Training empathy will utilize %1GB of neural memory "
                         "and is expected to take %2 cycles of reinforcement.")
                     .arg(QString::number(memory, 'f', 1))
                     .arg(cycles));
  msg->setStyleSheet("color: #e7c365; font-size: 9px; border: none; "
                     "background: transparent; font-weight: 500;");
  msg->setWordWrap(true);
  il->addWidget(msg);

  l->addWidget(infoBox);
  l->addStretch();

  QPushButton *startBtn = new QPushButton("START TRAINING PHASE →");
  startBtn->setFixedHeight(40);
  startBtn->setStyleSheet(
      "background-color: #cfbcff; color: #381e72; border-radius: 6px; "
      "font-weight: bold; border:none; font-size: 10px;");
  connect(startBtn, &QPushButton::clicked, this,
          &DashboardPanel::onStartTraining);
  l->addWidget(startBtn);

  return f;
}

QFrame *DashboardPanel::createTerminal() {
  QFrame *f = new QFrame();
  f->setFixedHeight(120);
  f->setStyleSheet("background-color: #0d0c10; border: 1px solid #25232a; "
                   "border-radius: 8px;");
  QVBoxLayout *l = new QVBoxLayout(f);
  l->setContentsMargins(10, 5, 10, 5);

  terminalOutput = new QTextEdit();
  terminalOutput->setReadOnly(true);
  terminalOutput->setStyleSheet(
      "background-color: transparent; border: none; color: #2dd4bf; "
      "font-family: 'JetBrains Mono', monospace; font-size: 9px;");

  l->addWidget(terminalOutput);
  return f;
}

void DashboardPanel::onStartTraining() {
  if (isTraining)
    return;
  isTraining = true;

  // Clear and pop logs
  terminalOutput->clear();
  QString ts = QDateTime::currentDateTime().toString("hh:mm:ss");

  auto addLog = [&](const QString &type, const QString &msg,
                    const QString &color) {
    terminalOutput->append(QString("<span style='color:#938f99'>[%1]</span> "
                                   "<span style='color:%3'>[%2]</span> %4")
                               .arg(ts)
                               .arg(type)
                               .arg(color)
                               .arg(msg));
  };

  addLog("SYSTEM", "SENTI-9 kernel verified. Handshake success.", "#cfbcff");
  addLog("NEURAL", "Pre-requisite check for 'Pain' initiated...", "#2dd4bf");
  addLog("NEURAL",
         "Recognition module: <span style='color:#ffffff'>OPTIMAL (0.992 "
         "fidelity)</span>",
         "#2dd4bf");
  addLog("SYNC", "Injecting '🥀 PAIN' neural vectors into local LLM weights.",
         "#bf5af2");
  addLog("PROCESS", "Training cycles active. Monitoring hardware telemetry...",
         "#ffcc00");

  // Hide preview message
  previewMsg->hide();
}

void DashboardPanel::updateWaveform() {
  waveOffset += 0.1f;
  update();
}

void DashboardPanel::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QPoint globalPos = waveformCanvas->mapTo(this, QPoint(0, 0));
  QRect rect(globalPos, waveformCanvas->size());

  // Only show waves if training is active
  if (isTraining) {
    painter.setPen(QPen(QColor(207, 188, 255, 180), 2));
  } else {
    painter.setPen(QPen(QColor(207, 188, 255, 30), 1));
  }

  QPainterPath path;
  int centerY = rect.center().y();
  path.moveTo(rect.left(), centerY);

  for (int x = rect.left(); x < rect.right(); ++x) {
    float y = centerY +
              std::sin((x * 0.05f) + waveOffset) * (isTraining ? 15.0f : 5.0f);
    path.lineTo(x, y);
  }
  painter.drawPath(path);
}

} // namespace emotion
