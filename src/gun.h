#pragma once
#include "../include/config_stat.h"
#include "gameEntity.h"
#include "bullet.h"

class Gun : public GameEntity
{
public:
  Gun() = default;

  Gun(float const x1, float const y1, float const x2, float const y2)
    : m_gun(x1, y1, x2, y2)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun(Point2D const & leftBottom, Point2D const & rightTop)
    : m_gun(leftBottom, rightTop)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun(float const x, float const y)
    : m_gun(x - GunSizeX / 2, y - GunSizeY / 2 , x + GunSizeX / 2, y + GunSizeY / 2)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun(Box2D const & gunobj)
    : m_gun(gunobj)
    , m_gunhealth(GunHealth)
    , m_gunspeed(GunSpeed)
    , m_gunpower(GunPower)
    , m_ammo(GunAmmo)
  {}

  Gun(initializer_list<float> const & lst)
    : m_gun(lst)
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

  Bullet Shot()
  {
      m_ammo--;
      return { m_gun.x1() + GunSizeX /2, m_gun.y2() + BulletSizeY, BulletSpeed };
  }

  Point2D GetCenter() const override
  {
    return { (m_gun.x1() + m_gun.x2()) / 2.0f, (m_gun.y1() + m_gun.y2()) / 2.0f  };
  }

  Box2D const & GetBox() const override { return m_gun; }

  ~Gun() override {}

private:
  Box2D m_gun = { 0.0f, 0.0f, 0.0f, 0.0f };

  float m_gunhealth = 0.0f;
  float m_gunspeed = 0.0f;
  float m_gunpower = 0.0f;
  int m_ammo = 0;
};
