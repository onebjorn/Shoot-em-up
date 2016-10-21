#include "alien.h"
#include "obstacle.h"
#include "gun.h"
#pragma once


class Space : public GameEntity
{
public:

  Space() = default;

  Space(float const x1, float const y1, float const x2, float const y2)
  {
    m_box = Box2D(x1, y1, x2, y2);
  }

  Space(Point2D const & leftBottom, Point2D const & rightTop)
  {
    m_box = Box2D(leftBottom, rightTop);
  }

  Space( Box2D const & spaceBox)
  {
    m_box = Box2D(spaceBox);
  }

};
