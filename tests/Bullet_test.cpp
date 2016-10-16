#include "gtest/gtest.h"
#include "../include/config_stat.h"
#include "bullet.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(bullet_test, test_construction)
{
  Box2D p1 = { 5.0f, 5.0f, 10.0f, 10.0f};

  Bullet a1(p1);
  EXPECT_EQ(a1.x1(), 5.0f);
  EXPECT_EQ(a1.y1(), 5.0f);
  EXPECT_EQ(a1.x2(), 10.0f);
  EXPECT_EQ(a1.y2(), 10.0f);
  EXPECT_EQ(a1.GimmeSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GimmeDamage(), BulletDamage);

  Bullet a2(1.0f, 1.0f, 4.0f, 5.0f);
  EXPECT_EQ(a2.x1(), 1.0f);
  EXPECT_EQ(a2.y1(), 1.0f);
  EXPECT_EQ(a2.x2(), 4.0f);
  EXPECT_EQ(a2.y2(), 5.0f);
  EXPECT_EQ(a1.GimmeSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GimmeDamage(), BulletDamage);

  Bullet a3 = { 1.0f, 1.0f, 4.0f, 5.0f };
  EXPECT_EQ(a3.x1(), 1.0f);
  EXPECT_EQ(a3.y1(), 1.0f);
  EXPECT_EQ(a3.x2(), 4.0f);
  EXPECT_EQ(a3.y2(), 5.0f);
  EXPECT_EQ(a1.GimmeSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GimmeDamage(), BulletDamage);
}

TEST(bullet_test, test_move)
{
  Bullet bul1(1.0f, 2.0f, 3.0f, 4.0f);
  Bullet bul2 = move(bul1);
  EXPECT_EQ(bul2.x1(), 1.0f);
  EXPECT_EQ(bul1.x1(), 0.0f);
}
