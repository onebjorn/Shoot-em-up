#pragma once

#include <cmath>
#include <iostream>
#include <functional>

float const kEps = 1e-5;

using namespace std;

class Point2D
{
public:
  Point2D()=default;

  Point2D ( Point2D  const & obj)
    : m_x(obj.m_x), m_y(obj.m_y)
  {}

  Point2D(float x, float y)
    : m_x(x), m_y(y)
  {}

  // Конструктор со списком инициализации.
  Point2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_x, &m_y };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Конструктор перемещения
  Point2D(Point2D && obj)
  {
    swap(m_x, obj.x());
    swap(m_y, obj.y());
  }

  // Оператор присваивания.
  Point2D & operator = (Point2D const & obj)
  {
    if (this == &obj) return *this;
    m_x = obj.m_x;
    m_y = obj.m_y;
    return *this;
  }

  // Оператор перемещения
  Point2D & operator = (Point2D && obj)
  {
    if (this == &obj) return *this;
    swap(m_x, obj.x());
    swap(m_y, obj.y());
    return *this;
  }

  // Оператор логического равенства.
  bool operator == (Point2D const & obj) const
  {
    return EqualWithEps(m_x, obj.m_x) && EqualWithEps(m_y, obj.m_y);
  }


  // Оператор логического неравенства.
  bool operator != (Point2D const & obj) const
  {
    return !operator==(obj);
  }
  // Оператор меньше.
  bool operator < (Point2D const & obj) const
  {
    if (m_x < obj.m_x) return true;
    return m_y < obj.m_y;
  }
  // Сложение.
  Point2D operator + (Point2D const & obj) const
  {
    return { m_x + obj.m_x, m_y + obj.m_y };
  }
  // Вычитание.
  Point2D operator - (Point2D const & obj) const
  {
    return { m_x - obj.m_x, m_y - obj.m_y };
  }
  // Умножение на число.
  Point2D operator * (float scale) const
  {
    return { m_x * scale, m_y * scale };
  }
  // Деление на число.
  Point2D operator / (float scale) const
  {
  //TODO: обработать деление на 0.
    return { m_x / scale, m_y / scale };
  }
  // Математическое отрицание.
  Point2D operator - () const
  {
    return { -m_x, -m_y };
  }
  Point2D & operator += (Point2D const & obj)
  {
    m_x += obj.m_x;
    m_y += obj.m_y;
    return *this;
  }
  Point2D & operator -= (Point2D const & obj)
  {
    m_x -= obj.m_x;
    m_y -= obj.m_y;
    return *this;
  }
  Point2D & operator *= (float scale)
  {
    m_x *= scale;
    m_y *= scale;
    return *this;
  }
  Point2D & operator /= (float scale)
  {
    //TODO: обработать деление на 0.
    m_x /= scale;
    m_y /= scale;
    return *this;
  }

  float & x() {return m_x;}
  float & y() {return m_y;}

  float const & x() const {return m_x;}
  float const & y() const {return m_y;}

private:
  float m_x=0.0, m_y=0.0;

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

};


