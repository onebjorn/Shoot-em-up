#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "main_window.hpp"
#include "StartDialog.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(format);

  //MainWindow mw;
  MainWindow SettingsWindow;
  SettingsWindow.show();
  return a.exec();

}
