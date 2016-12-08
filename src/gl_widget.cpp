#include "gl_widget.hpp"

#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QGuiApplication>
#include <cmath>

#include <iostream>
#include "main_window.hpp"
#include "game/space.h"


namespace
{

int constexpr kLeftDirection = 0;
int constexpr kRightDirection = 1;
int constexpr kUpDirection = 2;
int constexpr kDownDirection = 3;
int constexpr kPause = 4;

bool IsLeftButton(Qt::MouseButtons buttons)
{
  return buttons & Qt::LeftButton;
}
bool IsLeftButton(QMouseEvent const * const e)
{
  return IsLeftButton(e->button()) || IsLeftButton(e->buttons());
}

bool IsRightButton(Qt::MouseButtons buttons)
{
  return buttons & Qt::RightButton;
}
bool IsRightButton(QMouseEvent const * const e)
{
  return IsRightButton(e->button()) || IsRightButton(e->buttons());
}

} // namespace

GLWidget::GLWidget(MainWindow * SettingsWindow, QColor const & background)
  : m_mainWindow(SettingsWindow)
  , m_background(background)
{
  setMinimumSize(kSpaceSizeX, kSpaceSizeY);
  setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget()
{
  makeCurrent();
  delete m_texturedRect;
  delete m_alienTexture;
  delete m_alienTextureBlood;
  delete m_starTexture;
  delete m_gunTexture;
  delete m_bulletTexture;
  delete m_bulletAlienTexture;
  delete m_obstacleTexture;
  delete m_space;
  delete m_heartTexture;
  DeleteSpace();
  doneCurrent();
}

void GLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  m_texturedRect = new TexturedRect();
  m_texturedRect->Initialize(this);

  m_alienTexture = new QOpenGLTexture(QImage("data/alien.png"));
  m_starTexture = new QOpenGLTexture(QImage("data/star.png"));
  m_gunTexture = new QOpenGLTexture(QImage("data/gun.png"));
  m_obstacleTexture= new QOpenGLTexture(QImage("data/obstacle.png"));
  m_bulletTexture = new QOpenGLTexture(QImage("data/bullet.png"));
  m_bulletAlienTexture = new QOpenGLTexture(QImage("data/bullet.png"));
  m_heartTexture = new QOpenGLTexture(QImage("data/heart.png"));
  m_alienTextureBlood = new QOpenGLTexture(QImage("data/alienBoom.png"));

  m_space = new Space(Point2D{ 0.0, 0.0 }, Point2D{ kSpaceSizeX, kSpaceSizeY }, kAliensNumberRow, kAliensNumberColumn, kSpaceSizeX, kSpaceSizeY, kAlienHealth, kAlienSpeed);

  m_time.start();
}

void GLWidget::paintGL()
{
  if(m_gameOver)
  {
    paintGLGameOver();
  }
  else if(m_nextLevel)
  {
    if(m_level % 10 == 0)
    {
      paintGLNextLevelBoss();
    }
    else
    {
      paintGLNextLevel();
    }
  }
  else
  {
    paintGLGame();
  }
}

void GLWidget::paintGLGame()
{
  int const elapsed = m_time.elapsed();
  Update(elapsed / 1000.0f);

  QPainter painter;
  painter.begin(this);
  painter.beginNativePainting();

  glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Render();

  m_gunTime += elapsed / 1000.0f;
  m_alienTime += elapsed / 1000.0f;

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);


  painter.endNativePainting();

  if (elapsed != 0)
  {
    QString framesPerSecond;
    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
    painter.setPen(Qt::white);
    painter.drawText(400, 20, framesPerSecond + " fps");

    QString score;
    score.setNum(m_space->GetGun().GetScores());
    painter.setPen(Qt::white);
    painter.drawText(250, 20, "Scores: " + score);

    QString level;
    level.setNum(m_level);
    painter.setPen(Qt::white);
    painter.drawText(350, 20,  "Level " + level);

  }
  painter.end();

  if (!(m_frames % 100))
  {
    m_time.start();
    m_frames = 0;
  }
  ++m_frames;
  update();
}

void GLWidget::paintGLGameOver()
{
  m_space->clear();
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::white);

  glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  this->RenderStars();

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);

  painter.beginNativePainting();
  QString scores;
  scores.setNum(m_space->GetGun().GetScores());
  painter.drawText(kSpaceSizeX / 2.0f, kSpaceSizeY / 2.0f, "SCORES: " + scores);
  painter.drawText(kSpaceSizeX / 2.0f, kSpaceSizeY / 2.0f - 50.0f, "GAME OVER");

  painter.end();
}

