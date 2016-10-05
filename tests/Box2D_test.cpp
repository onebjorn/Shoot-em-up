#include "gtest/gtest.h"
#include "Box2D.h"
#include <sstream>
#include <unordered_set>

TEST(Box2D_test, test_construction)
{
  Box2D p1;
  EXPECT_EQ(p1.x1(), 0.0);
  EXPECT_EQ(p1.y1(), 0.0);
  EXPECT_EQ(p1.x2(), 0.0);
  EXPECT_EQ(p1.y2(), 0.0);

  Box2D p2 = { 1.2f, 2.4f, 1.2f, 2.9f};
  EXPECT_EQ(p2.x1(), 1.2f);
  EXPECT_EQ(p2.y1(), 2.4f);
  EXPECT_EQ(p2.x2(), 1.2f);
  EXPECT_EQ(p2.y2(), 2.9f);

  Box2D p3 = p2;
  EXPECT_EQ(p3, p2);
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
  p1 = { 1.2f, 2.4f, 1.2f, 2.8f };
  EXPECT_EQ(p1, Box2D(1.2f, 2.4f, 1.2f, 2.8f));
}

TEST(Box2D_test, test_calculus)
{
  Box2D p1 = { 1.2f, 2.4f , 1.2f, 2.7f};
  Box2D p2 = { 1.0f, 2.0f, 1.2f, 2.8f };
  EXPECT_EQ(p1 + p2, Box2D(2.2f, 4.4f, 2.4f, 5.5f));
  EXPECT_EQ(p1 - p2, Box2D(0.2f, 0.4f, 0.0f, -0.1f));
  EXPECT_EQ(p1 * 2.0f, Box2D(2.4f, 4.8f, 2.4f, 5.4f));
  EXPECT_EQ(p1 / 2.0f, Box2D(0.6f, 1.2f, 0.6f, 1.35f));
}

TEST(Box2D_test, test_operators)
{
  Box2D p1 = { 1.2f, 2.4f , 1.2f, 2.7f};
  p1 += { 1.2f, 2.4f , 1.2f, 2.7f};
  EXPECT_EQ(p1, Box2D(2.4f, 4.8f, 2.4f, 5.4f));
  p1 -= { 1.2f, 2.4f, 1.2f, 2.7f };
  EXPECT_EQ(p1, Box2D(1.2f, 2.4f, 1.2f, 2.7f));
  p1 *= 2.0f;
  EXPECT_EQ(p1, Box2D(2.4f, 4.8f, 2.4f, 5.4f));
  p1 /= 2.0f;
  EXPECT_EQ(p1, Box2D(1.2f, 2.4f, 1.2f, 2.7f));
}


