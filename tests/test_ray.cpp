#include "gtest/gtest.h"
#include "ray2d_maybe.h"
#include <sstream>
#include <unordered_set>

TEST(test_ray, test_construction)
{
  //Default creation
  Ray r1;
  EXPECT_EQ(r1.x0(), 0.0f);
  EXPECT_EQ(r1.y0(), 0.0f);
  EXPECT_EQ(r1.GetDirect(0), 0.0f);
  EXPECT_EQ(r1.GetDirect(1), 0.0f);


  //Create the ray
  Ray r3={1.0f, 2.0f, 4.0f, 6.0f};
  EXPECT_EQ(r3.x0(), 1.0f);
  EXPECT_EQ(r3.y0(), 2.0f);
  EXPECT_EQ(r3.GetDirect(0), 0.6f);
  EXPECT_EQ(r3.GetDirect(1), 0.8f);

  Ray r4=r3;
  EXPECT_EQ(r4, r3);
}


