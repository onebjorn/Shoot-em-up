#pragma once
#include "../include/config_stat.h"
#include "gameEntity.h"

class Bullet : public GameEntity
{
public:
  Bullet() = default;

  Bullet(float const x0, float const y0, float const x1, float const y1)
    : m_bullet(x0, y0, x1, y1)
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet(float const x, float const y, float speed)
    : m_bullet(x - BulletSizeX / 2, y - BulletSizeY / 2 , x + BulletSizeX / 2, y + BulletSizeY / 2)
    , m_bulletSpeed(speed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet(Point2D const & center)
    : m_bullet(center.x() - BulletSizeX / 2, center.y() - BulletSizeY / 2, center.x() + BulletSizeX / 2, center.y() + BulletSizeY / 2)
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}


  Bullet(Box2D const & bullobj)
    : m_bullet(bullobj)
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  Bullet(initializer_list<float> const & lst)
    : m_bullet(lst)
    , m_bulletSpeed(BulletSpeed)
    , m_bulletDam(BulletDamage)
  {}

  float const & GetDamage() const { return m_bulletDam; }
  float const & GetSpeed() const { return m_bulletSpeed; }

  Point2D GetCenter() const override
  {
    return { (m_bullet.x1() + m_bullet.x2()) / 2.0f, (m_bullet.y1() + m_bullet.y2()) / 2.0f  };
  }

  Box2D const & GetBox() const override { return m_bullet; }

  ~Bullet() {}

private:

  Box2D m_bullet = { 0.0f, 0.0f, 0.0f, 0.0f };

  float m_bulletSpeed = 0.0f;
  float m_bulletDam = 0.0f;
};
