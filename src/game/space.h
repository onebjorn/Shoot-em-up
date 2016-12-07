#pragma once
#include "alien.h"
#include "obstaclesManager.h"
#include "obstacle.h"
#include "gun.h"
#include "logger.h"
#include "bulletsManager.h"
#include "aliensManager.h"
//#include "gameEntity.h"
#include "stars.h"
#include <ostream>
#include <iostream>

class Space : public GameEntity
{
public:

  Space()
  {
      m_box = Box2D();
      Gun();
      AliensManager();
      Stars();
  }

  Space(float const x1, float const y1, float const x2, float const y2) { m_box = Box2D(x1, y1, x2, y2); }

  Space(Point2D const & leftBottom, Point2D const & rightTop)
  {
    float w = rightTop.x() - leftBottom.x();
    float h = rightTop.y() - leftBottom.y();

    m_box = Box2D(leftBottom, rightTop);
    m_gun = new Gun( w / 2.0f, 5.0f + kGunSizeY / 2.0f);
    m_aliens = new AliensManager();
    m_bullets = new BulletsManager();
    m_bulletsAliens = new BulletsManager();
    m_obstacles = new ObstaclesManager(2, 6);
    Stars();
  }

  Space(Box2D const & spaceBox) { m_box = Box2D(spaceBox); }

  MStars const & GetStars() const { return m_stars.GetStars(); }
  Aliens const & GetAliens() const { return m_aliens->GetAliens(); }
  Bullets const & GetBullets() const { return m_bullets->getBullets(); }
  Bullets const & GetBulletsAliens() const { return m_bulletsAliens->getBullets(); }

  AliensManager const & GetAliensManager() const { return *m_aliens; }
  BulletsManager const & GetBulletsManager() const { return *m_bullets; }
  BulletsManager const & GetBulletsManagerAliens() const { return *m_bulletsAliens; }
  ObstaclesManager const & GetObstaclesManager() const { return *m_obstacles; }
  Gun & GetGun() { return  *m_gun; }


  void ChangeGunPosition(float const delta_x, float const delta_y)
  {
      m_gun->SetBox({{delta_x, delta_y},{delta_x, delta_y}});
  }

  bool AlienIntersetionObstacles()
  {
    for(auto itAliens = m_aliens->GetAliens().begin(); itAliens != m_aliens->GetAliens().end(); ++itAliens)
    {
      for(auto itObstacles = m_obstacles->GetObstacles().begin(); itObstacles != m_obstacles->GetObstacles().end(); ++itObstacles)
      {
        if (GameEntity::ObjectsIntersect(*itAliens, *itObstacles)) { return true; }
      }
    }
    return false;
  }

  void BulletOut()
  {
    for (auto itBullet = m_bullets->getBullets().begin(); itBullet != m_bullets->getBullets().end(); ++itBullet)
    {
      if (itBullet->GetBox().GetCenter().y() > kSpaceSizeY) { m_bullets->DeleteBullet(itBullet); }
    }
    for (auto itBullet = m_bulletsAliens->getBullets().begin(); itBullet != m_bulletsAliens->getBullets().end(); ++itBullet)
    {
      if (itBullet->GetBox().GetCenter().y() < 0.0f) { m_bulletsAliens->DeleteBullet(itBullet); }
    }
  }

  void GunShoot()
  {
    m_bullets->AddBullet(m_gun->Shot());
  }

  bool CheckAliensDeath()
  {
    if (m_aliens->GetAliens().begin() == m_aliens->GetAliens().end()) { return true; }
    return false;
  }

  void AliensShoot()
  {
    m_bulletsAliens->AddBullet(m_aliens->AliensShoot());
  }

  void GunHit()
  {
    m_gun->CheckHit(m_bulletsAliens->getBullets(), * m_gun);
  }

  float GetGunScores()
  {
    return m_gun->GetScores();
  }

  void CheckAlienHit()
  {
    m_aliens->CheckHit(m_bullets->getBullets());
  }

  bool AddScores()
  {
    if(m_aliens->CheckHit(m_bullets->getBullets()) > 0) { return true; }
    return false;
  }

  void NewLevel(int const level)
  {
    delete m_aliens;
    m_aliens = nullptr;
    delete m_bullets;
    m_bullets = nullptr;
    delete m_bulletsAliens;
    m_bulletsAliens = nullptr;
    delete m_obstacles;
    m_obstacles = nullptr;

    /*TODO приращение свойств*/
    m_aliens = new AliensManager();
    m_bullets = new BulletsManager();
    m_bulletsAliens = new BulletsManager();
    m_obstacles = new ObstaclesManager(2, 6);
  }


  void CheckObstacleHit()
  {
    m_obstacles->CheckHit(m_bullets->getBullets());
    m_obstacles->CheckHit(m_bulletsAliens->getBullets());
  }

  void clear()
  {
    m_aliens->clear();
    m_bullets->clear();
    m_obstacles->clear();
  }


  void BulletsMove(float const & deltaX)
  {
    m_bullets->BulletsMove(deltaX);
    m_bulletsAliens->BulletsMove(deltaX);
  }

  void AliensMove(float const deltaX, float const deltaY) { m_aliens->AliensMove(deltaX, deltaY); }



private:

  Gun * m_gun = nullptr;
  ObstaclesManager * m_obstacles = nullptr;
  AliensManager * m_aliens = nullptr;
  BulletsManager * m_bullets = nullptr;
  BulletsManager * m_bulletsAliens = nullptr;
  Stars m_stars;
};

inline ostream & operator << (ostream & os, Space const & obj)
{
  os << "Space: " << "Сoordinates center = " << "{ "<< obj.GetBox().GetCenter().x() << ", "
     << obj.GetBox().GetCenter().y() << " }, " << endl;
  return os;
}
