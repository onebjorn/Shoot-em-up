#pragma once
#include "alien.h"
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
    m_gun = new Gun( w / 2.0f, kGunSizeY * 3.0f);
    m_aliens = new AliensManager();
    m_bullets = new BulletsManager();
    Stars();

    m_obstacles.push_back(Obstacle(w / 8.0f, kGunSizeY * 5.0f));
    m_obstacles.push_back(Obstacle(3.0f * w / 8.0f, 5.0f * kGunSizeY));
    m_obstacles.push_back(Obstacle(5.0f * w / 8.0f, 5.0f * kGunSizeY));
    m_obstacles.push_back(Obstacle(7.0f * w / 8.0f, 5.0f * kGunSizeY));
  }

  Space(Box2D const & spaceBox) { m_box = Box2D(spaceBox); }

  MStars const & GetStars() const { return m_stars.GetStars(); }
  Aliens const & GetAliens() const { return m_aliens->GetAliens(); }
  Bullets const & GetBullets() const { return m_bullets->getBullets(); }

  AliensManager const & GetAliensManager() const { return *m_aliens; }
  BulletsManager const & GetBulletsManager() const { return *m_bullets; }
  Gun & GetGun() { return  *m_gun; }
  vector<Obstacle> const & GetObstacles() const { return m_obstacles; }

  void ChangeGunPosition(float const delta_x, float const delta_y)
  {
      m_gun->SetBox({{delta_x, delta_y},{delta_x, delta_y}});
  }

  void GunShoot()
  {
    m_bullets->AddBullet(m_gun->Shot());
  }

  void CheckAlienHit()
  {
    m_aliens->CheckHit(m_bullets->getBullets());
  }

  void CheckObstacleHit()
  {
    for(auto itObstacle = m_obstacles.begin(); itObstacle != m_obstacles.end(); ++itObstacle)
    {
      for(auto itBullets = m_bullets->getBullets().begin(); itBullets != m_bullets->getBullets().end(); ++itBullets)
      if (itObstacle->ObjectsIntersect(*itObstacle, *itBullets))
      {
        if(itObstacle->GetHealth() <= kBulletDamage) m_obstacles.erase(itObstacle);
        m_bullets->DeleteBullet(itBullets);
      }
    }
  }

  void clear()
  {
    m_aliens->clear();
    m_bullets->clear();
    m_obstacles.erase(m_obstacles.begin(), m_obstacles.end());
  }


  void BulletsMove(float const & deltaX) { m_bullets->BulletsMove(deltaX); }

  void AliensMove(float const deltaX, float const deltaY) { m_aliens->AliensMove(deltaX, deltaY); }



private:

  vector<Obstacle> m_obstacles;
  Gun * m_gun = nullptr;
  AliensManager * m_aliens = nullptr;
  BulletsManager * m_bullets = nullptr;
  Stars m_stars;
};

inline ostream & operator << (ostream & os, Space const & obj)
{
  os << "Space: " << "Сoordinates center = " << "{ "<< obj.GetBox().GetCenter().x() << ", "
     << obj.GetBox().GetCenter().y() << " }, " << endl;
  return os;
}
