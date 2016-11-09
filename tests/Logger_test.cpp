#include "gtest/gtest.h"
#include "../include/config_stat.h"
#include "logger.h"
#include  "bulletsManager.h"
#include "aliensManager.h"
#include "gun.h"
#include "bullet.h"
#include "alien.h"
#include <sstream>
#include <ostream>
#include <iostream>
#include <unordered_set>

TEST(logger_test, test)
{
  stringstream bullets;
  stringstream bullet;
  stringstream aliens;
  stringstream alien;

  BulletsManager Bm;
  Logger::Log(Bm, bullets);
  EXPECT_EQ("Bullets:   Count = 0\n", bullets.str());

  Gun g(5.0f, 5.0f);
  Logger::Log(g.Shot(), bullet);
  EXPECT_EQ("Bullet: coordinates center:  { 5, 7.5 },  Damage = 100,  Speed = 200\n", bullet.str());

  AliensManager am(0, 0);
  Logger::Log(am, aliens);
  EXPECT_EQ("Aliens:  Rows = 0, Columns = 0\n", aliens.str());

  Alien a1;
  Logger::Log(a1, alien);
  EXPECT_EQ("Alien:   Coordinates center = { 0, 0 },    Health = 0,  Speed = 0\n", alien.str());
}
