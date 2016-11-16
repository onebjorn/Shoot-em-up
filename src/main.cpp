#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "settingsWindow.h"
#include "main_window.hpp"

int main(int argc, char ** argv)
{
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow mw;

  SettingsWindow SettingsWindow;
  SettingsWindow.setWindowTitle("Settings");
  SettingsWindow.show();

  return app.exec();
}
