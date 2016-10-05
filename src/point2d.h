#pragma once

#include <cmath>
#include <iostream>
#include <functional>

class Point

{
public:
  Point()=default;

  Point(Point const & obj)
    : m_x(obj.m_x), m_y(obj.m_y)
  {}

  Point(float x, float y)
    : m_x(x), m_y(y)
  {}

  float & x() {return m_x;}
  float & y() {return m_y;}

  float const & x() const {return m_x;}
  float const & y() const {return m_y;}

private:
  float m_x=0.0, m_y=0.0;
};


