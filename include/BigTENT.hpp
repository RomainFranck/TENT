#ifndef BIGTENT_HPP_
#define BIGTENT_HPP_

#include <ITENT.hpp>
#include <Folding.hpp>

#include <array>
#include <memory>

#include <iostream>

template <typename ValueType, unsigned int DIM>
class TENT;

template <typename ValueType, unsigned int DIM>
class BigTENT : public ITENT<ValueType, DIM> {
private:
  ValueType value;

  static unsigned int getIndex(int indexes[DIM], unsigned int maxPrecision) {
    unsigned int index = 0;
    for (int i = 0 ; i < DIM ; i++) {
      index += ((indexes[i] >> 2 * maxPrecision) & 3) << (2 * i);
    }
    return index;
  };

public:
  std::array<std::unique_ptr<ITENT<ValueType, DIM> >, 2 << DIM> children;

  BigTENT() = default;
  BigTENT(BigTENT&&) = default;

  BigTENT(BigTENT& t) {
    value = t.get();
  }

  BigTENT(TENT<ValueType, DIM>&& t) {
    for (int i = 0 ; i < 1 << DIM ; i++) {
      if (t.children[i] != nullptr) {
	for (int j = 0 ; j < 1 << DIM ; j++) {
	  if (t.children[i][j] != nullptr)
	    children[(i << DIM) + j] = std::move(t.children[i][j]);
	  else
	    children[(i << DIM) + j] = std::make_unique<TENT<ValueType, DIM> >(t.children[i]);
	}
      }
    }
  }

  ValueType get() const {
    return value;
  }

  ValueType get(int indexes[DIM], unsigned int maxPrecision) const {
    if (maxPrecision <= 1)
      return value;
    const unsigned int index = getIndex(indexes, maxPrecision);
    if (children[index] == nullptr)
      return value;
    return children[index]->get(indexes, maxPrecision - 2);
  };
  
  void set(int indexes[DIM], unsigned int precision, ValueType newValue) {
    if (precision <= 1) {
      value = newValue;
      return;
    }
    const unsigned int index =  getIndex(indexes, precision);
    if (children[index] == nullptr) {
      children[index] = std::make_unique<TENT<ValueType, DIM> >();
    }
    children[index]->set(indexes, precision - 2, newValue);
    fold();
  };

  void del(int indexes[DIM], unsigned int precision) {
    const unsigned int index = getIndex(indexes, precision);
    if (precision == 2)
      return children[index].reset();
    if (precision == 1) {
      //TODO
    }
    children[index]->del(indexes, precision - 2);
    fold();
  };

  void fold() {
    for (auto &f : Folding<BigTENT<ValueType, DIM>>::instance().continuous)
      f(*this);
  };
};

#endif
