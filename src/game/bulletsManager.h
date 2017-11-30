#pragma once
#include "alien.h"
#include "bullet.h"
#include "logger.h"
#include <vector>
#include "../include/config_stat.h"


using Bullets = vector<Bullet>;

class BulletsManager
{
public:

  BulletsManager() = default;

  Bullets & getBullets() { return m_bullets; }

  void DeleteBullet(vector<Bullet>::iterator it) { m_bullets.erase(it); }

  void AddBullet(Bullet const & obj) { m_bullets.push_back(obj); }

  void BulletsMove(float const deltaY)
  {
    for (auto it = m_bullets.begin(); it != m_bullets.end(); ++it)
    {
      it->SetBox({ 0.0f, deltaY * it->GetSpeed(), 0.0f, deltaY * it->GetSpeed() });
    }
 }

  ~BulletsManager() = default;

  void clear()
  {
    m_bullets.erase(m_bullets.begin(), m_bullets.end());
  }

private:
  vector<Bullet> m_bullets;
};

inline ostream & operator << (ostream & os, BulletsManager & obj)
{
  os << "Bullets:  " << " Count = " << obj.getBullets().size() << endl;
  Logger::Instance().Log(os, obj.getBullets());
  return os;
}
