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
  EXPECT_EQ(a1.GetBox().x1(), 5.0f);
  EXPECT_EQ(a1.GetBox().y1(), 5.0f);
  EXPECT_EQ(a1.GetBox().x2(), 10.0f);
  EXPECT_EQ(a1.GetBox().y2(), 10.0f);
  EXPECT_EQ(a1.GetSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GetDamage(), BulletDamage);

  Bullet a2(1.0f, 1.0f, 4.0f, 5.0f);
  EXPECT_EQ(a2.GetBox().x1(), 1.0f);
  EXPECT_EQ(a2.GetBox().y1(), 1.0f);
  EXPECT_EQ(a2.GetBox().x2(), 4.0f);
  EXPECT_EQ(a2.GetBox().y2(), 5.0f);
  EXPECT_EQ(a1.GetSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GetDamage(), BulletDamage);

  Bullet a3 = { 1.0f, 1.0f, 4.0f, 5.0f };
  EXPECT_EQ(a3.GetBox().x1(), 1.0f);
  EXPECT_EQ(a3.GetBox().y1(), 1.0f);
  EXPECT_EQ(a3.GetBox().x2(), 4.0f);
  EXPECT_EQ(a3.GetBox().y2(), 5.0f);
  EXPECT_EQ(a1.GetSpeed(), BulletSpeed);
  EXPECT_EQ(a1.GetDamage(), BulletDamage);
}

TEST(Bullet_test, test_move)
{
  Point2D p1 = { 1.0f, 1.0f };
  Box2D b1 = { 1.5f, 1.5f, 0.5f, 2.5f };

  Bullet bullet1(p1);
  Bullet bullet2(1.5f, 1.5f, 2.5f, 2.5f);
  Bullet bullet3(b1);

  bullet3 = move(bullet2);
  EXPECT_EQ(bullet3.GetBox().x1(), 1.5f);
  Bullet bullet4 = move(bullet1);
  EXPECT_EQ(bullet4.GetBox().x1(), 1.0f - BulletSizeX / 2);
  Bullet bullet5 = move(b1);
  EXPECT_EQ(bullet5.GetBox().x2(), 1.5f);
}
