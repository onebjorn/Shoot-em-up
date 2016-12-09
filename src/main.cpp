#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "settingsWindow.h"
#include "head_window.h"

int main(int argc, char ** argv)
{
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(format);

  HeadWindow hw;
  //hw.showFullScreen();
  hw.show();

  return app.exec();
}
