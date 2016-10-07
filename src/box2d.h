#include <iostream>
#pragma once
#include "point2d.h"
#include <functional>
#include <cmath>

using namespace std;

float const Eps = 1e-5f;

/* Класс двумерного прямоугольника Box2d*/
class Box2D
{
public:

  Box2D() = default;

  Box2D(float x1, float y1, float x2, float y2)
    : m_p1(min(x1,x2), min(y1,y2))
    , m_p2(max(x1,x2), max(y1,y2))
  {}

  Box2D ( Point2D const & p1, Point2D const & p2)
  {
    m_p1 = {min(p1.x(), p2.x()), min(p1.y(), p2.y())};
    m_p2 = {max(p1.x(), p2.x()), max(p1.y(), p2.y())};
  }

  Box2D (Box2D const  & obj)    // Конструктор копирования.
    : m_p1(obj.m_p1)
    , m_p2(obj.m_p2)
  {}

  Box2D(std::initializer_list<Point2D> const & lst)     // Конструктор со списком инициализации.
  {
    Point2D * arr[] = { & m_p1, & m_p2 };
    int const count = sizeof(arr) / sizeof(arr[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
    {
      *arr[i] = *it;
    }
    checkBox2D();
  }

  Box2D(std::initializer_list<float> const & lst)
  {
    float * arr[] = { & m_p1.x(), & m_p1.y(), & m_p2.x(), & m_p2.y() };
    int const count = sizeof(arr) / sizeof(arr[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
    {
      *arr[i] = *it;
    }
    checkBox2D();
  }

  Box2D & operator = (Box2D const & obj)     // Оператор присваивания.
  {
    if (this == &obj) return *this;
    m_p1.x() = min(obj.m_p1.x(), obj.m_p2.x());
    m_p1.y() = min(obj.m_p1.y(), obj.m_p2.y());
    m_p2.x() = max(obj.m_p1.x(), obj.m_p2.x());
    m_p2.y() = max(obj.m_p1.y(), obj.m_p2.y());
    return *this;
  }

  bool operator == (Box2D const & obj) const        // Оператор логического равенства.
  {
    return EqualWithEps(m_p1.x(), obj.m_p1.x()) && EqualWithEps(m_p1.y(), obj.m_p1.y())
        && EqualWithEps(m_p2.x(), obj.m_p2.x()) && EqualWithEps(m_p2.y(), obj.m_p2.y());
  }

  Box2D operator + (Box2D const & obj) const  // Сложение.
  {
    return { m_p1.x() + obj.m_p1.x(), m_p1.y() + obj.m_p1.y(),
          m_p2.x() + obj.m_p2.x(), m_p2.y() + obj.m_p2.y() };
  }
  Box2D operator - (Box2D const & obj) const // Сложение.
  {
    return { m_p1.x() - obj.m_p1.x(), m_p1.y() - obj.m_p1.y(),
          m_p2.x() - obj.m_p2.x(), m_p2.y() - obj.m_p2.y() };
  }
  Box2D operator * (float scale) const // Умножение на число.
  {
    return { m_p1.x() * scale, m_p1.y() * scale, m_p2.x() * scale, m_p2.y() * scale};
  }
  Box2D operator / (float scale) const // Деление на число.
  {
    return { m_p1.x() / scale, m_p1.y() / scale, m_p2.x() / scale, m_p2.y() / scale};
  }

  Box2D & operator += (Box2D const & obj)
  {
    m_p1.x() += obj.m_p1.x();
    m_p1.y() += obj.m_p1.y();
    m_p2.x() += obj.m_p2.x();
    m_p2.y() += obj.m_p2.y();
    return *this;
  }

  Box2D & operator -= (Box2D const & obj)
  {
    m_p1.x() -= obj.m_p1.x();
    m_p1.y() -= obj.m_p1.y();
    m_p2.x() -= obj.m_p2.x();
    m_p2.y() -= obj.m_p2.y();
    return *this;
  }

  Box2D & operator *= ( float scale)
  {
    m_p1.x() *= scale;
    m_p1.y() *= scale;
    m_p2.x() *= scale;
    m_p2.y() *= scale;
    return *this;
  }

  Box2D & operator /= ( float scale)
  {
    m_p1.x() /= scale;
    m_p1.y() /= scale;
    m_p2.x() /= scale;
    m_p2.y() /= scale;
    return *this;
  }

  float & x1() { return m_p1.x(); }
  float & y1() { return m_p1.y(); }
  float & x2() { return m_p2.x(); }
  float & y2() { return m_p2.y(); }

  int BoxesIntersect( Box2D const & a, Box2D const & b)
  {
    if (a.m_p2.x() < b.m_p1.x()) return 0; // a is left of b
    if (a.m_p1.x() > b.m_p2.x()) return 0; // a is right of b
    if (a.m_p2.y() < b.m_p1.y()) return 0; // a is above b
    if (a.m_p1.y() > b.m_p2.y()) return 0; // a is below b
    return 1; // boxes overlap
  }

  ~Box2D()
  {}

private:
  Point2D m_p1 = { 0.0f, 0.0f };
  Point2D m_p2 = { 0.0f, 0.0f };
  //Проверка положения точек
  void checkBox2D()
  {
    if (m_p1.x() > m_p2.x())
    {
      m_p1.x() += m_p2.x();
      m_p2.x() = m_p1.x() - m_p2.x();
      m_p1.x() -= m_p2.x();
    }
    if (m_p1.y() > m_p2.y())
    {
      m_p1.y() += m_p2.y();
      m_p2.y() = m_p1.y() - m_p2.y();
      m_p1.y() -= m_p2.y();
    }
  }

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < Eps;
  }
};
