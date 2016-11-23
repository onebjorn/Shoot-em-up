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
    AliensManager();
    Stars();
    m_box = Box2D(0.0f, 0.0f, kSpaceSizeX, kSpaceSizeY);
  }

  Space(float const x1, float const y1, float const x2, float const y2) { m_box = Box2D(x1, y1, x2, y2); }

  Space(Point2D const & leftBottom, Point2D const & rightTop) { m_box = Box2D(leftBottom, rightTop); }

  Space(Box2D const & spaceBox) { m_box = Box2D(spaceBox); }

  MStars const & GetStars() const { return m_stars.GetStars(); }

  Aliens const & GetAliens() const { return m_aliens.GetAliens(); }

private:
  vector<Obstacle> m_obstacles;
  Gun gun;
  AliensManager m_aliens;
  BulletsManager m_bullets;
  Stars m_stars;
};

inline ostream & operator << (ostream & os, Space const & obj)
{
  os << "Space: " << "Сoordinates center = " << "{ "<< obj.GetBox().GetCenter().x() << ", "
     << obj.GetBox().GetCenter().y() << " }, " << endl;
  return os;
}
