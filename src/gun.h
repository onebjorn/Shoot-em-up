#pragma once
#include "../include/config_stat.h"
#include "box2d.h"

class Gun2D
{
public:
  Gun2D() = default;

  Gun2D(float const x1, float const y1, float const x2, float const y2)
    : Box2D(x1, y1, x2, y2)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun2D(Point2D const & leftBottom, Point2D const & rightTop)
    : Box2D(leftBottom, rightTop)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun2D(Box2D const & gunobj)
    : Box2D(gunobj)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun2D(initializer_list<float> const & lst)
    : Box2D(lst)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  float const & GimmeHealth() const { return m_gunhealth; }
  float const & GimmeSpeed() const { return m_gunspeed; }
  float const & GimmeRate() const { return m_gunpower; }
  int const & GimmeAmmo() const { return m_ammo; }

  void HealthLoss(const float loss) { m_gunhealth -= loss; }
  void SpeedLoss(const float loss) { m_gunspeed -= loss;}
  void SpeedUp(const float nitro) { m_gunspeed += nitro;}

  //TODO: SHOT, BulletManager



private:
  float m_gunhealth = 0.0f;
  float m_gunspeed = 0.0f;
  float m_gunpower = 0.0f;
  unsigned int m_ammo = 0;

};
