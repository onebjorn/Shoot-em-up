#pragma once
#include "../include/config_stat.h"
#include "gameEntity.h"
#include "bullet.h"

class Alien : public GameEntity
{
public:
  Alien() = default;

  Alien(float const x1, float const y1, float const x2, float const y2)
    : m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {
    m_box = Box2D(x1, y1, x2, y2);
  }

  Alien(float const x, float const y)
    : m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {
    m_box = Box2D(x - AlienSizeX / 2, y - AlienSizeY / 2 , x + AlienSizeX / 2, y + AlienSizeY / 2);
  }

  Alien(Point2D const & center)
    : m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {
     m_box = Box2D(center.x() - AlienSizeX / 2, center.y() - AlienSizeY / 2, center.x() + AlienSizeX / 2, center.y() + AlienSizeY / 2);
  }

  Alien(Point2D const & leftBottom, Point2D const & rightTop, float const health, float const speed)
    : m_alienHealth(health)
    , m_alienSpeed(speed)
  {
    m_box = Box2D(leftBottom, rightTop);
  }

  Alien( Box2D const & alienBox)
    : m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {
     m_box = Box2D(alienBox.x1(), alienBox.y1(), alienBox.x2(), alienBox.y2());
  }

  float const & GetHealth() const { return m_alienHealth; }
  float const & GetSpeed() const { return m_alienSpeed; }

  void SetAlienHealth(const float newHelth)
  {
      if ((newHelth < 0.0f) || (newHelth > 100.0f)) throw invalid_argument("Health must be in range 0..100");
      m_alienHealth = newHelth;
  }
  void SetAlienSpeed( const float newSpeed) { m_alienSpeed = newSpeed; }
  void RemoveAlienHealth(const float deltaHelth)
  {
      if (m_alienHealth < deltaHelth) throw invalid_argument("Negative health");
      m_alienHealth -= deltaHelth;
  }
  void AddAlienSpeed( const float deltaSpeed) { m_alienSpeed += deltaSpeed; }

private:
  float m_alienHealth = 0.0f;
  float m_alienSpeed = 0.0f;
};
