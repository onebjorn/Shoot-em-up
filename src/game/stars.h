#pragma once
#include "geometry/point2d.h"
#include "../include/config_stat.h"
#include <vector>
#include <cmath>

using MStars = vector<Point2D>;

class Stars
{
public:

  Stars()
  {
    Create(kStars);
  }

  Stars(int const size)
  {
    Create(size);
  }

  MStars const & GetStars() const { return m_stars; }

  ~Stars() = default;

private:

  int m_number;

  void Create(int const size)
  {
    m_number = size;
    for (auto i = 0; i < size; i++)
    {
      m_stars.push_back(Point2D(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
    }
  }

  vector<Point2D> m_stars;
};

