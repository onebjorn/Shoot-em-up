#pragma once
#include "../include/config_stat.h"
#include "gameEntity.h"
#include <ostream>
#include <iostream>

class Bullet : public GameEntity
{
public:
  Bullet() = default;

  Bullet(float const x0, float const y0, float const x1, float const y1)
    : m_bulletSpeed(kBulletSpeed)
    , m_bulletDam(kBulletDamage)
  {
    m_box = Box2D(x0, y0, x1, y1);
  }

  Bullet(float const x, float const y, float speed)
    : m_bulletSpeed(speed)
    , m_bulletDam(kBulletDamage)
  {
    m_box = Box2D(x - kBulletSizeX / 2.0f, y - kBulletSizeY / 2.0f , x + kBulletSizeX / 2.0f, y + kBulletSizeY / 2.0f);
  }

  Bullet(Point2D const & center)
    : m_bulletSpeed(kBulletSpeed)
    , m_bulletDam(kBulletDamage)
  {
    m_box = Box2D(center.x() - kBulletSizeX / 2.0f, center.y() - kBulletSizeY / 2.0f, center.x() + kBulletSizeX / 2.0f, center.y() + kBulletSizeY / 2.0f);
  }

  Bullet(Box2D const & bullobj)
    : m_bulletSpeed(kBulletSpeed)
    , m_bulletDam(kBulletDamage)
  {
    m_box = Box2D(bullobj);
  }

  Bullet(initializer_list<float> const & lst)
    : m_bulletSpeed(kBulletSpeed)
    , m_bulletDam(kBulletDamage)
  {
    m_box = Box2D(lst);
  }

  float const & GetDamage() const { return m_bulletDam; }
  float const & GetSpeed() const { return m_bulletSpeed; }

private:
  float m_bulletSpeed = 0.0f;
  float m_bulletDam = 0.0f;
};

inline ostream & operator << (ostream & os, Bullet const & obj)
{
  os << "Bullet: coordinates center: " << " { "<< obj.GetBox().GetCenter().x() << ", "
     << obj.GetBox().GetCenter().y() << " },  Damage = "<< obj.GetDamage() << ",  Speed = " << obj.GetSpeed() << endl;
  return os;
}
