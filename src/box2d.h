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

  Box2D(std::initializer_list<Point2D> const & lst)     // Конструктор со списком инициализации.
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

  Box2D(std::initializer_list<float> const & lst)
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

  Box2D & operator = (Box2D const & obj)     // Оператор присваивания.
  {
    if (this == &obj) return *this;
    m_boxMin = obj.m_boxMin;
    m_boxMax = obj.m_boxMax;
    return *this;
  }

  bool operator == (Box2D const & obj) const        // Оператор логического равенства.
  {
    return EqualWithEps(m_boxMin.x(), obj.m_boxMin.x()) && EqualWithEps(m_boxMin.y(), obj.m_boxMin.y())
        && EqualWithEps(m_boxMax.x(), obj.m_boxMax.x()) && EqualWithEps(m_boxMax.y(), obj.m_boxMax.y());
  }

  Box2D operator + (Box2D const & obj) const  // Сложение.
  {
    return { m_boxMin.x() + obj.m_boxMin.x(), m_boxMin.y() + obj.m_boxMin.y(),
          m_boxMax.x() + obj.m_boxMax.x(), m_boxMax.y() + obj.m_boxMax.y() };
  }
  Box2D operator - (Box2D const & obj) const // Сложение.
  {
    return { m_boxMin.x() - obj.m_boxMin.x(), m_boxMin.y() - obj.m_boxMin.y(),
          m_boxMax.x() - obj.m_boxMax.x(), m_boxMax.y() - obj.m_boxMax.y() };
  }
  Box2D operator * (float scale) const // Умножение на число.
  {
    return { m_boxMin.x() * scale, m_boxMin.y() * scale, m_boxMax.x() * scale, m_boxMax.y() * scale};
  }
  Box2D operator / (float scale) const // Деление на число.
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
    if (a.m_boxMax.x() < b.m_boxMin.x()) return false; // a is left of b
    if (a.m_boxMin.x() > b.m_boxMax.x()) return false; // a is right of b
    if (a.m_boxMax.y() < b.m_boxMin.y()) return false; // a is above b
    if (a.m_boxMin.y() > b.m_boxMax.y()) return false; // a is below b
    return true; // boxes overlap
  }

  ~Box2D()
  {}

private:
  Point2D m_boxMin = { 0.0f, 0.0f };
  Point2D m_boxMax = { 0.0f, 0.0f };
  //Проверка положения точек
  void checkBox2D()
  {
    if (m_boxMin.x() > m_boxMax.x()) std::swap(m_boxMax.x(), m_boxMin.x());
    if (m_boxMin.y() > m_boxMax.y()) std::swap(m_boxMin.y(), m_boxMax.y());
  }

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < Eps;
  }
};
