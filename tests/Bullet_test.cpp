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
  EXPECT_EQ(a1.GetSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GetDamage(), BulletDamage);

  Bullet a2(1.0f, 1.0f, 4.0f, 5.0f);
  EXPECT_EQ(a2.x1(), 1.0f);
  EXPECT_EQ(a2.y1(), 1.0f);
  EXPECT_EQ(a2.x2(), 4.0f);
  EXPECT_EQ(a2.y2(), 5.0f);
  EXPECT_EQ(a1.GetSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GetDamage(), BulletDamage);

  Bullet a3 = { 1.0f, 1.0f, 4.0f, 5.0f };
  EXPECT_EQ(a3.x1(), 1.0f);
  EXPECT_EQ(a3.y1(), 1.0f);
  EXPECT_EQ(a3.x2(), 4.0f);
  EXPECT_EQ(a3.y2(), 5.0f);
  EXPECT_EQ(a1.GetSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GetDamage(), BulletDamage);
}

