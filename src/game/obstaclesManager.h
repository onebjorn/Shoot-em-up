#pragma once
#include "obstacle.h"
#include <vector>
#include "logger.h"
#include "bulletsManager.h"
#include "../include/config_stat.h"


using Obstacles = vector<Obstacle>;

class ObstaclesManager
{
public:

  ObstaclesManager()
  {
    CreateObstacles(kObstaclesNumberRow, kObstaclesNumberColumn, kSpaceSizeX, kSpaceSizeY);
  }

  ObstaclesManager(int const row, int const column)
  {
    CreateObstacles(row, column, kSpaceSizeX, kSpaceSizeY);
  }

  Obstacles const & GetObstacles() const { return m_obstacles; }
  int const & GetRow() const { return m_rows; }
  int const & GetColumn() const { return m_columns; }

  bool CheckHit(Bullets & obj)
  {
    for(auto itObstacles = m_obstacles.begin(); itObstacles != m_obstacles.end(); ++itObstacles)
    {
      for(auto itBullets = obj.begin(); itBullets != obj.end(); ++itBullets)
      if (itObstacles->ObjectsIntersect(*itObstacles, *itBullets))
      {
        itBullets->Update(*itObstacles);
        obj.erase(itBullets);
        itObstacles->RemoveObstacleHealth(kBulletDamage);
        if(itObstacles->GetHealth() <= kBulletDamage) m_obstacles.erase(itObstacles);
        return true;
      }
    }
    return false;
  }

  void clear() { m_obstacles.erase(m_obstacles.begin(), m_obstacles.end()); }

  ~ObstaclesManager() = default;

private:

  int m_rows = 0.0f;
  int m_columns = 0.0f;

  float m_initX = 0.0f;
  float m_initY = 0.0f;

  void CreateObstacles(int const row, int const column, float const X_size, float const Y_size)
  {
    m_rows = row;
    m_columns = column;

    for (auto i = 0; i < row; i++)
    {
      for (auto k = 0; k < column; k++)
      {
        m_obstacles.push_back(Obstacle(1.0f * X_size / 8.0f - (column / 2.0f - 0.5f) * kObstacleSizeX + k * kObstacleSizeX, Y_size / 30.0f + 1.5f * kGunSizeY - i * kObstacleSizeY));
        m_obstacles.push_back(Obstacle(3.0f * X_size / 8.0f - (column / 2.0f - 0.5f) * kObstacleSizeX + k * kObstacleSizeX, Y_size / 30.0f + 1.5f * kGunSizeY - i * kObstacleSizeY));
        m_obstacles.push_back(Obstacle(5.0f * X_size / 8.0f - (column / 2.0f - 0.5f) * kObstacleSizeX + k * kObstacleSizeX, Y_size / 30.0f + 1.5f * kGunSizeY - i * kObstacleSizeY));
        m_obstacles.push_back(Obstacle(7.0f * X_size / 8.0f - (column / 2.0f - 0.5f) * kObstacleSizeX + k * kObstacleSizeX, Y_size / 30.0f + 1.5f * kGunSizeY - i * kObstacleSizeY));
      }
    }
  }

  vector<Obstacle> m_obstacles;
};

inline ostream & operator << (ostream & os, ObstaclesManager const & obj)
{
  os << "Obstacles:  " << "Rows = " << obj.GetRow() << ", Columns = " << obj.GetColumn() << endl;
  Logger::Instance().Log(os, obj.GetObstacles());
  return os;
}