void GLWidget::paintGLGamePause()
{
  m_space->clear();
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::white);

  glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  this->RenderStars();

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);

  painter.beginNativePainting();

  QString scores;
  scores.setNum(m_space->GetGun().GetScores());
  painter.drawText(kSpaceSizeX / 2.0f, kSpaceSizeY / 2.0f, "SCORES: " + scores);

  painter.end();
}

void GLWidget::NextLevel(int level)
{
  m_nextLevel = false;
  m_space->NewLevel(level, kAliensNumberRow, kAliensNumberColumn, kSpaceSizeX, kSpaceSizeY, kAlienHealth, kAlienSpeed);
  m_time.restart();
}

void GLWidget::paintGLNextLevel()
{
  m_level += 1;
  NextLevel(m_level);
  paintGLGame();
}

void GLWidget::paintGLNextLevelBoss()
{
  m_level += 1;
  NextLevel(m_level);
  paintGLGame();
}

void GLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);
}

void GLWidget::UpdateGun(float elapsedSeconds)
{
  float const kSpeed = kGunSpeed;

  m_space->GunHit();

  if (m_directions[kLeftDirection])
  {
    if (m_space->GetGun().GetBox().x1() > m_space->GetBox().x1())
    {
      m_space->ChangeGunPosition(- kSpeed * elapsedSeconds, 0.0f);
    }
  }

  if (m_directions[kRightDirection])
  {
    if (m_space->GetGun().GetBox().x2() < m_space->GetBox().x2())
    {
      m_space->ChangeGunPosition(kSpeed * elapsedSeconds, 0.0f);
    }
  }

  if (m_directions[kUpDirection])
  {
    if(m_gunTime > kGunReloadTime)
    {
      m_space->GunShoot();
      m_gunTime = 0.0f;
    }
  }

  if(m_space->GetGun().GetHealth() < 0.0f) { m_gameOver = true; }
}

void GLWidget::UpdateAliens(float elapsedSeconds)
{
  float const kSpeed = m_space->GetAliens().front().GetSpeed();
  m_space->AliensMove(kSpeed * elapsedSeconds, kAlienSizeY);
  m_space->CheckAlienHit();
  if(m_space->AddScores())
  {
    m_scores += 10;
    m_space->GetGun().SetScores(10);
  }
  else
  {
    /**/
  }

  if(m_alienTime > kAlienReload)
  {
    m_space->AliensShoot();
    m_alienTime = 0.0f;
  }
}

void GLWidget::UpdateBullets(float elapsedSeconds)
{
  float const kSpeed = 0.7f;
  m_space->BulletsMove(kSpeed * elapsedSeconds);
  m_space->CheckObstacleHit();
//  m_space->BulletOut();
}

void GLWidget::Update(float elapsedSeconds)
{ 
  if(kPause) { m_pause = true; }

  UpdateGun(elapsedSeconds);
  UpdateAliens(elapsedSeconds);
  UpdateBullets(elapsedSeconds);

  if(m_space->CheckAliensDeath()) { m_nextLevel = true; }

  if(m_space->AlienIntersetionObstacles()) { m_gameOver = true; }

  if(m_alienTime > kAlienReload)
  {
    m_space->AliensShoot();
    m_alienTime = 0.0f;
  }

}

void GLWidget::RenderAliens()
{
  if(m_level % 10 == 0)
  {
    for (auto it = m_space->GetAliens().begin(); it != m_space->GetAliens().end(); ++it)
    {
      if(it->GetHealth() < kBulletDamage)
      {
        m_texturedRect->Render(m_alienTextureBlood, QVector2D(it->GetBox().GetCenter().x(), it->GetBox().GetCenter().y()), QSize(kAlienSizeX * 3, kAlienSizeY * 3), m_screenSize);
      }
      m_texturedRect->Render(m_alienTexture, QVector2D(it->GetBox().GetCenter().x(), it->GetBox().GetCenter().y()), QSize(kAlienSizeX * 3, kAlienSizeY * 3), m_screenSize);
    }
  }
  else
  {
    for (auto it = m_space->GetAliens().begin(); it != m_space->GetAliens().end(); ++it)
    {
      if(it->GetHealth() < kBulletDamage)
      {
        m_texturedRect->Render(m_alienTextureBlood, QVector2D(it->GetBox().GetCenter().x(), it->GetBox().GetCenter().y()), QSize(kAlienSizeX, kAlienSizeY), m_screenSize);
      }
      m_texturedRect->Render(m_alienTexture, QVector2D(it->GetBox().GetCenter().x(), it->GetBox().GetCenter().y()), QSize(kAlienSizeX, kAlienSizeY), m_screenSize);
    }
  }
}

