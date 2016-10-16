#include "gtest/gtest.h"
#include "../include/config_stat.h"
#include "gun.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(gun_test, test_construction)
{
  Point2D p1 = { 5.0f, 5.0f };
  Point2D p2 = { 2.0f, 3.0f };
  Box2D b1 = { 1.5f, 3.0f, 5.5f, 12.5f };

  Gun a1(p1, p2);
  EXPECT_EQ(a1.x2(), 5.0f);
  EXPECT_EQ(a1.y2(), 5.0f);
  EXPECT_EQ(a1.x1(), 2.0f);
  EXPECT_EQ(a1.y1(), 3.0f);
  EXPECT_EQ(a1.GimmeSpeed(), GunSpeed);
  EXPECT_EQ(a1.GimmeAmmo(), GunAmmo);
  EXPECT_EQ(a1.GimmeHealth(), GunHealth);
  EXPECT_EQ(a1.GimmeRate(), GunPower);

  Gun a2(1.5f, 1.0f, 2.5f, 5.0f);
  EXPECT_EQ(a2.x1(), 1.5f);
  EXPECT_EQ(a2.x2(), 2.5f);
  EXPECT_EQ(a2.y1(), 1.0f);
  EXPECT_EQ(a2.y2(), 5.0f);
  EXPECT_EQ(a2.GimmeSpeed(), GunSpeed);
  EXPECT_EQ(a2.GimmeAmmo(), GunAmmo);
  EXPECT_EQ(a2.GimmeHealth(), GunHealth);
  EXPECT_EQ(a2.GimmeRate(), GunPower);

  Gun a3(b1);
  EXPECT_EQ(a3.x1(), 1.5f);
  EXPECT_EQ(a3.y1(), 3.0f);
  EXPECT_EQ(a3.x2(), 5.5f);
  EXPECT_EQ(a3.y2(), 12.5f);
  EXPECT_EQ(a3.GimmeSpeed(), GunSpeed);
  EXPECT_EQ(a3.GimmeAmmo(), GunAmmo);
  EXPECT_EQ(a3.GimmeHealth(), GunHealth);
  EXPECT_EQ(a3.GimmeRate(), GunPower);
}
