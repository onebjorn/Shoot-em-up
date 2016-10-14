#pragma once
#include "../include/config_stat.h"
#include "ray2d.h"

class Bullet2D
{
public:
  Bullet2D() = default;

  Bullet2D(float const x0, float const y0, float const x1, float const y1)
    : Ray2D(x0,y0,x1,y1)
    , m_bulletspeed(BulletSpeed)
    , m_bulletdam(BulletDamage)
  {}

  Bullet2D(Ray2D const & bullobj)
    : Ray2D(bullobj)
    , m_bulletspeed(BulletSpeed)
    , m_bulletdam(BulletDamage)
  {}

  Bullet2D(initializer_list<float> const & lst)
    : Ray2D(lst)
    , m_bulletspeed(BulletSpeed)
    , m_bulletdam(BulletDamage)
  {}

  //TODO:Hit the object

private:
  //TODO: Size of bullet
  float m_bulletspeed = 0.0f;
  float m_bulletdam = 0.0f;
};
