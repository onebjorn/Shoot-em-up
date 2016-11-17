#include "gtest/gtest.h"
#include "../src/game/obstacle.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(Obstacle_test, test_construction)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Obstacle o1 = { p1, p2 };

  EXPECT_EQ(o1.GetHealth(), kObstacleHealth);
  EXPECT_EQ(o1.GetBox().x1(), 1.0f);
  EXPECT_EQ(o1.GetBox().x2(), 2.0f);
  EXPECT_EQ(o1.GetBox().y1(), 1.0f);
  EXPECT_EQ(o1.GetBox().y2(), 2.0f);
}

TEST(Obstacle_test, test_exception)
{
  Point2D p1 = { 3.0f, 3.0f };
  Point2D p2 = { 4.0f, 4.0f };
  Obstacle o3 = { p1, p2 };

  EXPECT_THROW(o3.RemoveObstacleHealth(101.0f), invalid_argument);
}
