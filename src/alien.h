#pragma once
#include "../include/config_stat.h"
#include "gameEntity.h"
#include "bullet.h"

class Alien : public GameEntity
{
public:

  Alien() = default;

  Alien(float const x1, float const y1, float const x2, float const y2)
    : m_alien(x1, y1, x2, y2)
    , m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {}

  Alien(float const x, float const y)
    : m_alien(x - AlienSizeX / 2, y - AlienSizeY / 2 , x + AlienSizeX / 2, y + AlienSizeY / 2)
    , m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {}

  Alien(Point2D const & center)
    : m_alien(center.x() - AlienSizeX / 2, center.y() - AlienSizeY / 2, center.x() + AlienSizeX / 2, center.y() + AlienSizeY / 2)
    , m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {}

  Alien(Point2D const & leftBottom, Point2D const & rightTop, float const health, float const speed)
    : m_alien(leftBottom, rightTop)
    , m_alienHealth(health)
    , m_alienSpeed(speed)
  {}

  Alien( Box2D const & alienBox)
    : m_alien( alienBox.x1(), alienBox.y1(), alienBox.x2(), alienBox.y2())
    , m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {}


  float const & GetHealth() const { return m_alienHealth; }
  float const & GetSpeed() const { return m_alienSpeed; }

  void SetAlienHealth(const float newHelth) { m_alienHealth = newHelth; }
  void SetAlienSpeed( const float newSpeed) { m_alienSpeed = newSpeed; }
  void RemoveAlienHealth(const float deltaHelth) { m_alienHealth -= deltaHelth; }
  void AddAlienSpeed( const float deltaSpeed) { m_alienSpeed += deltaSpeed; }

  bool ObjectsIntersect( Alien const & a, Alien const & b)
  {
    if (a.m_alien.x2() < b.m_alien.x1()) return false;
    if (a.m_alien.x1() > b.m_alien.x2()) return false;
    if (a.m_alien.y2() < b.m_alien.y1()) return false;
    if (a.m_alien.y1() > b.m_alien.y2()) return false;
    return true;
  }

  Box2D const & GetBox() const override { return m_alien; }

private:

  Box2D m_alien = { 0.0f, 0.0f, 0.0f, 0.0f };

  float m_alienHealth = 0.0f;
  float m_alienSpeed = 0.0f;
};
