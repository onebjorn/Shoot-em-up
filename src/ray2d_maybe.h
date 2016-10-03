#ifndef RAY2D_MAYBE
#define RAY2D_MAYBE

#endif // RAY2D_MAYBE

#pragma once

#include <cmath>
#include <iostream>
#include <functional>

using namespace std;
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

protected:
        float m_x, m_y;
};

class Ray: public Point
{
public:
        Ray()=default;

        Ray(Ray const & obj)
        {
                origin[0]=obj.origin[0];
                origin[0]=obj.origin[1];
                direct[0]=obj.direct[0];
                direct[1]=obj.direct[1];
        }

        Ray(float x_0, float y_0, float phi)
        {
                if (phi<0.0) phi= 2*3.14 - phi;
                SetOrigin(x_0,y_0);
                SetDir_1param(phi);
        }

        Ray(float x_0, float y_0, float x_1, float y_1)
        {
                SetOrigin(x_0,y_0);
                float sq=sqrt(x_1*x_1 + y_1*y_1);
                try
                {
                        if(sq<1){throw 123;}
                        else
                        {
                                direct[0]=x_1/sq;
                                direct[1]=y_1/sq;
                        }
                }
                catch(int p)
                {
                        cout << "Invalid way to create direction" << endl;
                }
        }

        float GetDirect(int i)
        {
                return direct[i];
        }

        float GetOrigin(int i)
        {
                return origin[i];
        }
private:
        float origin[2];
        float direct[2];

        void SetOrigin(float x,float y)
        {
                origin[0]=x;
                origin[1]=y;
        }

        void SetDir_1param(float x)
        {
                direct[0]=cos(x);
                direct[1]=sin(x);
        }

        //void GetCrossRect(float a, float b){}
};