void GLWidget::RenderBullets()
{
    for (auto it = m_space->GetBullets().begin(); it != m_space->GetBullets().end(); ++it)
    {
      m_texturedRect->Render(m_bulletTexture, QVector2D(it->GetBox().GetCenter().x(), it->GetBox().GetCenter().y()), QSize(kBulletSizeX, kBulletSizeY), m_screenSize);
    }
    for (auto it = m_space->GetBulletsAliens().begin(); it != m_space->GetBulletsAliens().end(); ++it)
    {
      m_texturedRect->Render(m_bulletAlienTexture, QVector2D(it->GetBox().GetCenter().x(), it->GetBox().GetCenter().y()), QSize(kAlienBulletSizeX, kAlienBulletSizeY), m_screenSize);
    }
}

void GLWidget::RenderObstacles()
{
  for (auto it = m_space->GetObstaclesManager().GetObstacles().begin(); it != m_space->GetObstaclesManager().GetObstacles().end(); ++it)
  {
    m_texturedRect->Render(m_obstacleTexture, QVector2D(it->GetBox().GetCenter().x(), it->GetBox().GetCenter().y()), QSize(kObstacleSizeX, kObstacleSizeY), m_screenSize);
  }
}

void GLWidget::RenderGun()
{
    m_texturedRect->Render(m_gunTexture, QVector2D(m_space->GetGun().GetBox().GetCenter().x(), m_space->GetGun().GetBox().GetCenter().y()), QSize(kGunSizeX, kGunSizeY), m_screenSize);
}

void GLWidget::RenderStars()
{
  for (auto it = m_space->GetStars().begin(); it != m_space->GetStars().end(); ++it)
  {
    float size = 6.0f * sinf(0.001f * m_time.elapsed() - 0.001f * static_cast <float> (rand()));
    m_texturedRect->Render(m_starTexture, QVector2D(it->x() * m_screenSize.width(), it->y() * m_screenSize.height()), QSize(size, size), m_screenSize);
  }
}

void GLWidget::RenderBoom()
{
  for (auto it = m_space->GetStars().begin(); it != m_space->GetStars().end(); ++it)
  {
    float size = 6.0f * sinf(0.001f * m_time.elapsed() - 0.001f * static_cast <float> (rand()));
    m_texturedRect->Render(m_starTexture, QVector2D(it->x() * m_screenSize.width(), it->y() * m_screenSize.height()), QSize(size, size), m_screenSize);
  }
}

void GLWidget::RenderInformation()
{
  for(int i = 0; i < m_space->GetGun().GetHealth() / 10; i++)
  {
    m_texturedRect->Render(m_heartTexture, QVector2D(7 + (kHeartSize + 7) * (i + 1), kSpaceSizeY - 7 - kHeartSize/ 2), QSize(kHeartSize, kHeartSize), m_screenSize);
  }
}

void GLWidget::DeleteSpace()
{
  if (m_space != nullptr)
  {
    m_space->clear();
    delete m_space;
  }
  m_space = nullptr;
}

void GLWidget::mousePressEvent(QMouseEvent * e)
{
  QOpenGLWidget::mousePressEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    // ...
  }
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
  QOpenGLWidget::mouseDoubleClickEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsRightButton(e))
  {
    // ... 
  }
}

void GLWidget::mouseMoveEvent(QMouseEvent * e)
{
  QOpenGLWidget::mouseMoveEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    // ...
  }
}

void GLWidget::mouseReleaseEvent(QMouseEvent * e)
{
  QOpenGLWidget::mouseReleaseEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    // ...
  }
}

void GLWidget::wheelEvent(QWheelEvent * e)
{
  QOpenGLWidget::wheelEvent(e);

  int const delta = e->delta();
  int const px = L2D(e->x());
  int const py = L2D(e->y());
  // ...
}

void GLWidget::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Up)
    m_directions[kUpDirection] = true;
  else if (e->key() == Qt::Key_Down)
    m_directions[kDownDirection] = true;
  else if (e->key() == Qt::Key_Left)
    m_directions[kLeftDirection] = true;
  else if (e->key() == Qt::Key_Right)
    m_directions[kRightDirection] = true;
  else if(e->key() == Qt::Key_Escape)
    m_directions[kPause] = true;

}

void GLWidget::keyReleaseEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Up)
    m_directions[kUpDirection] = false;
  else if (e->key() == Qt::Key_Down)
    m_directions[kDownDirection] = false;
  else if (e->key() == Qt::Key_Left)
    m_directions[kLeftDirection] = false;
  else if (e->key() == Qt::Key_Right)
    m_directions[kRightDirection] = false;
  else if(e->key() == Qt::Key_Escape)
    m_directions[kPause] = false;
}

void GLWidget::Render()
{
  this->RenderAliens();
  this->RenderStars();
  this->RenderGun();
  this->RenderObstacles();
  this->RenderBullets();
  this->RenderInformation();
}

