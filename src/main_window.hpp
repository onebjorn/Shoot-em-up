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

#include "gl_widget.hpp"

class HeadWindow;
class GLWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QStackedWidget * widget, HeadWindow * head);
  GLWidget * m_glWidget = nullptr;
  QStackedWidget * m_stackedWidget = nullptr;
  HeadWindow * m_headWindow = nullptr;
private:
  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;



};
