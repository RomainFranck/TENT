#ifndef FOLDING_HPP_
#define FOLDING_HPP_

#include <typeinfo>
#include <vector>
#include <functional>
#include <ITENT.hpp>

template<typename T>
class Fold {
  std::function<bool(T)> predicate;
  std::function<T(T)> action;
public:
  Fold(std::function<bool(T)> p, std::function<T(T)> a) : predicate(p), action(a) {};

  void operator()(T &t) {
    if (predicate(t))
      t = action(t);
  }
};

template<typename T>
class Folding {
private:
  Folding() {};
public:
  Folding& instance() {
    static Folding f;
    return f;
  }

  std::vector<Fold<T>> continuous;
  std::vector<Fold<T>> final;
};

#endif
