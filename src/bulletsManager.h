#include "alien.h"
#include "bullet.h"
#include "logger.h"
#include <vector>
#include "../include/config_stat.h"
#pragma once

using Bullets = std::vector<Bullet>;

class BulletsManager
{
public:

  BulletsManager() = default;

  Bullets const & getBullets() const { return m_bullets; }

  void AddBullet(Bullet const & obj) { m_bullets.push_back(obj); }

  ~BulletsManager() = default;

private:
  std::vector<Bullet> m_bullets;
};

inline ostream & operator << (ostream & os, BulletsManager const & obj)
{
  os << "Bullets:  " << " Count = " << obj.getBullets().size() << endl;
  Logger::Instance().LogList(os, obj.getBullets());
  return os;
}
