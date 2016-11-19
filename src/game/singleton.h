#pragma once

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
