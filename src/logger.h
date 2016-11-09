#pragma once
#include <iostream>
#include <ostream>
#include <fstream>

using namespace std;

template<typename T> class Singleton
{
public:
  static T & Instance()
  {
    static T inst;
    return inst;
  }

protected:
  Singleton() = default;
  virtual ~Singleton() = default;
  Singleton(Singleton const &) = delete;
  Singleton & operator = (Singleton const &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton & operator = (Singleton &&) = delete;
};

class Logger : public Singleton <Logger>
{
public:

  template <typename T>
  ostream & Log(T obj, ostream & os)
  {
    os << obj;
    return os;
  }

  template<typename T, template<typename, typename...> class C, typename... Args>
  ostream & Log(ostream & os, C<T, Args...> const & objs)
  {
    for (auto const & obj : objs)
    Log(obj, os);
    return os;
  }

  /*TODO добавить переключатель*/
  void LoggerSwitchOn() { m_logSwitch = true; }
  void LoggerSwitchOff() { m_logSwitch = false; }

  void LoggerSwitchFileOn() { m_logSwitchFile = true; }
  void LoggerSwitchFileOff() { m_logSwitchFile = false; }

private:
  bool m_logSwitch = true; /* Переключатель логгера(1 запись, 0 - не запись)*/
  bool m_logSwitchFile = true; /* Перключатель запись в файл */

  friend class Singleton<Logger>;
  Logger() = default;

};
