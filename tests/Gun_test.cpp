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
  EXPECT_EQ(a1.GetSpeed(), GunSpeed);
  EXPECT_EQ(a1.GetAmmo(), GunAmmo);
  EXPECT_EQ(a1.GetHealth(), GunHealth);
  EXPECT_EQ(a1.GetRate(), GunPower);

  Gun a2(1.5f, 1.0f, 2.5f, 5.0f);
  EXPECT_EQ(a2.x1(), 1.5f);
  EXPECT_EQ(a2.x2(), 2.5f);
  EXPECT_EQ(a2.y1(), 1.0f);
  EXPECT_EQ(a2.y2(), 5.0f);
  EXPECT_EQ(a2.GetSpeed(), GunSpeed);
  EXPECT_EQ(a2.GetAmmo(), GunAmmo);
  EXPECT_EQ(a2.GetHealth(), GunHealth);
  EXPECT_EQ(a2.GetRate(), GunPower);

  Gun a3(b1);
  EXPECT_EQ(a3.x1(), 1.5f);
  EXPECT_EQ(a3.y1(), 3.0f);
  EXPECT_EQ(a3.x2(), 5.5f);
  EXPECT_EQ(a3.y2(), 12.5f);
  EXPECT_EQ(a3.GetSpeed(), GunSpeed);
  EXPECT_EQ(a3.GetAmmo(), GunAmmo);
  EXPECT_EQ(a3.GetHealth(), GunHealth);
  EXPECT_EQ(a3.GetRate(), GunPower);
}
