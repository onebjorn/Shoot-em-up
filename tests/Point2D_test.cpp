#include "gtest/gtest.h"
#include "point2d.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

TEST(point2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Point2D p1;
  EXPECT_EQ(p1.x(), 0.0f);
  EXPECT_EQ(p1.y(), 0.0f);

  // Тест на создание объекта с параметрами.
  Point2D p2 = { 1.0f, 2.0f };
  EXPECT_EQ(p2.x(), 1.0f);
  EXPECT_EQ(p2.y(), 2.0f);

  // Тест на создание копии объекта.
  Point2D p3 = p2;
  EXPECT_EQ(p3, p2);
}

TEST(point2d_test, test_initializer_list)
{
  Point2D p1 = { 1.0f, 2.0f, 3.0f };
  EXPECT_EQ(p1.x(), 1.0f);
  EXPECT_EQ(p1.y(), 2.0f);

  Point2D p2 = { 1.0f };
  EXPECT_EQ(p2.x(), 1.0f);
  EXPECT_EQ(p2.y(), 0.0f);
}

TEST(point2d_test, test_move)
{
    Point2D p1 = { 1.0f, 2.0f };
    Point2D p2 = move(p1);
    Point2D p3;
    EXPECT_EQ(p2, Point2D(1.0f, 2.0f));
    EXPECT_EQ(p1, Point2D(0.0f, 0.0f));
    // move
    p3 = move(p2);
    EXPECT_EQ(p3, Point2D(1.0f, 2.0f));
    EXPECT_EQ(p2, Point2D(0.0f, 0.0f));
}

