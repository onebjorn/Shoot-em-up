#pragma once
#include "../include/config_stat.h"
#include "gameEntity.h"
#include "bullet.h"
#include "logger.h"
#include "bulletsManager.h"
#include <ostream>


class Gun : public GameEntity
{
public:
  Gun() = default;

  Gun(float const x1, float const y1, float const x2, float const y2)
    : m_gunHealth(kGunHealth)
    , m_gunSpeed(kGunSpeed)
    , m_gunPower(kGunPower)
    , m_ammo(kGunAmmo)
  {
     m_box = Box2D(x1, y1, x2, y2);
  }

  Gun(Point2D const & leftBottom, Point2D const & rightTop)
    : m_gunHealth(kGunHealth)
    , m_gunSpeed(kGunSpeed)
    , m_gunPower(kGunPower)
    , m_ammo(kGunAmmo)
  {
    m_box = Box2D(leftBottom, rightTop);
  }

  Gun(float const x, float const y)
    : m_gunHealth(kGunHealth)
    , m_gunSpeed(kGunSpeed)
    , m_gunPower(kGunPower)
    , m_ammo(kGunAmmo)
  {
    m_box = Box2D(x - kGunSizeX / 2.0f, y - kGunSizeY / 2.0f , x + kGunSizeX / 2.0f, y + kGunSizeY / 2.0f);
  }

  Gun(Box2D const & gunobj)
    : m_gunHealth(kGunHealth)
    , m_gunSpeed(kGunSpeed)
    , m_gunPower(kGunPower)
    , m_ammo(kGunAmmo)
  {
    m_box = Box2D(gunobj);
  }

  float const & GetHealth() const { return m_gunHealth; }
  float const & GetSpeed() const { return m_gunSpeed; }
  float const & GetRate() const { return m_gunPower; }
  int const & GetAmmo() const { return m_ammo; }

  void SetPower(float const power)
  {
    if (power < 0.0f) throw invalid_argument("Negative power");
    m_gunPower = power;
  }

  void SetHealth(float const health)
  {
    if ((health > 100.0f) || (health < 0.0f)) throw invalid_argument("Health must be in range 0..100");
    m_gunHealth = health;
  }

  void HealthLoss(float const loss)
  {
    if ((loss < 0.0f) || (loss > 100.0f)) throw invalid_argument("Negative health");
    m_gunHealth -= loss;
  }

  void SpeedLoss(const float loss)
  {
    if (m_gunSpeed < loss) throw invalid_argument("Negative speed");
    m_gunSpeed -= loss;
  }

  void SpeedUp(const float nitro) { m_gunSpeed += nitro; }

  Bullet Shot()
  {
    m_ammo--;
    Bullet m_bullet = { m_box.GetCenter().x() - kBulletSizeX / 2.0f, m_box.GetCenter().y() + kGunSizeY / 2.0f,
                        m_box.GetCenter().x() + kBulletSizeX / 2.0f, m_box.GetCenter().y() + kGunSizeY / 2.0f + kBulletSizeY };
    return m_bullet;
  }

private:
  float m_gunHealth = 0.0f;
  float m_gunSpeed = 0.0f;
  float m_gunPower = 0.0f;
  int m_ammo = 0;
};

inline ostream & operator << (ostream & os, Gun const & obj)
{
  os << "Gun: " << " Сoordinates center = " << "{ "<< obj.GetBox().GetCenter().x() << ", "
     << obj.GetBox().GetCenter().y() << " },  Health = " << obj.GetHealth()  << ", Ammo = " << obj.GetAmmo()  << ", Speed = " << obj.GetSpeed() << endl;
  return os;
}
