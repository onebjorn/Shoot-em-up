/* Игровая сущность*/
#pragma once
#include "../geometry/box2d.h"
#include "../geometry/ray2d.h"
#include "../include/config_stat.h"
#include <memory>


class Factory
{
public:
  template<typename T, typename... Args> std::unique_ptr<T> Create(Args && ... args)
  {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
};

class GameEntity
{
public:

  Box2D const & GetBox() const { return m_box; }

  bool ObjectsIntersect(GameEntity const & a, GameEntity const & b)
  {
    if (a.GetBox().x2() < b.GetBox().x1()) return false;
    if (a.GetBox().x1() > b.GetBox().x2()) return false;
    if (a.GetBox().y2() < b.GetBox().y1()) return false;
    if (a.GetBox().y1() > b.GetBox().y2()) return false;
    return true;
  }

  virtual ~GameEntity() = default;

protected:

  Box2D m_box;
};

inline ostream & operator << (ostream & os, GameEntity const & obj)
{
  os << "GameEntity coordinates center =  {" << obj.GetBox().GetCenter().x() << ", " <<  obj.GetBox().GetCenter().y() << "}";
  return os;
}

