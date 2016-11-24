#pragma once
#include <iostream>
#include <ostream>
#include <fstream>
#include <time.h>
#include "singleton.h"

using namespace std;

class Logger : public Singleton <Logger>
{
public:
  template <typename T>
  ostream & Log(T obj, ostream & os)
  {
    os << obj;
    return os;
  }

  template <typename T>
  fstream & Log(T obj)
  {
    setTime();
    file.open("Logfile.txt", ios_base::out | ios_base::app);
    if (file.is_open())
      {
        file << asctime(m_timeinfo) << "\t" << obj << endl;
      }
    else cout << "Unable to open" << endl;
    file.close();
  }

  template<typename T, template<typename, typename...> class C, typename... Args>
  ostream & Log(ostream & os, C<T, Args...> const & objs)
  {
    for (auto const & obj : objs)
    Log(obj, os);
    return os;
  }

  template<typename T, template<typename, typename...> class C, typename... Args>
  fstream & Log(C<T, Args...> const & objs)
  {
    setTime();
    file.open("Logfile.txt", ios_base::out | ios_base::app);
    if (file.is_open())
      {
        for (auto const & obj: objs)
          file << asctime(m_timeinfo) << "\t" << obj << endl;
      }
    else cout << "Unable to open" << endl;
    file.close();
  }

  /*TODO добавить переключатель*/
  void LoggerSwitchOn() { m_logSwitch = true; }
  void LoggerSwitchOff() { m_logSwitch = false; }

  void LoggerSwitchFileOn() { m_logSwitchFile = true; }
  void LoggerSwitchFileOff() { m_logSwitchFile = false; }
  void setTime()
  {
    time(& m_rawtime);
    m_timeinfo = localtime( & m_rawtime);
  }

private:
  bool m_logSwitch = true; /* Переключатель логгера(1 запись, 0 - не запись)*/
  bool m_logSwitchFile = true; /* Перключатель запись в файл */
  Logger() = default;

  friend class Singleton<Logger>;

  fstream file;
  time_t m_rawtime;
  struct tm * m_timeinfo;

};
