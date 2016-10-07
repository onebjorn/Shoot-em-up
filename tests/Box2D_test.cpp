#include "gtest/gtest.h"
#include "Box2D.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(Box2D_test, test_construction)
{
  Box2D p1;
  EXPECT_EQ(p1.x1(), 0.0);
  EXPECT_EQ(p1.y1(), 0.0);
  EXPECT_EQ(p1.x2(), 0.0);
  EXPECT_EQ(p1.y2(), 0.0);

  Box2D p2(1.9f, 10, 1.2f, 1);
  EXPECT_EQ(p2.x1(), 1.2f);
  EXPECT_EQ(p2.x2(), 1.9f);
  EXPECT_EQ(p2.y1(), 1.0f);
  EXPECT_EQ(p2.y2(), 10.0f);

  Box2D p3 = {1.9f, 10, 1.2f, 100};
  EXPECT_EQ(p3.x1(), 1.2f);
  EXPECT_EQ(p3.x2(), 1.9f);
  EXPECT_EQ(p3.y1(), 10.0f);
  EXPECT_EQ(p3.y2(), 100.0f);

  Box2D p4 = p3;
  EXPECT_EQ(p3, p4);
}

TEST(Box2D_test, test_initializer_list)
{
  Box2D p1 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
  EXPECT_EQ(p1.x1(), 1.0f);
  EXPECT_EQ(p1.y1(), 2.0f);
  Box2D p2 = { 1.0f };
  EXPECT_EQ(p2.x1(), 1.0f);
  EXPECT_EQ(p2.y1(), 0.0f);
}

TEST(Box2D_test, test_assignment)
{
  Box2D p1;
  p1 = { 1.2f, 2.8f, 1.8f, 2.4f };
  EXPECT_EQ(p1, Box2D(1.2f, 2.4f, 1.8f, 2.8f));
}

TEST(Box2D_test, test_calculus)
{
  Box2D p1 = { 1.2f, 2.4f , 1.5f, 2.7f};
  Box2D p2 = { 1.0f, 2.0f, 1.2f, 2.8f };
  EXPECT_EQ(p1 + p2, Box2D(2.2f, 4.4f, 2.7f, 5.5f));
  EXPECT_EQ(p1 - p2, Box2D(0.2f, 0.4f, 0.3f, -0.1f));
  EXPECT_EQ(p1 * 2.0f, Box2D(2.4f, 4.8f, 3.0f, 5.4f));
  EXPECT_EQ(p1 / 2.0f, Box2D(0.6f, 1.2f, 0.75f, 1.35f));
}

TEST(Box2D_test, test_operators)
{
  Box2D p1 = { 1.2f, 2.4f , 1.6f, 2.8f};
  p1 += { 1.2f, 2.4f , 1.6f, 2.8f};
  EXPECT_EQ(p1, Box2D(2.4f, 4.8f, 3.2f, 5.6f));
  p1 -= { 1.2f, 2.4f, 1.6f, 2.8f };
  EXPECT_EQ(p1, Box2D(1.2f, 2.4f, 1.6f, 2.8f));
  p1 *= 2.0f;
  EXPECT_EQ(p1, Box2D(2.4f, 4.8f, 3.2f, 5.6f));
 p1 /= 2.0f;
  EXPECT_EQ(p1, Box2D(1.2f, 2.4f, 1.6f, 2.8f));
}
TEST(Box2D_test, test_cross)
{
   Box2D p1 = { 1.0f, 1.0f , 4.0f, 2.0f};
   Box2D p2 = { 1.0f, 3.0f , 4.0f, 4.0f};
   Box2D p3 = { 2.0f, 1.0f , 3.0f, 5.0f};
   EXPECT_EQ(1, p1.BoxesIntersect(p1,p3));
   EXPECT_EQ(1, p2.BoxesIntersect(p2,p3));
   EXPECT_EQ(0, p1.BoxesIntersect(p1,p2));
}


