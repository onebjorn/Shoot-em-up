#include <iostream>
#pragma once
#include <functional>
#include <cmath>

using namespace std;

float const Eps = 1e-5f;


/* Класс двумерного прямоугольника Box2d*/
/*  */
class Box2D
{
public:

  Box2D() = default;

  float m_box2d_x_center = 0.0f;  // Иницилизация координат центра
  float m_box2d_y_center = 0.0f;
  float m_box2d_lenght = 0.0f;    // Длина и высота
  float m_box2d_height = 0.0f;

  Box2D(float x1, float y1, float x2, float y2) // Обычный конструктор с параметрами и проверкой на корректность.
  {
    if ( x2 > x1 )
    {
      m_box2d_x1 = x1;
      m_box2d_x2 = x2;
    }
    else if ( x1 == x2 )
    {
      cout<< "Enter correct box!"<<endl;
    }
    else
    {
      m_box2d_x1 = x2;
      m_box2d_x2 = x1;
    }
    if ( y2 > y1 )
    {
      m_box2d_y1 = y1;
      m_box2d_y2 = y2;
    }
    else if ( y1 == y2 )
    {
      cout<< "Enter correct box!"<<endl;
    }
    else
    {
      m_box2d_y1 = y2;
      m_box2d_y2 = y1;
    }
  }

  Box2D( const Box2D & obj)    // Конструктор копирования.
    : m_box2d_x1(obj.m_box2d_x1)
    , m_box2d_y1(obj.m_box2d_y1)
    , m_box2d_x2(obj.m_box2d_x2)
    , m_box2d_y2(obj.m_box2d_y2)
  {}

  Box2D(std::initializer_list<float> const & lst)     // Конструктор со списком инициализации.
  {
    float * vals[] = { &m_box2d_x1, &m_box2d_y1, &m_box2d_x2, &m_box2d_y2 };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
    if ( m_box2d_x1 > m_box2d_x2 && m_box2d_y1 > m_box2d_y2)
    {
      float * vals[] = { &m_box2d_x2, &m_box2d_y2, &m_box2d_x1, &m_box2d_y1 };
      int const count = sizeof(vals) / sizeof(vals[0]);
      auto it = lst.begin();
      for (int i = 0; i < count && it != lst.end(); i++, ++it)
        *vals[i] = *it;
    }
    if ( m_box2d_x1 > m_box2d_x2 && m_box2d_y1 < m_box2d_y2)
    {
      float * vals[] = { &m_box2d_x2, &m_box2d_y1, &m_box2d_x1, &m_box2d_y2 };
      int const count = sizeof(vals) / sizeof(vals[0]);
      auto it = lst.begin();
      for (int i = 0; i < count && it != lst.end(); i++, ++it)
        *vals[i] = *it;
    }
    if ( m_box2d_x1 < m_box2d_x2 && m_box2d_y1 > m_box2d_y2)
    {
      float * vals[] = { &m_box2d_x1, &m_box2d_y2, &m_box2d_x2, &m_box2d_y1 };
      int const count = sizeof(vals) / sizeof(vals[0]);
      auto it = lst.begin();
      for (int i = 0; i < count && it != lst.end(); i++, ++it)
        *vals[i] = *it;
    }
  }

  Box2D & operator = (Box2D const & obj)     // Оператор присваивания.
  {
    if (this == &obj) return *this;
    if (obj.m_box2d_x1 < obj.m_box2d_x2)
    {
      m_box2d_x1 = obj.m_box2d_x1;
      m_box2d_x2 = obj.m_box2d_x2;
    }
    else
    {
      m_box2d_x2 = obj.m_box2d_x1;
      m_box2d_x1 = obj.m_box2d_x2;
    }
    if (obj.m_box2d_y1 < obj.m_box2d_y2)
    {
      m_box2d_y1 = obj.m_box2d_y1;
      m_box2d_y2 = obj.m_box2d_y2;
    }
    else
    {
      m_box2d_y2 = obj.m_box2d_y1;
      m_box2d_y1 = obj.m_box2d_y2;
    }
    return *this;
  }

  bool operator == (Box2D const & obj) const        // Оператор логического равенства.
  {
    return EqualWithEps(m_box2d_x1, obj.m_box2d_x1) && EqualWithEps(m_box2d_y1, obj.m_box2d_y1)
        && EqualWithEps(m_box2d_x2, obj.m_box2d_x2) && EqualWithEps(m_box2d_y2, obj.m_box2d_y2);
  }


