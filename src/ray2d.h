#pragma once
/*
#ifndef M_PI
#define M_PI           3.14159265358979323846f
#endif
*/
#include <cmath>
#include <iostream>
#include <functional>
#include <initializer_list>
#include <box2d.h>
#include <point2d.h>


using namespace std;
float constexpr pi() { return acos(-1.0);}
class Ray2D
{
public:

  Ray2D() = default;

  Ray2D(Ray2D const & obj)
  {
    m_origin = obj.m_origin;
    m_direct[0] = obj.m_direct[0];
    m_direct[1] = obj.m_direct[1];
  }

  Ray2D(float x0, float y0, float phi)
  {
    if (phi < 0.0) phi = 2*pi() - fabs(phi);
    m_origin = Point2D(x0,y0);
    SetDirAngleParam(phi);
  }

  Ray2D(float x0, float y0, float x1, float y1)
  {
    m_origin = Point2D(x0,y0);
    Normalize(x0,y0,x1,y1);
    }

  Ray2D(std::initializer_list<float> const & lst)
  {
  float * vals[] = { &m_origin.x(), &m_origin.y(), &m_direct[0], &m_direct[1]};
  int const count = sizeof(vals) / sizeof(vals[0]);

  auto it = lst.begin();
  for (int i = 0; i < count && it != lst.end(); i++, ++it) *vals[i] = *it;
  int const n = lst.size();
  switch(n)
    {
    case 3:
      {
        SetDirAngleParam(*vals[2]);
        break;
      }
    case 4:
      {
        NormalizeArr(*vals);
        break;
     }
   }
  }

  float & GetDirect(int i)
  {
    return m_direct[i];
  }

  float const & GetDirect(int i) const
  {
    return m_direct[i];
  }

  float & x0() { return m_origin.x(); }
  float & y0() { return m_origin.y(); }

  float const & x() const { return m_origin.x();}
  float const & y() const { return m_origin.y();}

  bool Intersection(Box2D & b, Ray2D & a)
  {
    float tmin, tmax, tymin, tymax;

    if (a.GetDirect(0) >= 0.0)
      {
        tmin = (b.x1() - a.x0()) / a.GetDirect(0);
        tmax = (b.x2() - a.x0()) / a.GetDirect(0);
      }
      else
      {
        tmin = (b.x2() - a.x0()) / a.GetDirect(0);
        tmax = (b.x1() - a.x0()) / a.GetDirect(0);
      }
      if (a.GetDirect(1) >= 0.0)
      {
        tymin = (b.y1() - a.y0()) / a.GetDirect(1);
        tymax = (b.y2() - a.y0()) / a.GetDirect(1);
      }
      else
      {
        tymin = (b.y2() - a.y0()) / a.GetDirect(1);
        tymax = (b.y1() - a.y0()) / a.GetDirect(1);
      }

    if ((tmin > tymax) || (tymin > tmax)) { return false; }
    if (tymin > tmin) { tmin = tymin; }
    if (tymax < tmax) { tmax = tymax; }

    return true;

   }

  void Out(Box2D & b, Ray2D & a)
  {
    if (Intersection(b,a) == true) cout << "Yes" <<endl;
    else cout << "No" << endl;
  }

  bool operator == (Ray2D const & obj) const
    {
      return EqualWithEps(m_origin.x(), obj.m_origin.x()) && EqualWithEps(m_origin.y(), obj.m_origin.y())
          && EqualWithEps(m_direct[0], obj.m_direct[0]) && EqualWithEps(m_direct[1], obj.m_direct[1]);
    }

private:
  Point2D m_origin = Point2D();
  float m_direct[2] = {0.0f, 0.0f};

  void const SetDirAngleParam(float x)
  {
    m_direct[0] = Round(cos(x));
    m_direct[1] = Round(sin(x));
  }

  void Normalize(float x0, float y0, float x1, float y1)
  {
    float sq=sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
    try
    {
      if (sq < 1.0) { throw invalid_argument("Invalid way to create direction"); }
      else
        {
          m_direct[0] = (x1-x0)/sq;
          m_direct[1] = (y1-y0)/sq;
        }
    }
    catch(invalid_argument & p)
    {
      m_direct[0] = 0.0;
      m_direct[1] = 0.0;
    }
  }

  void NormalizeArr(float * arr)
  {
    float sq=sqrt((arr[2]-arr[0])*(arr[2]-arr[0]) + (arr[3]-arr[1])*(arr[3]-arr[1]));
    try
    {
      if (sq < 1.0) { throw invalid_argument("Invalid way to create direction"); }
      else
        {
          m_direct[0] = (arr[2]-arr[0])/sq;
          m_direct[1] = (arr[3]-arr[1])/sq;
        }
    }
    catch(invalid_argument & p)
    {
      m_direct[0] = 0.0;
      m_direct[1] = 0.0;
    }
  }

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < Eps;
  }

  float Round(float f)
  {
    return roundf(f * 1000.0) / 1000.0;
  }

};
