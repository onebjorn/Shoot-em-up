#pragma once
#include "../include/config_stat.h"
#include "box2d.h"

class Bullet : public Box2D
{
public:
  Bullet() = default;

  Bullet(float const x0, float const y0, float const x1, float const y1)
    : Box2D (x0, y0, x1, y1)
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet(float const x, float const y, float speed)
    : Box2D (x - BulletSizeX / 2, y - BulletSizeY / 2 , x + BulletSizeX / 2, y + BulletSizeY / 2)
    , m_bulletSpeed(speed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet(Point2D const & center)
    : Box2D(center.x() - BulletSizeX / 2, center.y() - BulletSizeY / 2, center.x() + BulletSizeX / 2, center.y() + BulletSizeY / 2)
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}


  Bullet(Box2D const & bullobj)
    : Box2D(bullobj)
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet(initializer_list<float> const & lst)
    : Box2D( lst )
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  float const & GimmeDamage() const { return m_bulletDam; }
  float const & GimmeSpeed() const { return m_bulletSpeed; }

  //TODO:Hit the object

private:
  float m_bulletSpeed = 0.0f;
  float m_bulletDam = 0.0f;
};
