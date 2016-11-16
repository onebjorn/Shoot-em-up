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

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
  MainWindow()
  {

    QWidget * centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setFixedWidth(600);
    centralWidget->setFixedHeight(800);

    QLabel * comboBox_label = new QLabel("Set Difficulty", this);
    slider_label = new QLabel("No Data");

    QComboBox * comboBox = new QComboBox(this);
    comboBox->addItem("Easy", 0);
    comboBox->addItem("Normal", 1);
    comboBox->addItem("Hard", 2);
    comboBox->addItem("Life", 3);
    comboBox->setCurrentIndex(1);
    comboBox->adjustSize();

    QGroupBox * groupBox = new QGroupBox("Enable obstacles", this);
    groupBox->setCheckable(true);
    groupBox->setChecked(false);

    QSlider * slider = new QSlider(Qt::Horizontal, groupBox);
    slider->setRange(0, 10);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(&SliderValueChanged(int)));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(slider);
    vbox->addWidget(slider_label);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    QGridLayout * layout = new QGridLayout(centralWidget);
    layout->setMargin(10);
    layout->addWidget(groupBox, 0, 1);
    layout->addWidget(comboBox_label, 1, 0);
    layout->addWidget(comboBox, 1, 1);

  }
public slots:
  void SliderValueChanged(int value)
  {
    slider_label->setText(QString::number(value));
  }
public:
  QLabel * slider_label;
};

