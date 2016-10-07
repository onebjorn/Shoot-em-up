#pragma once
#include <cmath>
#include <iostream>
#include <functional>
#include <initializer_list>
#include <box2d.h>
#include <point2d.h>

using namespace std;

float const pi = 3.14159265;

class Ray
{
public:

  Ray()=default;

  Ray(Ray const & obj)
  {
    m_origin = Point2D(obj.m_origin);
    m_direct[0]=obj.m_direct[0];
    m_direct[1]=obj.m_direct[1];
  }

  Ray(float x_0, float y_0, float phi)
  {
    if (phi<0.0) phi= 2*3.14 - phi;
    m_origin = Point2D(x_0,y_0);
    SetDir_1param(phi);
  }

  Ray(float x_0, float y_0, float x_1, float y_1)
  {
    m_origin = Point2D(x_0,y_0);
    float sq=sqrt((x_1-x_0)*(x_1-x_0) + (y_1-y_0)*(y_1-y_0));
    try
    {
      if(sq<1){throw 123;}
      else
      {
        m_direct[0]=(x_1-x_0)/sq;
        m_direct[1]=(y_1-y_0)/sq;
      }
    }
    catch(int p)
    {
      m_direct[0]=0.0;
      m_direct[1]=0.0;
      cout << "Invalid way to create direction" << endl;
    }
    }

