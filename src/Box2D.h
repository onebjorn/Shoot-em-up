#include <iostream>
#pragma once
#include <ray2d_maybe.h>
#include <functional>
#include <cmath>

using namespace std;

/* Класс двумерного прямоугольника Box2d*/
class Box2D
{
private:
    /* Инициализация координат прямоугольника*/
    float box2d_x1 = 0.0,
             box2d_y1 = 0.0,
             box2d_x2 = 0.0,
             box2d_y2 = 0.0;
public:

    Box2D() = default;

    /* Иницилизация координат центра*/
    float box2d_x_center = 0.0,
             box2d_y_center = 0.0;
    /* Длина и высота */
    float box2d_lenght = 0.0,
             box2d_height = 0.0;
    /* Координаты углов*/
    float x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;

    /* Обычный конструктор с параметрами*/
    Box2D(float x1, float y1, float x2,float y2)
        :box2d_x1(x1),
         box2d_y1(y1),
         box2d_x2(x2),
         box2d_y2(y2)
    {  }

    /* Конструктор копирования */
    Box2D( const Box2D & obj)
        :box2d_x1(obj.box2d_x1),
         box2d_y1(obj.box2d_y1),
         box2d_x2(obj.box2d_x2),
         box2d_y2(obj.box2d_y2)
    {   }

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

 void getBox2D(Box2D const & obj)
 {
     x1 = obj.box2d_x1;
     y1 = obj.box2d_y1;
     x2 = obj.box2d_x2;
     y2 = obj.box2d_y2;
 }

 void boxGeometry()
 {
  box2d_x_center = (box2d_x2 + box2d_x1) / 2.0;
  box2d_y_center = (box2d_y2 + box2d_y1) / 2.0;
  box2d_lenght = fabs(box2d_x2 - box2d_x1);
  box2d_height = fabs(box2d_y2 - box2d_y1);
 }

void boxCrossing( Box2D&obj1, Box2D&obj2 )
{
  obj1.boxGeometry();
  obj2.boxGeometry();

    float rho_x = 0.0, rho_y = 0.0;
    float l = 0.0, h = 0.0;

/* Вычисление растояния между центрами по осям x и y */
rho_x =fabs(obj1.box2d_x_center - obj2.box2d_x_center);
rho_y = fabs(obj1.box2d_y_center - obj2.box2d_y_center);

/* Вычисление пересечения */
l = (obj1.box2d_lenght + obj2.box2d_lenght) / 2.0;
h = (obj1.box2d_height + obj2.box2d_height) / 2.0;

if  (rho_x > l && rho_y > h)
  {
    cout<< " NOT Crossing" <<  endl;
  }
else
  {
      cout<< " Crossing" << endl;
  }

}

~Box2D()
{}

};
