#pragma once
#include "box2d.h"
#include "../include/config_stat.h"

class Obstacle : public Box2D
{
public:
  Obstacle() = default;

  Obstacle(float const x, float const y)
    : Box2D (x - ObstacleSizeX / 2, y - ObstacleSizeY / 2 , x + ObstacleSizeX / 2, y + ObstacleSizeY / 2)
    , m_obstacleHealth(ObstacleHealth)
  {}

  Obstacle(float const x1, float const y1, float const x2, float const y2)
    : Box2D (x1, y1, x2, y2)
    , m_obstacleHealth(ObstacleHealth)
  {}

  Obstacle(Point2D const & leftBottom, Point2D const & rightTop, float health)
    : Box2D(leftBottom, rightTop)
    , m_obstacleHealth(health)
  {}

  Obstacle(Point2D const & center)
    : Box2D(center.x() - ObstacleSizeX / 2, center.y() - ObstacleSizeY / 2, center.x() + ObstacleSizeX / 2, center.y() + ObstacleSizeY / 2)
    , m_obstacleHealth(ObstacleHealth)
  {}

  Obstacle(Point2D const & leftBottom, Point2D const & rightTop)
    : Box2D(leftBottom, rightTop)
    , m_obstacleHealth(ObstacleHealth)
  {}

  Obstacle( Box2D const & obstacleBox)
    : Box2D( obstacleBox.x1(), obstacleBox.y1(), obstacleBox.x2(), obstacleBox.y2())
    , m_obstacleHealth(ObstacleHealth)
  {}

  float const & GetHealth() const { return m_obstacleHealth; }

  void RemoveObstacleHealth(const float deltaHealth) { m_obstacleHealth -= deltaHealth; }


private:

  /* TODO vector of coordinates*/
  float m_obstacleHealth = 0.0f;

};
