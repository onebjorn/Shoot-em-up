#pragma once
#include "../include/config_stat.h"
#include "ray2d.h"

class Bullet2D : public Ray2D
{
public:
  Bullet2D() = default;

  Bullet2D(float const x0, float const y0, float const x1, float const y1)
    : Ray2D( x0 ,y0 ,x1 ,y1 )
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet2D(Ray2D const & bullobj)
    : Ray2D( bullobj )
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet2D(initializer_list<float> const & lst)
    : Ray2D( lst )
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
