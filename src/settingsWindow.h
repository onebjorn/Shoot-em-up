#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QSlider>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QTextEdit>
#include <json/json.h>
#include <json/writer.h>
#include <fstream>

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
  SettingsWindow()
  {
    QWidget * centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setFixedWidth(600);
    centralWidget->setFixedHeight(800);

    QLabel * comboBoxLabel = new QLabel("Set Difficulty", this);

    m_sliderObstaclesLabel = new QLabel("Obstacles count = No obstacles");
    m_sliderObstaclesLabelHealth = new QLabel("Obstacles health = No obstacles");

    m_sliderAliensLabel = new QLabel("Aliens count = default");
    m_sliderAliensLabelHealth = new QLabel("Aliens health = default");

    m_sliderSpeedLabel = new QLabel("Gun speed = default");

    m_comboBox = new QComboBox(this);
    m_comboBox->addItem("Easy", 0);
    m_comboBox->addItem("Normal", 1);
    m_comboBox->addItem("Hard", 2);
    m_comboBox->addItem("Life", 3);
    m_comboBox->setCurrentIndex(1);
    m_comboBox->adjustSize();

    m_groupBoxObstacles = new QGroupBox("Enable obstacles", this);
    m_groupBoxObstacles->setCheckable(true);
    m_groupBoxObstacles->setChecked(false);

    m_groupBoxSpeed = new QGroupBox("Speed", this);
    m_groupBoxAliens = new QGroupBox("Aliens", this);
    m_groupBoxDifficulty = new QGroupBox("", this);

    m_buttonExit = new QPushButton("Exit", this);
    connect(m_buttonExit, SIGNAL(released()), this, SLOT(close()));

    m_sliderObstacles = new QSlider(Qt::Horizontal, m_groupBoxObstacles);
    m_sliderObstacles->setRange(0, 10);
    connect(m_sliderObstacles, SIGNAL(valueChanged(int)), this, SLOT(SliderObstaclesChanged(int)));

    m_sliderObstaclesHealth = new QSlider(Qt::Horizontal, m_groupBoxObstacles);
    m_sliderObstaclesHealth->setRange(0, 100);
    connect(m_sliderObstaclesHealth, SIGNAL(valueChanged(int)), this, SLOT(SliderObstaclesChangedHealth(int)));

    m_sliderAliens = new QSlider(Qt::Horizontal, m_groupBoxAliens);
    m_sliderAliens->setRange(0, 75);
    connect(m_sliderAliens, SIGNAL(valueChanged(int)), this, SLOT(SliderAliensChanged(int)));

    m_sliderAliensHealth = new QSlider(Qt::Horizontal, m_groupBoxAliens);
    m_sliderAliensHealth->setRange(0, 100);
    connect(m_sliderAliensHealth, SIGNAL(valueChanged(int)), this, SLOT(SliderAliensChangedHealth(int)));

    m_sliderSpeed = new QSlider(Qt::Horizontal, m_groupBoxSpeed);
    m_sliderSpeed->setRange(0, 10);
    connect(m_sliderSpeed, SIGNAL(valueChanged(int)), this, SLOT(SliderSpeedChanged(int)));

    QVBoxLayout *hBoxDifficulty = new QVBoxLayout;
    hBoxDifficulty->addWidget(comboBoxLabel);
    hBoxDifficulty->addWidget(m_comboBox);
    hBoxDifficulty->addStretch(0);
    m_groupBoxDifficulty->setLayout(hBoxDifficulty);
    m_groupBoxDifficulty->setFixedHeight(100);
    m_groupBoxDifficulty->setFixedWidth(400);
    m_groupBoxDifficulty->adjustSize();

    QVBoxLayout *vBoxObstacles = new QVBoxLayout;
    vBoxObstacles->addWidget(m_sliderObstaclesLabel);
    vBoxObstacles->addWidget(m_sliderObstacles);
    vBoxObstacles->addWidget(m_sliderObstaclesLabelHealth);
    vBoxObstacles->addWidget(m_sliderObstaclesHealth);
    vBoxObstacles->addStretch(0);
    m_groupBoxObstacles->setLayout(vBoxObstacles);
    m_groupBoxObstacles->setFixedHeight(200);
    m_groupBoxObstacles->setFixedWidth(400);
    m_groupBoxObstacles->adjustSize();

    QVBoxLayout *vBoxAliens = new QVBoxLayout;
    vBoxAliens->addWidget(m_sliderAliensLabel);
    vBoxAliens->addWidget(m_sliderAliens);
    vBoxAliens->addWidget(m_sliderAliensLabelHealth);
    vBoxAliens->addWidget(m_sliderAliensHealth);
    vBoxAliens->addStretch(0);
    m_groupBoxAliens->setLayout(vBoxAliens);
    m_groupBoxAliens->setFixedHeight(150);
    m_groupBoxAliens->setFixedWidth(400);
    m_groupBoxAliens->adjustSize();

    QVBoxLayout *vBoxSpeed = new QVBoxLayout;
    vBoxSpeed->addWidget(m_sliderSpeed);
    vBoxSpeed->addWidget(m_sliderSpeedLabel);
    vBoxSpeed->addStretch(0);
    m_groupBoxSpeed->setLayout(vBoxSpeed);
    m_groupBoxSpeed->setFixedHeight(100);
    m_groupBoxSpeed->setFixedWidth(400);
    m_groupBoxSpeed->adjustSize();

    m_buttonNewGame = new QPushButton("New Game", this);
    connect(m_buttonNewGame, SIGNAL(released()), this, SLOT(NewGameBtnClick()));

    QGridLayout * layout = new QGridLayout(centralWidget);
    layout->setMargin(10);
    layout->addWidget(m_groupBoxDifficulty, 0, 0);
    layout->addWidget(m_groupBoxObstacles, 1, 0);
    layout->addWidget(m_groupBoxAliens, 2, 0);
    layout->addWidget(m_groupBoxSpeed, 3, 0);
    layout->addWidget(m_buttonNewGame);
    layout->addWidget(m_buttonExit);

  }

