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

    sliderObstaclesLabel = new QLabel("Obstacles count = No obstacles");
    sliderObstaclesLabelHealth = new QLabel("Obstacles health = No obstacles");

    sliderAliensLabel = new QLabel("Aliens count = default");
    sliderAliensLabelHealth = new QLabel("Aliens health = default");

    sliderSpeedLabel = new QLabel("Gun speed = default");

    QComboBox * comboBox = new QComboBox(this);
    comboBox->addItem("Easy", 0);
    comboBox->addItem("Normal", 1);
    comboBox->addItem("Hard", 2);
    comboBox->addItem("Life", 3);
    comboBox->setCurrentIndex(1);
    comboBox->adjustSize();

    QGroupBox * groupBoxObstacles = new QGroupBox("Enable obstacles", this);
    groupBoxObstacles->setCheckable(true);
    groupBoxObstacles->setChecked(false);

    QGroupBox * groupBoxSpeed = new QGroupBox("Speed", this);
    QGroupBox * groupBoxAliens = new QGroupBox("Aliens", this);
    QGroupBox * groupBoxDifficulty = new QGroupBox("", this);

    QPushButton * buttonExit = new QPushButton("Exit", this);
    connect(buttonExit, SIGNAL(released()), centralWidget, SLOT(close()));


    QSlider * sliderObstacles = new QSlider(Qt::Horizontal, groupBoxObstacles);
    sliderObstacles->setRange(0, 10);
    connect(sliderObstacles, SIGNAL(valueChanged(int)), this, SLOT(SliderObstaclesChanged(int)));

    QSlider * sliderObstaclesHealth = new QSlider(Qt::Horizontal, groupBoxObstacles);
    sliderObstaclesHealth->setRange(0, 100);
    connect(sliderObstaclesHealth, SIGNAL(valueChanged(int)), this, SLOT(SliderObstaclesChangedHealth(int)));

    QSlider * sliderAliens = new QSlider(Qt::Horizontal, groupBoxAliens);
    sliderAliens->setRange(0, 75);
    connect(sliderAliens, SIGNAL(valueChanged(int)), this, SLOT(SliderAliensChanged(int)));

    QSlider * sliderAliensHealth = new QSlider(Qt::Horizontal, groupBoxAliens);
    sliderAliensHealth->setRange(0, 100);
    connect(sliderAliensHealth, SIGNAL(valueChanged(int)), this, SLOT(SliderAliensChangedHealth(int)));

    QSlider * sliderSpeed = new QSlider(Qt::Horizontal, groupBoxSpeed);
    sliderSpeed->setRange(0, 10);
    connect(sliderSpeed, SIGNAL(valueChanged(int)), this, SLOT(SliderSpeedChanged(int)));

    QVBoxLayout *hBoxDifficulty = new QVBoxLayout;
    hBoxDifficulty->addWidget(comboBoxLabel);
    hBoxDifficulty->addWidget(comboBox);
    hBoxDifficulty->addStretch(0);
    groupBoxDifficulty->setLayout(hBoxDifficulty);
    groupBoxDifficulty->setFixedHeight(100);
    groupBoxDifficulty->setFixedWidth(400);
    groupBoxDifficulty->adjustSize();

    QVBoxLayout *vBoxObstacles = new QVBoxLayout;
    vBoxObstacles->addWidget(sliderObstaclesLabel);
    vBoxObstacles->addWidget(sliderObstacles);
    vBoxObstacles->addWidget(sliderObstaclesLabelHealth);
    vBoxObstacles->addWidget(sliderObstaclesHealth);
    vBoxObstacles->addStretch(0);
    groupBoxObstacles->setLayout(vBoxObstacles);
    groupBoxObstacles->setFixedHeight(200);
    groupBoxObstacles->setFixedWidth(400);
    groupBoxObstacles->adjustSize();

    QVBoxLayout *vBoxAliens = new QVBoxLayout;
    vBoxAliens->addWidget(sliderAliensLabel);
    vBoxAliens->addWidget(sliderAliens);
    vBoxAliens->addWidget(sliderAliensLabelHealth);
    vBoxAliens->addWidget(sliderAliensHealth);
    vBoxAliens->addStretch(0);
    groupBoxAliens->setLayout(vBoxAliens);
    groupBoxAliens->setFixedHeight(200);
    groupBoxAliens->setFixedWidth(400);
    groupBoxAliens->adjustSize();

    QVBoxLayout *vBoxSpeed = new QVBoxLayout;
    vBoxSpeed->addWidget(sliderSpeed);
    vBoxSpeed->addWidget(sliderSpeedLabel);
    vBoxSpeed->addStretch(0);
    groupBoxSpeed->setLayout(vBoxSpeed);
    groupBoxSpeed->setFixedHeight(200);
    groupBoxSpeed->setFixedWidth(400);
    groupBoxSpeed->adjustSize();

    QGridLayout * layout = new QGridLayout(centralWidget);
    layout->setMargin(10);
    layout->addWidget(groupBoxDifficulty, 0, 0);
    layout->addWidget(groupBoxObstacles, 1, 0);
    layout->addWidget(groupBoxAliens, 2, 0);
    layout->addWidget(groupBoxSpeed, 3, 0);
    layout->addWidget(buttonExit);
  }

public slots:

  void SliderObstaclesChanged(int value) { sliderObstaclesLabel->setText("Obstacles count = " + QString::number(value)); }
  void SliderObstaclesChangedHealth(int value) { sliderObstaclesLabelHealth->setText("Obstacles health = " + QString::number(value)); }

  void SliderAliensChanged(int value) { sliderAliensLabel->setText("Aliens count = " + QString::number(value)); }
  void SliderAliensChangedHealth(int value) { sliderAliensLabelHealth->setText("Aliens health = " + QString::number(value)); }

  void SliderSpeedChanged(int val) { sliderSpeedLabel->setText("Gun speed = " + QString::number(val)); }

  /*TODO Запись в файл игровых констант значений из настроек, либо задание этих констант в слотах*/
  /*TODO Выбор сложности определеяет задание все настраиваемых величин пропорционально уровню сложности*/
private:
  QLabel * sliderObstaclesLabel = nullptr;
  QLabel * sliderSpeedLabel = nullptr;
  QLabel * sliderObstaclesLabelHealth = nullptr;
  QLabel * sliderAliensLabel = nullptr;
  QLabel * sliderAliensLabelHealth = nullptr;

};
