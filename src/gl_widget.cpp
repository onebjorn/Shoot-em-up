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
  m_gunTexture = new QOpenGLTexture(QImage("data/alien.png"));
  m_obstacleTexture= new QOpenGLTexture(QImage("data/alien.png"));
  m_bulletTexture = new QOpenGLTexture(QImage("data/alien.png"));
  m_bulletAlienTexture = new QOpenGLTexture(QImage("data/alien.png"));
  m_heartTexture = new QOpenGLTexture(QImage("data/star.png"));

  m_space = new Space(Point2D{ 0.0, 0.0 }, Point2D{ kSpaceSizeX, kSpaceSizeY });

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
    paintGLNextLevel();
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
    painter.drawText(20, 40, framesPerSecond + " fps");

    QString scores;
    scores.setNum(m_space->GetGunScores() * 1.0, 'f', 2);
    painter.setPen(Qt::white);
    painter.drawText(120, 20, "SCORE: " + scores );

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
  if (!m_gameOver)
  {
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

    Render();

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);

    painter.beginNativePainting();

    QString scores;
    scores.setNum(m_space->GetGun().GetScores());
    painter.drawText(kSpaceSizeX / 2.0f, kSpaceSizeY / 2.0f, "RESULTS: " + scores);
    painter.drawText(kSpaceSizeX / 2.0f, kSpaceSizeY / 2.0f - 50.0f, "GAME OVER");

    QPen pen = QPen(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.end();
  }
}

void GLWidget::NextLevel(int level)
{
  // reset flag
  m_nextLevel = false;

  // new level
  m_space->NewLvlPrepare(level);
  m_time.restart();
}

// PAINTING
void GLWidget::paintGLNextLevel()
{
  if (!m_nextLevel)  // pause with info
  {
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::white);

    QString rate;
    rate.setNum(m_space->GetGun().GetScores());
    painter.drawText(500 / 2 - 150, 500 / 3 - 15, "You current rezult: " + rate);
    painter.drawText(500 / 2 - 180, 500 / 3 + 15, "Aliens destroyed! You win! Level " + QString::number(m_level + 1));
    painter.drawText(500 / 2 - 180, 500 / 3 + 30, "Click Enter to go to the next level! ");
  }
  else              // next level
  {
    NextLevel(++m_level);
    paintGL();
  }
}


void GLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);
}

void GLWidget::UpdateGun(float elapsedSeconds)
{
  // gun speed
  float const kSpeed = 10.0f; // pixels per second.

  // move gun left
  if (m_directions[kLeftDirection])
  {
    if (m_space->GetGun().GetBox().x1() > m_space->GetBox().x1())
    {
      m_space->ChangeGunPosition(- kSpeed * elapsedSeconds, 0.0f);
    }
  }
  // move gun right
  if (m_directions[kRightDirection])
  {
    if (m_space->GetGun().GetBox().x2() < m_space->GetBox().x2())
    {
      m_space->ChangeGunPosition(kSpeed * elapsedSeconds, 0.0f);
    }
  }

  // gun shoot
  if (m_directions[kUpDirection])
  {
    if(m_gunTime > kGunReloadTime)
    {
      m_space->GunShoot();
      m_gunTime = 0.0f;
    }
  }

  if(m_space->GetGun().GetHealth() < 0.0f)
  {
    m_gameOver = true;
  }

}


void GLWidget::UpdateAliens(float elapsedSeconds)
{
  float const kSpeed = 0.6f;
  m_space->AliensMove(kSpeed * elapsedSeconds, kAlienSizeY);
}

void GLWidget::UpdateBullets(float elapsedSeconds)
{
  float const kSpeed = 0.7f;
  m_space->BulletsMove(kSpeed * elapsedSeconds);
}


void GLWidget::Update(float elapsedSeconds)
{ 
  UpdateGun(elapsedSeconds);
  UpdateAliens(elapsedSeconds);
  UpdateBullets(elapsedSeconds);
  m_space->CheckObstacleHit();
  m_space->CheckAlienHit();
  m_space->GunHit();

  if(m_alienTime > kAlienReload)
  {
    m_alienTime = 0.0f;
    m_space->AliensShoot();
  }

}

void GLWidget::RenderAliens()
{
    for (auto it = m_space->GetAliens().begin(); it != m_space->GetAliens().end(); ++it)
    {
      m_texturedRect->Render(m_alienTexture, QVector2D(it->GetBox().GetCenter().x(), it->GetBox().GetCenter().y()), QSize(kAlienSizeX, kAlienSizeY), m_screenSize);
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

void GLWidget::RenderInformation()
{
  for(int i = 0; i < m_space->GetGun().GetHealth() / 10; i++)
  {
    m_texturedRect->Render(m_heartTexture, QVector2D(7 + kHeartSize * (i + 1), kSpaceSizeY - 7 - kHeartSize/ 2), QSize(kHeartSize, kHeartSize), m_screenSize);
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

