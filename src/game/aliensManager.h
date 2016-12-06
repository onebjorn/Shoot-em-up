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
    CreateAliens(kAliensNumberRow, kAliensNumberColumn, kSpaceSizeX, kSpaceSizeY);
  }

  AliensManager(int const row, int const column)
  {
    CreateAliens(row, column, kSpaceSizeX, kSpaceSizeY);
  }

  Aliens const & GetAliens() const { return m_aliens; }
  int const & GetRow() const { return m_rows; }
  int const & GetColumn() const { return m_columns; }

  bool CheckHit(Bullets & obj)
  {
    for(auto itAliens = m_aliens.begin(); itAliens != m_aliens.end(); ++itAliens)
    {
      for(auto itBullets = obj.begin(); itBullets != obj.end(); ++itBullets)
      if (itAliens->ObjectsIntersect(*itAliens, *itBullets))
      {
        itBullets->Update(*itAliens);
        if(itAliens->GetHealth() <= kBulletDamage) m_aliens.erase(itAliens);
        obj.erase(itBullets);
        return true;
      }
    }
    return false;
  }

  void AliensMove(float const deltaX, float const deltaY)
  {
    if(m_aliens.back().GetBox().x2() < kSpaceSizeX - 50.0f)
    {
      for (auto it = m_aliens.begin(); it != m_aliens.end(); ++it)
      {
        it->SetBox({ deltaX, 0.0f, deltaX, 0.0f });
      }
    }
    else
    {
      for (auto it = m_aliens.begin(); it != m_aliens.end(); ++it)
      {
        it->SetBox({ - kSpaceSizeX + 200.0f, - deltaY, - kSpaceSizeX + 200.0f, - deltaY});
      }
    }
  }

  void clear() { m_aliens.erase(m_aliens.begin(), m_aliens.end()); }

  ~AliensManager() = default;

private:

  int m_rows = 0.0f;
  int m_columns = 0.0f;

  float m_initX = 0.0f;
  float m_initY = 0.0f;

  void CreateAliens(int const row, int const column, float const X_size, float const Y_size)
  {
    m_rows = row;
    m_columns = column;

    float const Delta = X_size / (column + 5.0f);
    m_initX = X_size / 2.0f - column / 2.0 * Delta;
    m_initY = Y_size - 2.0f * Delta;
    /*TODO построение в центре пересчитать координату init*/
    for (auto i = 0; i < row; i++)
    {
      for (auto k = 0; k < column; k++)
      {
        m_aliens.push_back(Alien(m_initX + k * Delta, m_initY + i * Delta));
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

