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

