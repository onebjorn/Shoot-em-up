#include <iostream>
#include <vector>

class String23
{
public:

  String23() = default;

  String23(char cc)
  {
    for (int i = 0; i < 10; i++)
    {
      c[i] = cc;
    }
  }

private:
  char c[10];
};
