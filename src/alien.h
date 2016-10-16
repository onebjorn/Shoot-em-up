#pragma once
#include "../include/config_stat.h"
#include "box2d.h"
#include "bullet.h"

class Alien : public Box2D
{
public:
  Alien() = default;

  /* Добавить константы в конфиг*/

  Alien(float const x1, float const y1, float const x2, float const y2)
    : Box2D (x1, y1, x2, y2)
    , m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {}

  Alien(float const x, float const y)
    : Box2D (x - AlienSizeX / 2, y - AlienSizeY / 2 , x + AlienSizeX / 2, y + AlienSizeY / 2)
    , m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {}

  Alien(Point2D const & center)
    : Box2D(center.x() - AlienSizeX / 2, center.y() - AlienSizeY / 2, center.x() + AlienSizeX / 2, center.y() + AlienSizeY / 2)
    , m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {}

  Alien(Point2D const & leftBottom, Point2D const & rightTop, float const health, float const speed)
    : Box2D(leftBottom, rightTop)
    , m_alienHealth(health)
    , m_alienSpeed(speed)
  {}

  Alien( Box2D const & alienBox)
    : Box2D( alienBox.x1(), alienBox.y1(), alienBox.x2(), alienBox.y2())
    , m_alienHealth(AlienHealth)
    , m_alienSpeed(AlienSpeed)
  {}

  Bullet AlienShot( Alien const & obj)
  {
     return { obj.x1() + AlienSizeX / 2, obj.y1() + BulletSizeY / 2, - BulletSpeed };
  }


  float const & GetHealth() const { return m_alienHealth; }
  float const & GetSpeed() const { return m_alienSpeed; }

  void SetAlienHealth(const float newHelth) { m_alienHealth = newHelth; }
  void SetAlienSpeed( const float newSpeed) { m_alienSpeed = newSpeed; }
  void RemoveAlienHealth(const float deltaHelth) { m_alienHealth -= deltaHelth; }
  void AddAlienSpeed( const float deltaSpeed) { m_alienSpeed += deltaSpeed; }

private:
  float m_alienHealth = 0.0f;
  float m_alienSpeed = 0.0f;
};
