#ifndef TENT_HPP_
#define TENT_HPP_

#include <ITENT.hpp>
#include <Folding.hpp>

#include <array>
#include <memory>

#include <iostream>

template <typename ValueType, unsigned int DIM>
class BigTENT;

template <typename ValueType, unsigned int DIM>
class TENT : public ITENT<ValueType, DIM> {
private:
  ValueType value;

  static unsigned int getIndex(int indexes[DIM], unsigned int maxPrecision) {
    unsigned int index = 0;
    for (int i = 0 ; i < DIM ; i++) {
      index += (((indexes[i] >> maxPrecision) & 1) << i);
    }
    return index;
  };
public:
  std::array<std::unique_ptr<ITENT<ValueType, DIM> >, 1 << DIM> children;

  TENT() = default;
  TENT(TENT&&) = default;

  TENT(TENT& t) {
    value = t.get();
  }

  TENT(BigTENT<ValueType, DIM>&& t) {
    for (int i = 0 ; i < 2 << DIM ; i++) {
      if (t.children[i] != nullptr) {
	if (children[i >> DIM] == nullptr) {
	  children[i >> DIM] = std::make_unique<TENT<ValueType, DIM> >();
	  children[i >> DIM]->set(t.get());
	}
	children[i >> DIM]->children[i & ((1 << DIM) - 1)] = std::move(t.children[i]);
      }
    }
  }
  
  ValueType get() const {
    return value;
  }

  ValueType get(int indexes[DIM], unsigned int maxPrecision) const {
    if (maxPrecision == 0)
      return value;
    const unsigned int index = getIndex(indexes, maxPrecision);
    if (children[index] == nullptr)
      return value;
    return children[index]->get(indexes, maxPrecision - 1);
  };
  
  void set(ValueType newValue) {
    value = newValue;
  }

  void set(int indexes[DIM], unsigned int precision, ValueType newValue) {
    if (precision == 0) {
      value = newValue;
      return;
    }
    const unsigned int index =  getIndex(indexes, precision);
    if (children[index] == nullptr) {
      children[index] = std::make_unique<TENT<ValueType, DIM> >();
    }
    children[index]->set(indexes, precision - 1, newValue);
    fold();
  };

  void del(int indexes[DIM], unsigned int precision) {
    const unsigned int index = getIndex(indexes, precision);
    if (precision == 1)
      return children[index].reset();
    children[index]->del(indexes, precision - 1);
    fold();
  };

  void fold() {
    for (auto &f : Folding<TENT<ValueType, DIM>>::instance().continuous)
      f(*this);
  };
};

#endif
