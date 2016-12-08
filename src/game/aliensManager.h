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
    CreateAliens(kAliensNumberRow, kAliensNumberColumn, kSpaceSizeX, kSpaceSizeY, kAlienHealth, kAlienSpeed, 0);
  }

  AliensManager(int const row, int const column)
  {
    CreateAliens(row, column, kSpaceSizeX, kSpaceSizeY, kAlienHealth, kAlienSpeed, 0);
  }

  AliensManager(int const row, int const column, float const SpaceSizeX, float const SpaceSizeY, float const Health, float const Speed, bool type)
  {
    CreateAliens(row, column, SpaceSizeX, SpaceSizeY, Health, Speed, 0);
  }


  Bullet AliensShoot()
  {
    srand(0);
    auto it = rand() % m_aliens.size();
    return m_aliens.at(it).Shot();
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
        obj.erase(itBullets);
        itAliens->RemoveHealth(kBulletDamage);
        if(itAliens->GetHealth() < 0.0f) { m_aliens.erase(itAliens); }
        return true;
      }
    }
    return false;
  }

  void AliensMove(float const deltaX, float const deltaY)
  {
    int AlienCase = 0;
    for (auto it = m_aliens.begin(); it != m_aliens.end(); ++it)
    {
      if(it->GetBox().x2() > kSpaceSizeX - deltaX) { AlienCase = 1; }
      if(it->GetBox().x1() < deltaX) { AlienCase = 2; }
    }

    if(AlienCase == 1)
    {
      m_dir = - 1.0f;
      for (auto it = m_aliens.begin(); it != m_aliens.end(); ++it)
      {
        it->SetBox({ -deltaX, - deltaY / 2.0f, -deltaX, - deltaY / 2.0f});
      }
    }
    else if (AlienCase == 2)
    {
      m_dir = 1.0f;
      for (auto it = m_aliens.begin(); it != m_aliens.end(); ++it)
      {
        it->SetBox({ deltaX, - deltaY / 2.0f, deltaX, - deltaY / 2.0f});
      }
    }
    else
    {
      for (auto it = m_aliens.begin(); it != m_aliens.end(); ++it)
      {
        it->SetBox({ deltaX * m_dir, 0.0f, deltaX * m_dir, 0.0f });
      }
    }
  }

  void clear() { m_aliens.erase(m_aliens.begin(), m_aliens.end()); }

  ~AliensManager() = default;

private:

  float m_dir = 1.0f;

  int m_rows = 0.0f;
  int m_columns = 0.0f;

  float m_initX = 0.0f;
  float m_initY = 0.0f;

  void CreateAliens(int const row, int const column, float const X_size, float const Y_size,float const health, float const speed, bool type)
  {
    m_rows = row;
    m_columns = column;

    float const Delta = X_size / (column + 5.0f);
    m_initX = X_size / 2.0f - column / 2.0 * Delta;
    m_initY = Y_size * 0.9f;
    /*TODO построение в центре пересчитать координату init*/
    for (auto i = 0; i < row; i++)
    {
      for (auto k = 0; k < column; k++)
      {
        m_aliens.push_back(Alien(m_initX + k * kAlienSizeX, m_initY - i * kAlienSizeY, health, speed, type));
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

