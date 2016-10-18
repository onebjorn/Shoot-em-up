#include "alien.h"
#include "obstacle.h"
#include "gun.h"
#pragma once


class Space : public GameEntity
{
public:
  Space() = default;

  Space(float const x1, float const y1, float const x2, float const y2)
    : m_space(x1, y1, x2, y2)
  {}

  Space(Point2D const & leftBottom, Point2D const & rightTop)
    : m_space(leftBottom, rightTop)
  {}

  Space( Box2D const & spaceBox)
    : m_space(spaceBox)
  {}

  Box2D const & GetBox() const override { return m_space; }

private:
  Box2D m_space = { 0.0f, 0.0f, 0.0f, 0.0f };
};
