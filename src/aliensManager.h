#pragma once
#include "alien.h"
#include <vector>
#include "logger.h"
#include "bulletsManager.h"
#include "../include/config_stat.h"


using Aliens = vector<Alien>;

class AliensManager
{
public:

  AliensManager()
  {
    CreateAliens(kAliensNumberRow, kAliensNumberColumn);
  }

  AliensManager(int const row, int const column)
  {
    CreateAliens(row, column);
  }

  Aliens const & GetAliens() const { return m_aliens; }
  int const & GetRow() const { return m_rows; }
  int const & GetColumn() const { return m_columns; }

  bool CheckHit(Bullets const & obj)
  {
    for(auto itAliens = m_aliens.begin(); itAliens != m_aliens.end(); ++itAliens)
    {
      for(auto itBullets = obj.begin(); itBullets != obj.end(); ++itBullets)
      if (itAliens->ObjectsIntersect(*itAliens, *itBullets)) return true;
    }
    return false;
  }

  ~AliensManager() = default;

private:

  int m_rows = 0.0f;
  int m_columns = 0.0f;

  void CreateAliens(int const row, int const column)
  {
    m_rows = row;
    m_columns = column;
    float const Delta = kSpaceSizeX / (column + 6.0f);
    for (auto i = 0; i < row; i++)
    {
      for (auto k = 0; k < column; k++)
      {
        m_aliens.push_back(Alien(Delta / 2.0f + k * Delta, Delta + i * Delta));
      }
    }
  }

  vector<Alien> m_aliens;
};

inline ostream & operator << (ostream & os, AliensManager const & obj)
{
  os << "Aliens:  " << "Rows = " << obj.GetRow() << ", Columns = " << obj.GetColumn() << endl;
  Logger::Instance().Log(os, obj.GetAliens());
  return os;
}

