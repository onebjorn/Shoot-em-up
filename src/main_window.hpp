#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QDialog>
#include <QStackedWidget>

class HeadWindow;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QStackedWidget * widget, HeadWindow * head);

  QStackedWidget * m_stackedWidget = nullptr;
  HeadWindow * m_headWindow = nullptr;
private:
  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  QOpenGLWidget * m_glWidget = nullptr;


};
