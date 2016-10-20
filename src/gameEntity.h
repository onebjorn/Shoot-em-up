/* Игровая сущность*/
#include "box2d.h"
#include "ray2d.h"
#include "../include/config_stat.h"
#pragma once

class GameEntity
{
public:

  Box2D const & GetBox() const { return m_box; }

  bool ObjectsIntersect( GameEntity const & a, GameEntity const & b)
  {
    if (a.GetBox().x2() < b.GetBox().x1()) return false;
    if (a.GetBox().x1() > b.GetBox().x2()) return false;
    if (a.GetBox().y2() < b.GetBox().y1()) return false;
    if (a.GetBox().y1() > b.GetBox().y2()) return false;
    return true;
  }

protected:
  Box2D m_box;
};
