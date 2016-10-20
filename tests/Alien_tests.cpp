#include "gtest/gtest.h"
#include "../include/config_stat.h"
#include "alien.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(Alien_test, test_construction)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Point2D p3 = { 1.5f, 1.5f };
  Box2D b1 = { 0.5f, 1.5f, 1.5f, 2.5f };

  Alien a1(p1, p2, 0.0f, 0.0f );
  Alien a2(1.5f, 1.5f, 2.5f, 2.5f);
  Alien a3(b1);


  EXPECT_EQ(a1.GetBox().GetCenter(), p3);
  EXPECT_EQ(a1.GetHealth(), 0.0f);

  EXPECT_EQ(a1.GetBox().x1(), 1.0f);
  EXPECT_EQ(a1.GetBox().y1(), 1.0f);
  EXPECT_EQ(a1.GetBox().x2(), 2.0f);
  EXPECT_EQ(a1.GetBox().y2(), 2.0f);


  EXPECT_EQ(a2.GetHealth(), 100.0f);
  EXPECT_EQ(a2.GetSpeed(), AlienSpeed);
  EXPECT_EQ(a2.GetBox().x2(), 2.5f);
  EXPECT_EQ(a2.GetBox().x1(), 1.5f);
}

TEST(Alien_test, test_cross)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Box2D b1 = { 0.5f, 1.5f, 1.5f, 2.5f };

  Alien a1(p1, p2, 0.0f, 0.0f );
  Alien a2(1.5f, 1.5f, 2.5f, 2.5f);
  Alien a3(b1);

  EXPECT_EQ(a2.ObjectsIntersect(a1,a2), true);
  EXPECT_EQ(a3.ObjectsIntersect(a1,a3), true);
  EXPECT_EQ(a2.ObjectsIntersect(a2,a3), true);
}

TEST(Alien_test, test_move)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Box2D b1 = { 1.5f, 1.5f, 0.5f, 2.5f };

  Alien a1(p1, p2, 0.0f, 0.0f);
  Alien a2(1.5f, 1.5f, 2.5f, 2.5f);
  Alien a3(b1);

  a3 = move(a2);
  EXPECT_EQ(a3.GetBox().x1(), 1.5f);
  Alien a4 = move(a3);
  EXPECT_EQ(a4.GetBox().x1(), 1.5f);
  Alien a5 = move(b1);
  EXPECT_EQ(a5.GetBox().x2(), 1.5f);
}

TEST(Alien_test, test_exception)
{
  Box2D b1 = {1.0f, 2.0f, 3.0f, 4.0f};
  Alien a6(b1);

  EXPECT_THROW(a6.RemoveAlienHealth(101.0f), invalid_argument);
  EXPECT_THROW(a6.SetAlienHealth(101.0f), invalid_argument);
}
