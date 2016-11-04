#pragma once
#include <iostream>
#include <ostream>

using namespace std;
class Logger
{
public:
  Logger() = default;

  template <typename T>
  Logger & Log (T const & obj)
  {
    m_s << obj;
    return *this;
  }

  template<typename T, template<typename, typename...> class C, typename... Args>
  Logger & operator << (C<T, Args...> const & objs)
  {
    m_s << "Container" << endl;
    for (auto const & obj : objs)
      m_s << obj << "\t";
    return *this;
  }
private:
  ostream & m_s = cout;
};
