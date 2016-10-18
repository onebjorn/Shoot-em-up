#include "gtest/gtest.h"
#include "../include/config_stat.h"
#include "space.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(Space_test, test_construction)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Point2D p3 = { 1.5f, 1.5f };
  Box2D b1 = { 0.5f, 1.5f, 1.5f, 2.5f };

  Space a1(p1, p2);
  Space a2(1.5f, 1.5f, 2.5f, 2.5f);
  Space a3(b1);

  EXPECT_EQ(a1.GetBox().GetCenter(), p3);

  EXPECT_EQ(a1.GetBox().x1(), 1.0f);
  EXPECT_EQ(a1.GetBox().y1(), 1.0f);
  EXPECT_EQ(a1.GetBox().x2(), 2.0f);
  EXPECT_EQ(a1.GetBox().y2(), 2.0f);

  EXPECT_EQ(a2.GetBox().x2(), 2.5f);
  EXPECT_EQ(a2.GetBox().x1(), 1.5f);
}

