#ifndef ITENT_HPP_
#define ITENT_HPP_

#include <type_traits>
#include <Folding.hpp>

template<typename ValueType, unsigned int DIM>
class ITENT {
public:
  void continuousFold() {
    for (auto f : Folding<decltype(*this)>::instance().continuous)
      f(this);
  }

  void finalFold() {
    for(auto f : Folding<decltype(*this)>::instance().final)
      f(this);
  }

  ValueType get(int indexes[DIM], unsigned int maxPrecision) const {
    return ValueType();
  };
  
  void set(int indexes[DIM], unsigned int precision, ValueType value) {
    return;
  };

  void del(int indexes[DIM], unsigned int maxPrecision) {
    return;
  };
};

#endif
