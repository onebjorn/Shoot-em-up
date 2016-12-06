#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include "textured_rect.hpp"
#include <array>
#include <list>
#include "game/gameEntity.h"
#include "game/space.h"
#include "game/gun.h"

class MainWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:

  GLWidget(MainWindow * mw, QColor const & background);
  ~GLWidget();

protected:
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initializeGL() override;

  void Update(float elapsedSeconds);
  void UpdateGun(float elapsedSeconds);
  void UpdateAliens(float elapsedSeconds);
  void UpdateBullets(float elapsedSeconds);

  void Render();
  void RenderStars();
  void RenderAliens();
  void RenderGun();
  void RenderBullets();
  void DeleteSpace();
  void RenderObstacles();

  void mousePressEvent(QMouseEvent * e) override;
  void mouseDoubleClickEvent(QMouseEvent * e) override;
  void mouseMoveEvent(QMouseEvent * e) override;
  void mouseReleaseEvent(QMouseEvent * e) override;
  void wheelEvent(QWheelEvent * e) override;
  void keyPressEvent(QKeyEvent * e) override;
  void keyReleaseEvent(QKeyEvent * e) override;

private:
  int L2D(int px) const { return px * devicePixelRatio(); }

  QOpenGLTexture * m_alienTexture = nullptr;
  QOpenGLTexture * m_starTexture = nullptr;
  QOpenGLTexture * m_gunTexture = nullptr;
  QOpenGLTexture * m_bulletTexture = nullptr;
  QOpenGLTexture * m_obstacleTexture = nullptr;

  MainWindow * m_mainWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QColor m_background;
  QSize m_screenSize;
  TexturedRect * m_texturedRect = nullptr;

  QVector2D m_position = QVector2D(200, 200);
  std::array<bool, 4> m_directions = {{false, false, false, false}};
  std::list<QOpenGLTexture*> m_texture;
  Space * m_space = new Space;
};
