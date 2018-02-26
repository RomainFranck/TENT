#ifndef TENT_HPP_
#define TENT_HPP_

#include <ITENT.hpp>

#include <array>
#include <memory>

#include <iostream>

template <typename ValueType, unsigned int DIM>
class TENT : ITENT<ValueType, DIM> {
private:
  ValueType value;

  static unsigned int getIndex(int indexes[DIM], unsigned int maxPrecision) {
    unsigned int index = 0;
    for (int i = 0 ; i < DIM ; i++) {
      index += ((1 << (maxPrecision - 1)) & indexes[i] ? 1 << i : 0);
    }
    return index;
  }
public:
  std::array<std::unique_ptr<ITENT<ValueType, DIM>>, 1 << DIM> children;

  ValueType get(int indexes[DIM], unsigned int maxPrecision) const {
    if (maxPrecision == 0)
      return value;
    const unsigned int index = getIndex(indexes, maxPrecision);
    if (children[index] == nullptr)
      return value;
    return children[index]->get(indexes, maxPrecision - 1);
  }
  
  void set(int indexes[DIM], unsigned int precision, ValueType newValue) {
    if (precision == 0) {
      value = newValue;
      return;
    }
    const unsigned int index =  getIndex(indexes, precision);
    if (children[index] == nullptr)
      children[index] = std::unique_ptr<ITENT<ValueType, DIM>>(new TENT<ValueType, DIM>());
    children[index]->set(indexes, precision - 1, newValue);
  }

  void del(int indexes[DIM], unsigned int precision) {
    const unsigned int index = getIndex(indexes, precision);
    if (precision == 1)
      children[index].reset();
    else
      children[index]->del(indexes, precision - 1);
  }
};

#endif
