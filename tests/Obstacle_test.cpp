#include "gtest/gtest.h"
#include "obstacle.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(Obstacle_test, test_construction)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Obstacle o1 = { p1, p2 };

  EXPECT_EQ(o1.GetHealth(), ObstacleHealth);
  EXPECT_EQ(o1.GetBox().x1(), 1.0f);
  EXPECT_EQ(o1.GetBox().x2(), 2.0f);
  EXPECT_EQ(o1.GetBox().y1(), 1.0f);
  EXPECT_EQ(o1.GetBox().y2(), 2.0f);
}

TEST(Obstacle_test, test_move)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Obstacle o1 = { p1, p2 };

  Obstacle o2 = move(o1);
  EXPECT_EQ(o2.GetBox().x1(), 1.0f);
}
