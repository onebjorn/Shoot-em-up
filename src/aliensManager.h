#include "alien.h"
#include <vector>
#include "../include/config_stat.h"

using Aliens = std::vector<Alien>;

class AliensManager
{
public:

  AliensManager()
  {
    CreateAliens(AliensNumberRow, AliensNumberColumn);
  }

  AliensManager(float const row, float const column)
  {
    CreateAliens(row, column);
  }

  Aliens const & GetAliens() { return m_aliens; }

   ~AliensManager() = default;

private:

  void CreateAliens(float const row, float const column)
  {
    float const Delta = SpaceSizeX / (column + 6.0f);
    for (auto i = 0; i < row; i++)
    {
      for (auto k = 0; k < column; k++)
      {
        m_aliens.push_back(Alien(Delta / 2.0f + k * Delta, Delta + i * Delta));
      }
    }
  }

  std::vector<Alien> m_aliens;
};

