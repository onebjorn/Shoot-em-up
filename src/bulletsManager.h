#include "alien.h"
#include "gun.h"
#include "bullet.h"
#include <vector>
#include "../include/config_stat.h"

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
