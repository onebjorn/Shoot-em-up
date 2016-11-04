#pragma once
#include "../include/config_stat.h"
#include "gameEntity.h"
#include "bullet.h"
#include <ostream>
#include <iostream>

class Alien : public GameEntity
{
public:
  Alien() = default;

  Alien(float const x1, float const y1, float const x2, float const y2)
    : m_alienHealth(kAlienHealth)
    , m_alienSpeed(kAlienSpeed)
  {
    m_box = Box2D(x1, y1, x2, y2);
  }

  Alien(float const x, float const y)
    : m_alienHealth(kAlienHealth)
    , m_alienSpeed(kAlienSpeed)
  {
    m_box = Box2D(x - kAlienSizeX / 2, y - kAlienSizeY / 2 , x + kAlienSizeX / 2, y + kAlienSizeY / 2);
  }

  Alien(Point2D const & center)
    : m_alienHealth(kAlienHealth)
    , m_alienSpeed(kAlienSpeed)
  {
    m_box = Box2D(center.x() - kAlienSizeX / 2, center.y() - kAlienSizeY / 2, center.x() + kAlienSizeX / 2, center.y() + kAlienSizeY / 2);
  }

  Alien(Point2D const & leftBottom, Point2D const & rightTop, float const health, float const speed)
    : m_alienHealth(health)
    , m_alienSpeed(speed)
  {
    m_box = Box2D(leftBottom, rightTop);
  }

  Alien( Box2D const & alienBox)
    : m_alienHealth(kAlienHealth)
    , m_alienSpeed(kAlienSpeed)
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

  void AddAlienSpeed(float const deltaSpeed) { m_alienSpeed += deltaSpeed; }

  Bullet AlienShot() { return { m_box.x1() + kAlienSizeX /2, m_box.y2() + kBulletSizeY, - kBulletSpeed }; }

private:
  float m_alienHealth = 0.0f;
  float m_alienSpeed = 0.0f;
};

inline ostream & operator << (ostream & os, Alien const & obj)
{
  os << "Alien: " << "  Coordinates center = " <<"{ "<< obj.GetBox().GetCenter().x() << ", "
     << obj.GetBox().GetCenter().y() << " },  " << "  Health = " << obj.GetHealth() << ",  Speed = " << obj.GetSpeed() << std::endl;
  return os;
}
