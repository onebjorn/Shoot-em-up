#include "box2d.h"
#include "alien.h"
#include "obstacle.h"
#include "ray2d.h"
#include "gun.h"
#pragma once


class Space : public Box2D
{
public:

  Space() = default;

  Space(float const x1, float const y1, float const x2, float const y2)
    : Box2D (x1, y1, x2, y2)
  {}

  Space(Point2D const & leftBottom, Point2D const & rightTop)
      :Box2D(leftBottom, rightTop)
  {}

  Space( Box2D const & spaceBox)
    : Box2D(spaceBox)
  {}

private:
/* к 4ой домашке сделать контейнер для пуль, в который доавляется пуля после выстрела, потом перемещается. Либо отдельным классом*/
  Gun gun;
};
