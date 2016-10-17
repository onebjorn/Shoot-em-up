/* Игровая сущность*/
#include "box2d.h"
#include "ray2d.h"
#include "../include/config_stat.h"
#pragma once

class GameEntity
{
public:

  virtual ~GameEntity() = default;

  virtual Point2D GetCenter() const = 0;

  virtual float const & x1() = 0; // Объявление чистого виртуального метода.
  virtual float const & x2() = 0; // Объявление чистого виртуального метода.
  virtual float const & y1() = 0; // Объявление чистого виртуального метода.
  virtual float const & y2() = 0; // Объявление чистого виртуального метода.

private:

  Box2D m_object = { 0.0f, 0.0f, 0.0f, 0.0f };

};
