/* Игровая сущность*/
#include "box2d.h"
#include "ray2d.h"
#include "../include/config_stat.h"
#pragma once

class GameEntity
{
public:

  virtual ~GameEntity() = default;

  virtual Box2D const & GetBox() const = 0;

protected:
  Box2D m_box = { 0.0f, 0.0f, 0.0f, 0.0f };
};
