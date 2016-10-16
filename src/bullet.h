#pragma once
#include "../include/config_stat.h"
#include "box2d.h"

class Bullet2D : public Box2D
{
public:
  Bullet2D() = default;

  Bullet2D(float const x0, float const y0, float const x1, float const y1)
    : Box2D( x0, y0, x1, y1 )
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet2D(Box2D const & bullobj)
    : Box2D( bullobj )
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet2D(initializer_list<float> const & lst)
    : Box2D( lst )
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  float const & GimmeDamage() const { return m_bulletDam; }
  float const & GimmeSpeed() const { return m_bulletSpeed; }

  //TODO:Hit the object

private:
  //TODO: Size of bullet
  float m_bulletSpeed = 0.0f;
  float m_bulletDam = 0.0f;
};