public slots:

  void SliderObstaclesChanged(int value) { m_sliderObstaclesLabel->setText("Obstacles count = " + QString::number(value)); }
  void SliderObstaclesChangedHealth(int value) { m_sliderObstaclesLabelHealth->setText("Obstacles health = " + QString::number(value)); }

  void SliderAliensChanged(int value) { m_sliderAliensLabel->setText("Aliens count = " + QString::number(value)); }
  void SliderAliensChangedHealth(int value) { m_sliderAliensLabelHealth->setText("Aliens health = " + QString::number(value)); }

  void SliderSpeedChanged(int val) { m_sliderSpeedLabel->setText("Gun speed = " + QString::number(val)); }

  void NewGameBtnClick() { WriteJson(); } //TODO: переход в главное окно

  /*TODO Запись в файл игровых констант значений из настроек, либо задание этих констант в слотах*/
  /*TODO Выбор сложности определеяет задание все настраиваемых величин пропорционально уровню сложности*/

private:
  QLabel * m_sliderObstaclesLabel = nullptr;
  QLabel * m_sliderSpeedLabel = nullptr;
  QLabel * m_sliderObstaclesLabelHealth = nullptr;
  QLabel * m_sliderAliensLabel = nullptr;
  QLabel * m_sliderAliensLabelHealth = nullptr;

  QPushButton * m_buttonExit = nullptr;
  QPushButton * m_buttonNewGame = nullptr;

  QSlider * m_sliderObstacles = nullptr;
  QSlider * m_sliderObstaclesHealth = nullptr;
  QSlider * m_sliderAliens = nullptr;
  QSlider * m_sliderAliensHealth = nullptr;
  QSlider * m_sliderSpeed = nullptr;

  QComboBox * m_comboBox = nullptr;

  QGroupBox * m_groupBoxObstacles = nullptr;
  QGroupBox * m_groupBoxSpeed = nullptr;
  QGroupBox * m_groupBoxAliens = nullptr;
  QGroupBox * m_groupBoxDifficulty = nullptr;

  void WriteJson()
  {
    Json::Value settings;
    Json::Value resolutions(Json::arrayValue);
    resolutions.append(Json::Value("800x600"));
    resolutions.append(Json::Value("1024x768"));
    resolutions.append(Json::Value("1280x1024"));

    auto & root = settings["Settings"];
    root["resolution"] = resolutions;
    //root["difficulty"] = m_comboBox-> TODO: Combobox selected value

    //TODO: add default settings
    root["aliens count"] = m_sliderAliens->value();
    root["aliens health"] = m_sliderAliensHealth->value();

    root["obstacles count"] = m_sliderObstacles->value();
    root["obstacles health"] = m_sliderObstaclesHealth->value();

    root["gun speed"] = m_sliderSpeed->value();

    std::ofstream settingsFile;
    settingsFile.open("settings.json");
    if (settingsFile.is_open())
      {
        Json::StyledWriter styledWriter;
        settingsFile << styledWriter.write(settings);
        settingsFile.close();
      }
  }
};
