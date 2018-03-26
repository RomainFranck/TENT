#ifndef FOLDING_HPP_
#define FOLDING_HPP_

#include <vector>
#include <memory>
#include <functional>
#include <ITENT.hpp>

template<typename T>
class Folding {
public:
  typedef std::function<void(ITENT<typename T::valuetype, T::dim>&)> Fold;
  
  static Folding& instance() {
    static Folding f;
    return f;
  }

  std::vector<Fold> continuous;
  std::vector<Fold> final;
};

#endif
