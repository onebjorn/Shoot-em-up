#include "box2d.h"
#include "alien.h"
#include "obstacle.h"
#include "ray2d.h"
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
    : Box2D(spaceBox.x1(), spaceBox.y1(), spaceBox.x2(),spaceBox.y2())
  {}







  /* Сделать пересечение пули и пришельца */
  /* Сделать вылет пули из оружия */
  /* Сделать движение оружия */
  /* Сделать движение пришельцев */
  /* Сделать пересечние пули с препятствием */

private:

};
