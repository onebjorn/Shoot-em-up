#include "head_window.h"
#include "gl_widget.hpp"
#include <json/json.h>
#include <json/value.h>
#include <json/writer.h>
#include <fstream>
#include <QSize>
#include <QPalette>
#include <QFont>
#include "../include/config_stat.h"

HeadWindow::HeadWindow()
{
  m_widgetStacked = new QStackedWidget(this);
  this->setCentralWidget(m_widgetStacked);

  m_menuNewGameBtn = new QPushButton("New Game");
  m_menuContinueGameBtn = new QPushButton("Continue game");
  m_menuSettingsBtn = new QPushButton("Settings");
  m_menuExitBtn = new QPushButton("Exit");

  QSize btnsize(400, 100);
  QPalette Palette(palette());

  connect(m_menuNewGameBtn, SIGNAL(clicked(bool)), this, SLOT(NewGame()));
  connect(m_menuContinueGameBtn, SIGNAL(clicked(bool)), this, SLOT(ContinueGame()));
  connect(m_menuSettingsBtn, SIGNAL(clicked(bool)), this, SLOT(Settings()));
  connect(m_menuExitBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
  m_menuNewGameBtn->setFixedSize(btnsize);
  m_menuContinueGameBtn->setFixedSize(btnsize);
  m_menuSettingsBtn->setFixedSize(btnsize);
  m_menuExitBtn->setFixedSize(btnsize);


  m_menuLayout = new QGridLayout;
  m_menuLayout->addWidget(m_menuNewGameBtn, 1, 1, 1, 1);
  m_menuLayout->addWidget(m_menuContinueGameBtn, 2, 1, 1, 1);
  m_menuLayout->addWidget(m_menuSettingsBtn, 3, 1, 1, 1);
  m_menuLayout->addWidget(m_menuExitBtn, 4, 1, 1, 1);

  m_menuWidget = new QWidget(m_widgetStacked);
  Palette.setColor(QPalette::Background, Qt::black);
  m_menuWidget->setAutoFillBackground(true);
  m_menuWidget->setPalette(Palette);
  m_menuWidget->setLayout(m_menuLayout);
  m_menuWidget->setStyleSheet("QPushButton {\n"
                                "font-size: 18pt;\n"
                                "font-weight: bold;\n"
                                "color: #ff0000;}");
  m_menuWidget->adjustSize();

  m_windowGame = new MainWindow(m_widgetStacked, this);

  m_settingsBackBtn = new QPushButton("Back");
  m_settingsSaveBtn = new QPushButton("Save");

  connect(m_settingsBackBtn, SIGNAL(clicked(bool)), this, SLOT(BackToMenu()));
  connect(m_settingsSaveBtn, SIGNAL(clicked(bool)), this, SLOT(SaveSettings()));

  m_diffLabelCombBox = new QLabel("Set Difficulty", this);

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
  connect(m_comboBox, SIGNAL(activated(int)), this, SLOT(ComboboxDifficultyChanged(int)));

  m_groupBoxObstacles = new QGroupBox("Enable obstacles", this);
  m_groupBoxObstacles->setCheckable(true);
  m_groupBoxObstacles->setChecked(false);

  m_groupBoxSpeed = new QGroupBox("Speed", this);
  m_groupBoxAliens = new QGroupBox("Aliens", this);
  m_groupBoxDifficulty = new QGroupBox("", this);

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

  m_vboxDifficulty = new QVBoxLayout;
  m_vboxDifficulty->addWidget(m_diffLabelCombBox);
  m_vboxDifficulty->addWidget(m_comboBox);
  m_vboxDifficulty->addStretch(0);
  m_groupBoxDifficulty->setLayout(m_vboxDifficulty);
  m_groupBoxDifficulty->setFixedHeight(100);
  m_groupBoxDifficulty->setFixedWidth(400);
  m_groupBoxDifficulty->adjustSize();

  m_vboxObstacles = new QVBoxLayout;
  m_vboxObstacles->addWidget(m_sliderObstaclesLabel);
  m_vboxObstacles->addWidget(m_sliderObstacles);
  m_vboxObstacles->addWidget(m_sliderObstaclesLabelHealth);
  m_vboxObstacles->addWidget(m_sliderObstaclesHealth);
  m_vboxObstacles->addStretch(0);
  m_groupBoxObstacles->setLayout(m_vboxObstacles);
  m_groupBoxObstacles->setFixedHeight(200);
  m_groupBoxObstacles->setFixedWidth(400);
  m_groupBoxObstacles->adjustSize();

  m_vboxAliens = new QVBoxLayout;
  m_vboxAliens->addWidget(m_sliderAliensLabel);
  m_vboxAliens->addWidget(m_sliderAliens);
  m_vboxAliens->addWidget(m_sliderAliensLabelHealth);
  m_vboxAliens->addWidget(m_sliderAliensHealth);
  m_vboxAliens->addStretch(0);
  m_groupBoxAliens->setLayout(m_vboxAliens);
  m_groupBoxAliens->setFixedHeight(150);
  m_groupBoxAliens->setFixedWidth(400);
  m_groupBoxAliens->adjustSize();

  m_vboxSpeed = new QVBoxLayout;
  m_vboxSpeed->addWidget(m_sliderSpeed);
  m_vboxSpeed->addWidget(m_sliderSpeedLabel);
  m_vboxSpeed->addStretch(0);
  m_groupBoxSpeed->setLayout(m_vboxSpeed);
  m_groupBoxSpeed->setFixedHeight(100);
  m_groupBoxSpeed->setFixedWidth(400);
  m_groupBoxSpeed->adjustSize();

  m_layoutSettings = new QGridLayout;
  m_layoutSettings->setMargin(10);
  m_layoutSettings->addWidget(m_groupBoxDifficulty, 0, 0);
  m_layoutSettings->addWidget(m_groupBoxObstacles, 1, 0);
  m_layoutSettings->addWidget(m_groupBoxAliens, 2, 0);
  m_layoutSettings->addWidget(m_groupBoxSpeed, 3, 0);
  m_layoutSettings->addWidget(m_settingsSaveBtn, 4, 0);
  m_layoutSettings->addWidget(m_settingsBackBtn, 5, 0);

  m_widgetSettings = new QWidget(m_widgetStacked);
  m_widgetSettings->setLayout(m_layoutSettings);
  m_widgetSettings->hide();

  m_widgetStacked->addWidget(m_menuWidget);
  m_widgetStacked->addWidget(m_widgetSettings);
  m_widgetStacked->addWidget(m_windowGame);
  m_widgetStacked->setCurrentIndex(0);
}

void HeadWindow::ContinueGame()
{
  m_windowGame->m_glWidget->ChangePause();
  m_widgetStacked->setCurrentIndex(2);
}

void HeadWindow::NewGame()
{
  if (! m_settingsChanged) HeadWindow::DefaultSettings();
  //m_gameStarted = true;
  m_widgetStacked->setCurrentIndex(2);
}

void HeadWindow::Settings()
{
  m_widgetStacked->setCurrentIndex(1);
}

void HeadWindow::BackToMenu()
{
  m_widgetStacked->setCurrentIndex(0);
}

void HeadWindow::SaveSettings()
{
  //HeadWindow::WriteJson();
  m_widgetStacked->setCurrentIndex(0);
}

void HeadWindow::SliderAliensChanged(int value)
{
  HeadWindow::DefineAliensMesh(value);
  m_sliderAliensLabel->setText("Aliens count = " + QString::number(value));
  m_settingsChanged = true;
}

void HeadWindow::SliderAliensChangedHealth(int value)
{
  m_windowGame->m_glWidget->kAliensHealth = float(value);
  m_sliderAliensLabelHealth->setText("Aliens health = " + QString::number(value));
  m_settingsChanged = true;
}

void HeadWindow::SliderObstaclesChanged(int value)
{
  m_sliderObstaclesLabel->setText("Obstacles count = " + QString::number(value));
  m_settingsChanged = true;
}

void HeadWindow::SliderObstaclesChangedHealth(int value)
{
  m_sliderObstaclesLabelHealth->setText("Obstacles health = " + QString::number(value));
  m_settingsChanged = true;
}

void HeadWindow::SliderSpeedChanged(int val)
{
  m_windowGame->m_glWidget->kGunspeed = float(val);
  m_sliderSpeedLabel->setText("Gun speed = " + QString::number(val));
  m_settingsChanged = true;
}

void HeadWindow::ComboboxDifficultyChanged(int val)
{
  switch(val)
    {
      case 0:
      {
        m_windowGame->m_glWidget->kAliensSpeed = kAlienSpeed;
        break;
      }
    case 1:
      {
        m_windowGame->m_glWidget->kAliensSpeed = kAlienSpeed * 1.2f;
        break;
      }
    case 2:
      {
        m_windowGame->m_glWidget->kAliensSpeed = kAlienSpeed * 1.5f;
        break;
      }
    case 3:
      {
        m_windowGame->m_glWidget->kAliensSpeed = kAlienSpeed * 2.0f;
        break;
      }
    }
  m_settingsChanged = true;
}

int const HeadWindow::DefineAliensMesh(int value)
{
  if (value % 4 == 0)
    {
      m_windowGame->m_glWidget->kAliensRow = 4;
      m_windowGame->m_glWidget->kAliensColumn = value / 4;
    }
  else if (value % 3 == 0)
    {
      m_windowGame->m_glWidget->kAliensRow = 3;
      m_windowGame->m_glWidget->kAliensColumn = value / 3;
    }
  else if (value % 5 == 0)
    {
      m_windowGame->m_glWidget->kAliensRow = 5;
      m_windowGame->m_glWidget->kAliensColumn = value / 5;
    }
  else
    {
      m_windowGame->m_glWidget->kAliensRow = 2;
      m_windowGame->m_glWidget->kAliensColumn = (value-1) / 2;
    }
}

void HeadWindow::DefaultSettings()
{
  m_windowGame->m_glWidget->kAliensRow = kAliensNumberRow;
  m_windowGame->m_glWidget->kAliensColumn = kAliensNumberColumn;
  m_windowGame->m_glWidget->kAliensHealth = kAlienHealth;
  m_windowGame->m_glWidget->kAliensSpeed = kAlienSpeed;

  m_windowGame->m_glWidget->kGunspeed = kGunSpeed;
}

/*
void HeadWindow::WriteJson()
{
  Json::Value settings;
  Json::Value resolutions(Json::arrayValue);
  resolutions.append(Json::Value("800x600"));
  resolutions.append(Json::Value("1024x768"));
  resolutions.append(Json::Value("1280x1024"));

  auto & root = settings["Settings"];
  root["resolution"] = resolutions;
  root["difficulty"] = m_comboBox->currentIndex();

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

void HeadWindow::ReadJson()
{
  Json::Value settings;
  std::ifstream file;
  file.open("settings.json");
  if (file.is_open())
    {
      file >> settings;
      file.close();
    }

  auto & root = settings["Settings"];
    //FOR RESOLUTION MUTHERFUCKAA!!!!!
  Json::Value & aliensCount = root["aliens count"];
  if (! aliensCount.empty())
    {
      //deliver to aliens
    }
  //else default settings for THIS DIFFICULTY

  Json::Value & aliensHealth = root["aliens health"];
  if (! aliensHealth.empty())
    {
      //same thing
    }
  // else default

  Json::Value & difficulty = root["difficulty"];
  if (! difficulty.empty())
    {
      // where to push?
    }

  Json::Value & gunSpeed = root["gun speed"];
  if (! gunSpeed.empty())
    {
      //deliver to gun
    }
  // else default

  Json::Value & obstaclesCount = root["obstacles count"];
  if (! obstaclesCount.empty())
    {
      // deliver to obstacles
    }
  //else default

  Json::Value & obstaclesHealth = root["obstacles health"];
  if (! obstaclesHealth.empty())
    {
      // same thing
    }
  //else default
}
*/
