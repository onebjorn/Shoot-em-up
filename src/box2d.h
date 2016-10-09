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
    : m_boxMin(min(x1,x2), min(y1,y2))
    , m_boxMax(max(x1,x2), max(y1,y2))
  {}

  Box2D (Point2D const & p1, Point2D const & p2)
  {
    m_boxMin = { min(p1.x(), p2.x()), min(p1.y(), p2.y()) };
    m_boxMax = { max(p1.x(), p2.x()), max(p1.y(), p2.y()) };
  }

  Box2D (Box2D const  & obj)    // Конструктор копирования.
    : m_boxMin(obj.m_boxMin)
    , m_boxMax(obj.m_boxMax)
  {}

  Box2D(initializer_list<Point2D> const & lst)     // Конструктор со списком инициализации из точек.
  {
    Point2D * arr[] = { & m_boxMin, & m_boxMax };
    int const count = sizeof(arr) / sizeof(arr[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
    {
      *arr[i] = *it;
    }
    checkBox2D();
  }

  Box2D(initializer_list<float> const & lst)    // Конструктор со списком инициализации из координат.
  {
    float * arr[] = { & m_boxMin.x(), & m_boxMin.y(), & m_boxMax.x(), & m_boxMax.y() };
    int const count = sizeof(arr) / sizeof(arr[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
    {
      *arr[i] = *it;
    }
    checkBox2D();
  }

  Box2D(Box2D && obj) // Конструктор перемещения
  {
    m_boxMin = move(obj.m_boxMin);
    m_boxMax =move(obj.m_boxMax);
}

  Box2D & operator = (Box2D const & obj)     // Оператор присваивания.
  {
    if (this == &obj) return *this;
    m_boxMin = obj.m_boxMin;
    m_boxMax = obj.m_boxMax;
    return *this;
  }

  Box2D & operator = (Box2D && obj) //  Оператор перемещения
  {
    if (this == &obj) return *this;
    m_boxMin = std::move(obj.m_boxMin);
    m_boxMax = std::move(obj.m_boxMax);
    return *this;
  }

  bool operator == (Box2D const & obj) const        // Оператор логического равенства.
  {
    return EqualWithEps(m_boxMin.x(), obj.m_boxMin.x()) && EqualWithEps(m_boxMin.y(), obj.m_boxMin.y())
        && EqualWithEps(m_boxMax.x(), obj.m_boxMax.x()) && EqualWithEps(m_boxMax.y(), obj.m_boxMax.y());
  }

  Box2D operator + (Box2D const & obj) const
  {
    return { m_boxMin.x() + obj.m_boxMin.x(), m_boxMin.y() + obj.m_boxMin.y(),
          m_boxMax.x() + obj.m_boxMax.x(), m_boxMax.y() + obj.m_boxMax.y() };
  }
  Box2D operator - (Box2D const & obj) const
  {
    return { m_boxMin.x() - obj.m_boxMin.x(), m_boxMin.y() - obj.m_boxMin.y(),
          m_boxMax.x() - obj.m_boxMax.x(), m_boxMax.y() - obj.m_boxMax.y() };
  }
  Box2D operator * (float scale) const
  {
    return { m_boxMin.x() * scale, m_boxMin.y() * scale, m_boxMax.x() * scale, m_boxMax.y() * scale};
  }
  Box2D operator / (float scale) const
  {
    return { m_boxMin.x() / scale, m_boxMin.y() / scale, m_boxMax.x() / scale, m_boxMax.y() / scale};
  }

  Box2D & operator += (Box2D const & obj)
  {
    m_boxMin.x() += obj.m_boxMin.x();
    m_boxMin.y() += obj.m_boxMin.y();
    m_boxMax.x() += obj.m_boxMax.x();
    m_boxMax.y() += obj.m_boxMax.y();
    return *this;
  }

  Box2D & operator -= (Box2D const & obj)
  {
    m_boxMin.x() -= obj.m_boxMin.x();
    m_boxMin.y() -= obj.m_boxMin.y();
    m_boxMax.x() -= obj.m_boxMax.x();
    m_boxMax.y() -= obj.m_boxMax.y();
    return *this;
  }

  Box2D & operator *= ( float scale)
  {
    m_boxMin.x() *= scale;
    m_boxMin.y() *= scale;
    m_boxMax.x() *= scale;
    m_boxMax.y() *= scale;
    return *this;
  }

  Box2D & operator /= ( float scale)
  {
    m_boxMin.x() /= scale;
    m_boxMin.y() /= scale;
    m_boxMax.x() /= scale;
    m_boxMax.y() /= scale;
    return *this;
  }

  float const & x1() const { return m_boxMin.x(); }
  float const & y1() const { return m_boxMin.y(); }
  float const & x2() const { return m_boxMax.x(); }
  float const & y2() const { return m_boxMax.y(); }

  bool BoxesIntersect( Box2D const & a, Box2D const & b)
  {
    if (a.m_boxMax.x() < b.m_boxMin.x()) return false;
    if (a.m_boxMin.x() > b.m_boxMax.x()) return false;
    if (a.m_boxMax.y() < b.m_boxMin.y()) return false;
    if (a.m_boxMin.y() > b.m_boxMax.y()) return false;
    return true;
  }

  ~Box2D()
  {}

private:
  Point2D m_boxMin = { 0.0f, 0.0f };
  Point2D m_boxMax = { 0.0f, 0.0f };

  void checkBox2D()   //Проверка положения точек
  {
    if (m_boxMin.x() > m_boxMax.x()) swap(m_boxMax.x(), m_boxMin.x());
    if (m_boxMin.y() > m_boxMax.y()) swap(m_boxMin.y(), m_boxMax.y());
  }

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < Eps;
  }
};
