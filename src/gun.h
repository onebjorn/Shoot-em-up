#pragma once
#include "../include/config_stat.h"
#include "gameEntity.h"
#include "bullet.h"
#include "logger.h"
#include <ostream>
#include "bulletsManager.h"

class Gun : public GameEntity
{
public:
  Gun() = default;

  Gun(float const x1, float const y1, float const x2, float const y2)
    : m_gunhealth(kGunHealth)
    , m_gunspeed(kGunSpeed)
    , m_gunpower(kGunPower)
    , m_ammo(kGunAmmo)
  {
     m_box = Box2D(x1, y1, x2, y2);
  }

  Gun(Point2D const & leftBottom, Point2D const & rightTop)
    : m_gunhealth(kGunHealth)
    , m_gunspeed(kGunSpeed)
    , m_gunpower(kGunPower)
    , m_ammo(kGunAmmo)
  {
    m_box = Box2D(leftBottom, rightTop);
  }

  Gun(float const x, float const y)
    : m_gunhealth(kGunHealth)
    , m_gunspeed(kGunSpeed)
    , m_gunpower(kGunPower)
    , m_ammo(kGunAmmo)
  {
    m_box = Box2D(x - kGunSizeX / 2.0f, y - kGunSizeY / 2.0f , x + kGunSizeX / 2.0f, y + kGunSizeY / 2.0f);
  }

  Gun(Box2D const & gunobj)
    : m_gunhealth(kGunHealth)
    , m_gunspeed(kGunSpeed)
    , m_gunpower(kGunPower)
    , m_ammo(kGunAmmo)
  {
    m_box = Box2D(gunobj);
  }

  float const & GetHealth() const { return m_gunhealth; }
  float const & GetSpeed() const { return m_gunspeed; }
  float const & GetRate() const { return m_gunpower; }
  int const & GetAmmo() const { return m_ammo; }

  void SetPower(float const power)
  {
    if (power < 0.0f) throw invalid_argument("Negative power");
    m_gunpower = power;
  }

  void SetHealth(float const health)
  {
    if ((health > 100.0f) || (health < 0.0f)) throw invalid_argument("Health must be in range 0..100");
    m_gunhealth = health;
  }

  void HealthLoss(float const loss)
  {
    if (m_gunhealth < loss) throw invalid_argument("Negative health");
    m_gunhealth -= loss;
  }

  void SpeedLoss(const float loss)
  {
    if (m_gunspeed < loss) throw invalid_argument("Negative speed");
    m_gunspeed -= loss;
  }

  void SpeedUp(const float nitro) { m_gunspeed += nitro; }

  Bullet Shot()
  {
    if (m_ammo > 0)
    m_ammo--;
    Bullet m_bullet = { m_box.GetCenter().x() - kBulletSizeX / 2.0f, m_box.GetCenter().y() + kGunSizeY / 2.0f,
                        m_box.GetCenter().x() + kBulletSizeX / 2.0f, m_box.GetCenter().y() + kGunSizeY / 2.0f + kBulletSizeY };
    return m_bullet;
  }

private:
  float m_gunhealth = 0.0f;
  float m_gunspeed = 0.0f;
  float m_gunpower = 0.0f;
  int m_ammo = 0;
};

inline ostream & operator << (ostream & os, Gun const & obj)
{
  os << "Gun: " << " Сoordinates center = " << "{ "<< obj.GetBox().GetCenter().x() << ", "
     << obj.GetBox().GetCenter().y() << " },  Health = " << obj.GetHealth()  << ", Ammo = " << obj.GetAmmo()  << ", Speed = " << obj.GetSpeed() << endl;
  return os;
}
