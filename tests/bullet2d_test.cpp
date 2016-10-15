#include "gtest/gtest.h"
#include "../include/config_stat.h"
#include "bullet.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(Bullet2D_test, test_construction)
{
  Ray2D p1 = { 5.0f, 5.0f, pi()/3.0f };

  Bullet2D a1(p1);
  EXPECT_EQ(a1.x0(), 5.0f);
  EXPECT_EQ(a1.y0(), 5.0f);
  EXPECT_EQ(a1.GetDirect(0), 0.5f);
  EXPECT_EQ(a1.GetDirect(1), 0.866f);
  EXPECT_EQ(a1.GimmeSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GimmeDamage(), BulletDamage);

  Bullet2D a2(1.0f, 1.0f, 4.0f, 5.0f);
  EXPECT_EQ(a2.x0(), 1.0f);
  EXPECT_EQ(a2.y0(), 1.0f);
  EXPECT_EQ(a2.GetDirect(0), 0.6f);
  EXPECT_EQ(a2.GetDirect(1), 0.8f);
  EXPECT_EQ(a1.GimmeSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GimmeDamage(), BulletDamage);

  Bullet2D a3 = { 1.0f, 1.0f, 4.0f, 5.0f };
  EXPECT_EQ(a3.x1(), 1.0f);
  EXPECT_EQ(a3.y1(), 1.0f);
  EXPECT_EQ(a3.x1(), 0.6f);
  EXPECT_EQ(a3.x1(), 0.8f);
  EXPECT_EQ(a1.GimmeSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GimmeDamage(), BulletDamage);

}
