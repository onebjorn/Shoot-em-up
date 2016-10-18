#pragma once
#include "gameEntity.h"
#include "../include/config_stat.h"

class Obstacle : public GameEntity
{
public:
  Obstacle() = default;

  Obstacle(float const x, float const y)
    : m_obstacleHealth(ObstacleHealth)
  {
    m_box = Box2D(x - ObstacleSizeX / 2, y - ObstacleSizeY / 2 , x + ObstacleSizeX / 2, y + ObstacleSizeY / 2);
  }

  Obstacle(float const x1, float const y1, float const x2, float const y2)
    : m_obstacleHealth(ObstacleHealth)
  {
     m_box = Box2D(x1, y1, x2, y2);
  }

  Obstacle(Point2D const & leftBottom, Point2D const & rightTop, float health)
    : m_obstacleHealth(health)
  {
     m_box = Box2D(leftBottom, rightTop);
  }

  Obstacle(Point2D const & center)
    : m_obstacleHealth(ObstacleHealth)
  {
     m_box = Box2D(center.x() - ObstacleSizeX / 2, center.y() - ObstacleSizeY / 2, center.x() + ObstacleSizeX / 2, center.y() + ObstacleSizeY / 2);
  }

  Obstacle(Point2D const & leftBottom, Point2D const & rightTop)
    : m_obstacleHealth(ObstacleHealth)
  {
    m_box = Box2D(leftBottom, rightTop);
  }

  Obstacle( Box2D const & obstacleBox)
    : m_obstacleHealth(ObstacleHealth)
  {
     m_box = Box2D(obstacleBox.x1(), obstacleBox.y1(), obstacleBox.x2(), obstacleBox.y2());
  }

  float const & GetHealth() const { return m_obstacleHealth; }

  void RemoveObstacleHealth(const float deltaHealth) { m_obstacleHealth -= deltaHealth; }


  ~Obstacle()
  {}

private:
  float m_obstacleHealth = 0.0f;
};
