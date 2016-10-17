/* Игровая сущность*/
#include "box2d.h"
#include "ray2d.h"
#include "../include/config_stat.h"
#pragma once

class GameEntity
{
public:

  virtual ~GameEntity() = default;

  Point2D const & GetBox() const { return m_box; }
  Point2D const & GetDir() const { return m_ray; }

protected:

  Box2D m_box = { 0.0f, 0.0f, 0.0f, 0.0f };
  Ray2D m_ray = { 0.0f, 0.0f, 0.0f, 0.0f };
};
