#include "logger.h"
#include "gun.h"
#include "bulletsManager.h"
#include "aliensManager.h"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

int main()
{
  Gun g1(0.0f, 0.0f, 10.0f, 10.0f);

  BulletsManager Bm;
  Bm.AddBullet(g1.Shot());

  AliensManager am(2, 2);
  /* TODO ALIen SHOOT*/
//  Bm.AddBullet(am.GetAliens().front().Alien::AlienShot());

  Logger::Log(g1, cout);
  Logger::Log(am, cout);
  Logger::Log(Bm, cout);

//  Logger::Log2(Bm, cout);
  /*
  Bullet b1(0.0f, 1.0f, 50.0f);
  Bullet b2 = {10.0f, 15.0f, 17.0f, 20.0f, 50.0f};
  log.Log(b1);
  log.Log(b2);
  vector<Bullet> Bull = {b1, b2};
  log << Bull;
  */

  return 0;
}
