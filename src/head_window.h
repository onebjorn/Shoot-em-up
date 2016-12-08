#pragma once

#include <QMainWindow>
#include <QShortcut>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QGroupBox>


#include "main_window.hpp"

class MainWindow;

class HeadWindow: public QMainWindow
{
  Q_OBJECT

public:
  HeadWindow();

  //void WriteJson();
  //void ReadJson();

  int const GetAliensCount();
  float const GetAliensHealth();

private slots:
  void NewGame();
  void ContinueGame();
  void Settings();
  void BackToMenu();
  void SaveSettings();

  void SliderObstaclesChanged(int value);
  void SliderObstaclesChangedHealth(int value);

  void SliderAliensChanged(int value);
  void SliderAliensChangedHealth(int value);

  void SliderSpeedChanged(int val);

private:
  QShortcut * m_shortcutGamePause = nullptr;
  // MENU
  bool m_gameStarted = false;
  QPushButton * m_menuNewGameBtn = nullptr;
  QPushButton * m_menuContinueGameBtn = nullptr;
  QPushButton * m_menuSettingsBtn = nullptr;
  QPushButton * m_menuExitBtn = nullptr;
  QGridLayout * m_menuLayout = nullptr;
  QWidget * m_menuWidget = nullptr;
  // SETTINGS
  bool m_settingsChanged = false;
    // button
  QPushButton * m_settingsBackBtn = nullptr;
  QPushButton * m_settingsSaveBtn = nullptr;

  QLabel * m_sliderObstaclesLabel = nullptr;
  QLabel * m_sliderSpeedLabel = nullptr;
  QLabel * m_sliderObstaclesLabelHealth = nullptr;
  QLabel * m_sliderAliensLabel = nullptr;
  QLabel * m_sliderAliensLabelHealth = nullptr;
  QLabel * m_diffLabelCombBox = nullptr;

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

  QVBoxLayout * m_vboxDifficulty = nullptr;
  QVBoxLayout * m_vboxObstacles = nullptr;
  QVBoxLayout * m_vboxAliens = nullptr;
  QVBoxLayout * m_vboxSpeed = nullptr;

    // combobox
  QComboBox * m_cbWindowState = nullptr;
  QComboBox * m_cbWindowSize = nullptr;
  QComboBox * m_cbLanguage = nullptr;
    // gridlayout
  QGridLayout * m_layoutSettings = nullptr;
    // widget
  QWidget * m_widgetSettings = nullptr;
  // GAME
  MainWindow * m_windowGame = nullptr;
  // WINDOW
  QStackedWidget * m_widgetStacked = nullptr;
  QSize m_size;
  QString m_style;

};