 Ray(std::initializer_list<float> const & lst)
  {
  float * vals[] = { &m_origin.x(), &m_origin.y(), &m_direct[0], &m_direct[1]};
  int const count = sizeof(vals) / sizeof(vals[0]);

  auto it = lst.begin();
  for (int i = 0; i < count && it != lst.end(); i++, ++it) *vals[i] = *it;
  int const n=lst.size();
  switch(n)
    {
    case 3:
      {
        SetDir_1param(*vals[2]);
        break;
      }
    case 4:
      {
        float sq=sqrt((*vals[2]-*vals[0])*(*vals[2]-*vals[0]) + (*vals[3]-*vals[1])*(*vals[3]-*vals[1]));
        try
        {
          if(sq<1){throw 123;}
          else
          {
            *vals[2]=(*vals[2]-*vals[0])/sq;
            *vals[3]=(*vals[3]-*vals[1])/sq;
          }
        }
        catch(int p)
        {
          *vals[2]=0.0;
          *vals[3]=0.0;
        }
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

  float & x0() {return m_origin.x();}
  float & y0() {return m_origin.y();}


  float const & x() const {return m_origin.x();}
  float const & y() const {return m_origin.y();}

  int Where(Box2D & obj1)
  {
    int wh;
    if (m_origin.x()<obj1.x1()){
        if (m_origin.y()<obj1.y1()) {wh=2;}
        else if (m_origin.y()>obj1.y2()) {wh=8;}
        else wh=1;
      }
    else if (m_origin.x()>obj1.x2()){
        if (m_origin.y()<obj1.y1()) {wh=4;}
        else if (m_origin.y()>obj1.y2()) {wh=6;}
        else wh=5;
      }
    else {
        if (m_origin.y()<obj1.y1()) {wh=3;}
        else if (m_origin.y()>obj1.y2()) {wh=7;}
        else wh=0;
      }
    return wh;
  }

  // Checking correct direction of ray
  bool Correct_Dir(int b)
  {
    switch (b)
      {
      case 0:
        {
         return false;
         break;
        }
      case 1:
        {
          if (fabs(acos(-GetDirect(0)))<pi/2.0) {return false;}
          else {return true;}
          break;
        }
      case 2:
        {
          if ((acos(GetDirect(0)) > pi/2.0)||(acos(GetDirect(1)) > pi/2.0)) {return false;}
          else {return true;}
          break;
        }
      case 3:
        {
          if (fabs(acos(-GetDirect(1)))<pi/2.0) {return false;}
          else {return true;}
          break;
        }
      case 4:
        {
          if ((acos(-GetDirect(0)) > pi/2.0)||(acos(GetDirect(1)) > pi/2.0)) {return false;}
          else {return true;}
          break;
        }
      case 5:
        {
          if (fabs(acos(GetDirect(0)))<pi/2.0) {return false;}
          else {return true;}
          break;
        }
      case 6:
        {
          if ((acos(-GetDirect(0)) > pi/2.0)||(acos(-GetDirect(1)) > pi/2.0)) {return false;}
          else {return true;}
          break;
        }
      case 7:
        {
          if (fabs(acos(GetDirect(1)))<pi/2.0) {return false;}
          else {return true;}
          break;
        }
      case 8:
        {
          if ((acos(GetDirect(0)) > pi/2.0)||(acos(-GetDirect(1)) > pi/2.0)) {return false;}
          else {return true;}
          break;
        }
      }
  }

  float X_test(float y)
  {
    if (GetDirect(1)!=0.0)
      {
        float b = m_origin.x() + (y - m_origin.y())*GetDirect(0)/GetDirect(1);
        return b;
      }
    else return m_origin.y();
  }

  float Y_test(float x)
  {
    if (GetDirect(0)!=0.0)
      {
        float b = m_origin.y() + (x - m_origin.x())*GetDirect(1)/GetDirect(0);
        return b;
      }
    else return m_origin.x();
  }

  bool Condition(Box2D & obj1,int b)
  {
    switch (b)
      {
      case 1:
        {
          return (Y_test(obj1.x1()) > obj1.y1())&&(Y_test(obj1.x1()) < obj1.y2());
          break;
        }
      case 2:
        {
          return ( ((Y_test(obj1.x1()) > obj1.y1())&&(Y_test(obj1.x1()) < obj1.y2()))
                  || ((X_test(obj1.y1()) > obj1.x1())&&(X_test(obj1.y1()) < obj1.x2())) );
          break;
        }
      case 3:
        {
          return ((X_test(obj1.y1()) > obj1.x1())&&(X_test(obj1.y1()) < obj1.x2()));
          break;
        }
      case 4:
        {
          return ( ((X_test(obj1.y1()) > obj1.x1())&&(X_test(obj1.y1()) < obj1.x2()))
                  || ( (Y_test(obj1.x2()) > obj1.y1())&&(Y_test(obj1.x2()) < obj1.y2()) ) );
          break;
        }
      case 5:
        {
          return (Y_test(obj1.x2()) > obj1.y1())&&(Y_test(obj1.x2()) < obj1.y2());
          break;
        }
      case 6:
        {
          return ( ( (Y_test(obj1.x2()) > obj1.y1())&&(Y_test(obj1.x2()) < obj1.y2()) )
                  || ( (X_test(obj1.y2()) > obj1.x1())&&(X_test(obj1.y2()) < obj1.x2()) ) );
          break;
        }
      case 7:
        {
          return (X_test(obj1.y2()) > obj1.x1())&&(X_test(obj1.y2()) < obj1.x2());
          break;
        }
      case 8:
        {
          return ( ( (X_test(obj1.y2()) > obj1.x1())&&(X_test(obj1.y2()) < obj1.x2()) )
                  || ( (Y_test(obj1.x1()) > obj1.y1())&&(Y_test(obj1.x1()) < obj1.y2()) ) );
          break;
        }
      }
  }

  void GetCrossRect(Box2D & obj1)
  {
    int c = Where(obj1);

    try
    {
      if (Correct_Dir(c)==false) {throw 123;}
      else
        {
          if (Condition(obj1, c)==true) {cout << "Crossing" << endl;}
          else {cout << "Not Crossing" << endl;}
        }
    }
    catch(int p)
    {
      cout << "Not Crossing" << endl;
    }
  }

  bool operator == (Ray const & obj) const
    {
      return EqualWithEps(m_origin.x(), obj.m_origin.x()) && EqualWithEps(m_origin.y(), obj.m_origin.y())
          && EqualWithEps(m_direct[0], obj.m_direct[0]) && EqualWithEps(m_direct[1], obj.m_direct[1]);
    }

private:
  Point2D m_origin = Point2D();
  float m_direct[2]={0.0f, 0.0f};

  void const SetDir_1param(float x)
  {

    m_direct[0]=cos(x);
    if (x==pi/2.0) {m_direct[0]=0.0;} // Oh, I don't know how it happened...
    m_direct[1]=sin(x);
  }

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

};