  void boxGeometry()
  {
    m_box2d_x_center = (m_box2d_x2 + m_box2d_x1) / 2.0f;
    m_box2d_y_center = (m_box2d_y2 + m_box2d_y1) / 2.0f;
    m_box2d_lenght = fabs(m_box2d_x2 - m_box2d_x1);
    m_box2d_height = fabs(m_box2d_y2 - m_box2d_y1);
 }

  int boxCrossing( Box2D&obj1, Box2D&obj2 )
  {
    obj1.boxGeometry();
    obj2.boxGeometry();
    float m_rho_x = 0.0f, m_rho_y = 0.0f;
    float m_l = 0.0f, m_h = 0.0f;

    m_rho_x =fabs(obj1.m_box2d_x_center - obj2.m_box2d_x_center); // Вычисление растояния между центрами по осям x и y.
    m_rho_y = fabs(obj1.m_box2d_y_center - obj2.m_box2d_y_center);

    m_l = (obj1.m_box2d_lenght + obj2.m_box2d_lenght) / 2.0f; // Вычисление пересечения.
    m_h = (obj1.m_box2d_height + obj2.m_box2d_height) / 2.0f;

    if  (m_rho_x > m_l && m_rho_y > m_h)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  Box2D operator + (Box2D const & obj) const  // Сложение.
  {
    return { m_box2d_x1 + obj.m_box2d_x1, m_box2d_y1 + obj.m_box2d_y1,
          m_box2d_x2 + obj.m_box2d_x2, m_box2d_y2 + obj.m_box2d_y2 };
  }
  Box2D operator - (Box2D const & obj) const // Сложение.
  {
    return { m_box2d_x1 - obj.m_box2d_x1, m_box2d_y1 - obj.m_box2d_y1,
          m_box2d_x2 - obj.m_box2d_x2, m_box2d_y2 - obj.m_box2d_y2 };
  }
  Box2D operator * (float scale) const // Умножение на число.
  {
    return { m_box2d_x1 * scale, m_box2d_y1 * scale, m_box2d_x2 * scale, m_box2d_y2 * scale};
  }
  Box2D operator / (float scale) const // Умножение на число.
  {
    if ( scale != 0.0f )
    {
      return { m_box2d_x1 / scale, m_box2d_y1 / scale, m_box2d_x2 / scale, m_box2d_y2 / scale};
    }
    else
    {
      return { m_box2d_x1, m_box2d_y1, m_box2d_x2, m_box2d_y2};
    }
  }

  Box2D & operator += (Box2D const & obj)
  {
    m_box2d_x1 += obj.m_box2d_x1;
    m_box2d_y1 += obj.m_box2d_y1;
    m_box2d_x2 += obj.m_box2d_x2;
    m_box2d_y2 += obj.m_box2d_y2;
    return *this;
  }

  Box2D & operator -= (Box2D const & obj)
  {
    m_box2d_x1 -= obj.m_box2d_x1;
    m_box2d_y1 -= obj.m_box2d_y1;
    m_box2d_x2 -= obj.m_box2d_x2;
    m_box2d_y2 -= obj.m_box2d_y2;
    return *this;
  }

  Box2D & operator *= ( float scale)
  {
    m_box2d_x1 *= scale;
    m_box2d_y1 *= scale;
    m_box2d_x2 *= scale;
    m_box2d_y2 *= scale;
    return *this;
  }

  Box2D & operator /= ( float scale)
  {
    if( scale != 0.0f)
    {
      m_box2d_x1 /= scale;
      m_box2d_y1 /= scale;
      m_box2d_x2 /= scale;
      m_box2d_y2 /= scale;
      return *this;
    }
    else
    {
      m_box2d_x1 /= 1.0f;
      m_box2d_y1 /= 1.0f;
      m_box2d_x2 /= 1.0f;
      m_box2d_y2 /= 1.0f;
      return *this;
    }
  }


  float & x1() { return m_box2d_x1; }
  float & y1() { return m_box2d_y1; }
  float & x2() { return m_box2d_x2; }
  float & y2() { return m_box2d_y2; }

  ~Box2D()
  {}

private:
  float m_box2d_x1 = 0.0;     // Инициализация координат прямоугольника
  float m_box2d_y1 = 0.0;
  float m_box2d_x2 = 0.0;
  float m_box2d_y2 = 0.0;

bool EqualWithEps(float v1, float v2) const
{
return fabs(v1 - v2) < Eps;
}
};
