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
  EXPECT_EQ(a1.GetBox().x1(), 2.0f);
  EXPECT_EQ(a1.GetBox().y1(), 3.0f);
  EXPECT_EQ(a1.GetBox().x2(), 5.0f);
  EXPECT_EQ(a1.GetBox().y2(), 5.0f);
  EXPECT_EQ(a1.GetSpeed(), GunSpeed);
  EXPECT_EQ(a1.GetAmmo(), GunAmmo);
  EXPECT_EQ(a1.GetHealth(), GunHealth);
  EXPECT_EQ(a1.GetRate(), GunPower);

  Gun a2(1.5f, 1.0f, 2.5f, 5.0f);
  EXPECT_EQ(a2.GetBox().x1(), 1.5f);
  EXPECT_EQ(a2.GetBox().y1(), 1.0f);
  EXPECT_EQ(a2.GetBox().x2(), 2.5f);
  EXPECT_EQ(a2.GetBox().y2(), 5.0f);
  EXPECT_EQ(a2.GetSpeed(), GunSpeed);
  EXPECT_EQ(a2.GetAmmo(), GunAmmo);
  EXPECT_EQ(a2.GetHealth(), GunHealth);
  EXPECT_EQ(a2.GetRate(), GunPower);

  Gun a3(b1);
  EXPECT_EQ(a3.GetBox().x1(), 1.5f);
  EXPECT_EQ(a3.GetBox().y1(), 3.0f);
  EXPECT_EQ(a3.GetBox().x2(), 5.5f);
  EXPECT_EQ(a3.GetBox().y2(), 12.5f);
  EXPECT_EQ(a3.GetSpeed(), GunSpeed);
  EXPECT_EQ(a3.GetAmmo(), GunAmmo);
  EXPECT_EQ(a3.GetHealth(), GunHealth);
  EXPECT_EQ(a3.GetRate(), GunPower);
}

TEST(Gun_test, test_move)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Box2D b1 = { 1.5f, 1.5f, 0.5f, 2.5f };

  Gun a1(p1, p2);
  Gun a2(2.5f, 1.5f, 1.5f, 2.5f);
  Gun a3(b1);

  a3 = move(a2);
  EXPECT_EQ(a3.GetBox().GetCenter().x(), 2.0f);
  Gun a4 = move(a3);
  EXPECT_EQ(a4.GetBox().x1(), 1.5f);
  Gun a5 = move(b1);
  EXPECT_EQ(a5.GetBox().x2(), 1.5f);
}

TEST(Gun_test, test_shot)
{
  Gun a2(2.0f, 2.0f);
  EXPECT_EQ(a2.Shot().GetBox().x1(), 2.0f);
}

TEST(Gun_test, test_exceptions)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  Gun gun1(p1, p2);
  EXPECT_THROW(gun1.HealthLoss(101.0f), invalid_argument);
  EXPECT_THROW(gun1.SpeedLoss(20.0f), invalid_argument);
  EXPECT_THROW(gun1.SetHealth(-101.0f), invalid_argument);
}
