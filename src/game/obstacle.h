#pragma once
#include "gameEntity.h"
#include "../include/config_stat.h"
#include <ostream>
#include "src/game/bulletsManager.h"
#include <iostream>

class Obstacle : public GameEntity
{
public:
  Obstacle() = default;

  Obstacle(float const x, float const y)
    : m_obstacleHealth(kObstacleHealth)
  {
    m_box = Box2D(x - kObstacleSizeX / 2, y - kObstacleSizeY / 2 , x + kObstacleSizeX / 2, y + kObstacleSizeY / 2);
  }

  Obstacle(float const x1, float const y1, float const x2, float const y2)
    : m_obstacleHealth(kObstacleHealth)
  {
    m_box = Box2D(x1, y1, x2, y2);
  }

  Obstacle(Point2D const & leftBottom, Point2D const & rightTop, float health)
    : m_obstacleHealth(health)
  {
    m_box = Box2D(leftBottom, rightTop);
  }

  Obstacle(Point2D const & center)
    : m_obstacleHealth(kObstacleHealth)
  {
    m_box = Box2D(center.x() - kObstacleSizeX / 2, center.y() - kObstacleSizeY / 2, center.x() + kObstacleSizeX / 2, center.y() + kObstacleSizeY / 2);
  }

  Obstacle(Point2D const & leftBottom, Point2D const & rightTop)
    : m_obstacleHealth(kObstacleHealth)
  {
    m_box = Box2D(leftBottom, rightTop);
  }

  Obstacle( Box2D const & obstacleBox)
    : m_obstacleHealth(kObstacleHealth)
  {
    m_box = Box2D(obstacleBox.x1(), obstacleBox.y1(), obstacleBox.x2(), obstacleBox.y2());
  }

  float const & GetHealth() const { return m_obstacleHealth; }

  void RemoveObstacleHealth(const float deltaHealth)
  {
    if ((deltaHealth < 0.0f) || (deltaHealth > 100.0f)) throw invalid_argument("Negative health");
    m_obstacleHealth -= deltaHealth;
  }

  bool CheckHit(Bullets & obj)
  {
    for(auto itAliens = m_obstacles.begin(); itAliens != m_obstacles.end(); ++itAliens)
    {
      for(auto itBullets = obj.begin(); itBullets != obj.end(); ++itBullets)
      if (itAliens->ObjectsIntersect(*itAliens, *itBullets))
      {
        itBullets->Update(*itAliens);
        if(itAliens->GetHealth() <= kBulletDamage) m_obstacles.erase(itAliens);
        obj.erase(itBullets);
        return true;
      }
    }
    return false;
  }

private:

  vector<Obstacle> m_obstacles;
  float m_obstacleHealth = 0.0f;

};

inline ostream & operator << (ostream & os, Obstacle const & obj)
{
  os << "Obstacle: " << "Сoordinates center = " << "{ "<< obj.GetBox().GetCenter().x() << ", "
     << obj.GetBox().GetCenter().y() << " },  Health = " << obj.GetHealth() << endl;
  return os;
}
