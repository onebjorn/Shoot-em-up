#include "gtest/gtest.h"
#include "../include/config_stat.h"
#include "alien.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(Alien2D_test, test_construction)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Point2D p3 = { 1.5f, 1.5f };
  Box2D b1 = { 0.5f, 1.5f, 1.5f, 2.5f };

  Alien2D a1(p1, p2, 0.0f, 0.0f );
  Alien2D a2( 1.5f, 1.5f, 2.5f, 2.5f);
  Alien2D a3(b1);


  EXPECT_EQ(a1.GetCenter(), p3);
  EXPECT_EQ(a1.GetHealth(), 0.0f);
  EXPECT_EQ(a1.x2(), 2.0f);
  EXPECT_EQ(a1.y2(), 2.0f);
  EXPECT_EQ(a1.x1(), 1.0f);
  EXPECT_EQ(a1.y1(), 1.0f);


  EXPECT_EQ(a2.GetHealth(), 100.0f);
  EXPECT_EQ(a2.GetSpeed(), AlienSpeed);
  EXPECT_EQ(a2.x2(), 2.5f);
  EXPECT_EQ(a2.x1(), 1.5f);
}

TEST(Alien2D_test, test_cross)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Box2D b1 = { 0.5f, 1.5f, 1.5f, 2.5f };

  Alien2D a1(p1, p2, 0.0f, 0.0f );
  Alien2D a2(1.5f, 1.5f, 2.5f, 2.5f);
  Alien2D a3(b1);

  EXPECT_EQ(a2.BoxesIntersect(a1,a2), true);
  EXPECT_EQ(a3.BoxesIntersect(a1,a3), true);
  EXPECT_EQ(a2.BoxesIntersect(a2,a3), true);
}

TEST(Alien2D_test, test_operators)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 2.0f, 2.0f };
  Box2D b1 = { 0.5f, 1.5f, 1.5f, 2.5f };

  Alien2D a1(p1, p2, 0.0f, 0.0f );
  a1 += b1;
  EXPECT_EQ(a1.x1(), 1.5f);
  EXPECT_EQ(a1.y1(), 2.5f);
}
