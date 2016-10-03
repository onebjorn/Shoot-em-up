#include <iostream>
#pragma once
#include <initializer_list>
#include <functional>
#include <cmath>

using namespace std;
/* Класс двумерного прямоугольника Box2d*/
class Box2D
{
private:
    /* Инициализация координат прямоугольника*/
    double box2d_x1 = 0.0,
                 box2d_y1 = 0.0,
                 box2d_x2 = 0.0,
                 box2d_y2 = 0.0;
    /* Инициализация площади */
    double box2d_square = 0.0;

public:

    Box2D() = default;

    /* Иницилизация координат центра*/
    double box2d_x_center = 0.0,
                 box2d_y_center = 0.0;
    /* Длина и высота */
    double box2d_lenght = 0.0,
                 box2d_height = 0.0;

    /* Обычный конструктор с параметрами*/
    Box2D(double x1, double y1, double x2,double y2)
        :box2d_x1(x1),
         box2d_y1(y1),
         box2d_x2(x2),
         box2d_y2(y2)
    {
        // Код конструктора
    }

    /* Конструктор копирования */
    Box2D( const Box2D & obj)
        :box2d_x1(obj.box2d_x1),
         box2d_y1(obj.box2d_y1),
         box2d_x2(obj.box2d_x2),
         box2d_y2(obj.box2d_y2)
    {
        //Код конструктора копирования
    }

     /* Оператор присваивания */
      Box2D & operator = (Box2D const & obj)
      {
        if (this == &obj) return *this;
        box2d_x1 = obj.box2d_x1;
        box2d_y1 = obj.box2d_y1;
        box2d_x2 = obj.box2d_x2;
        box2d_y2 = obj.box2d_y2;
        return *this;
      }

 void getBox2d()
 {
  cout << "Box= " << "( "<< box2d_x1 <<", "<< box2d_y1 << ") & ( "
          << box2d_x2<< ", "<< box2d_y2 << ")" << endl;

 }

/* TODO операции сложений и умножений*/

 /* Вычисление площади*/
 void square()
 {
     box2d_square = fabs(box2d_x2 - box2d_x1) * fabs(box2d_y2 - box2d_y1);
     cout << "Square(Box) = "<< box2d_square << endl;
 }

 void boxGeometry()
 {
  box2d_x_center = (box2d_x2 + box2d_x1) / 2.0;
  box2d_y_center = (box2d_y2 + box2d_y1) / 2.0;
  box2d_lenght = fabs(box2d_x2 - box2d_x1);
  box2d_height = fabs(box2d_y2 - box2d_y1);
 }

 friend void boxCrossing(Box2D&, Box2D&);

    ~Box2D()
    {
  //Код деструктора
    }

};


class Ray2D
{

private:
double ray_x = 0.0,
             ray_y = 0.0;
/* Угол к горизонтали */
double ray_angle = 0.0;

public:

    Ray2D() = default;

    /* Обычный конструктор с параметрами*/
    Ray2D (double x1, double y1, double a)
        :ray_x(x1),
         ray_y(y1),
         ray_angle(a)
    {
        // Код конструктора
    }

    /* Конструктор копирования */
    Ray2D( const Ray2D & obj)
        :ray_x(obj.ray_x),
         ray_y(obj.ray_y),
         ray_angle(obj.ray_angle)
    {
        //Код конструктора копирования
    }


    /* Оператор присваивания */
     Ray2D & operator = (Ray2D const & obj)
     {
       if (this == &obj) return *this;
       ray_x = obj.ray_x;
       ray_y = obj.ray_y;
       ray_angle = obj.ray_angle;
       return *this;
     }


     void getRay2d()
     {
      cout << "Ray= " << "( "<< ray_x <<", "<< ray_y << ") & ( "
              << ray_angle << ")" << endl;
     }


     void rayGeometry()
     {
double ray_k = 0.0;
ray_k = tan(ray_angle);
cout<< "Ray = " << ray_k  << endl;
     }

     friend void rayCrossing(Ray2D&, Box2D&);

        ~Ray2D()
        {
      //Код деструктора
        }


};
