#pragma once
#include "../include/config_stat.h"
#include "box2d.h"
#include "bullet.h"

class Gun : public Box2D
{
public:
  Gun() = default;

  Gun(float const x1, float const y1, float const x2, float const y2)
    : Box2D(x1, y1, x2, y2)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun(Point2D const & leftBottom, Point2D const & rightTop)
    : Box2D(leftBottom, rightTop)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun(Box2D const & gunobj)
    : Box2D(gunobj)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun(initializer_list<float> const & lst)
    : Box2D(lst)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  float const & GetHealth() const { return m_gunhealth; }
  float const & GetSpeed() const { return m_gunspeed; }
  float const & GetRate() const { return m_gunpower; }
  int const & GetAmmo() const { return m_ammo; }

  void HealthLoss(const float loss) { m_gunhealth -= loss; }
  void SpeedLoss(const float loss) { m_gunspeed -= loss;}
  void SpeedUp(const float nitro) { m_gunspeed += nitro;}

  void Shot( Gun const & obj)
  {
    if (m_ammo > 0)
    {
      Bullet bullet(obj.x1() + GunSizeX, obj.y2() + BulletSizeY, BulletSpeed);
      m_ammo--;
    }
    else m_ammo = 10;
  }

private:
  float m_gunhealth = 0.0f;
  float m_gunspeed = 0.0f;
  float m_gunpower = 0.0f;
  int m_ammo = 0;
};
