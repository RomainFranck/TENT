#ifndef ITENT_HPP_
#define ITENT_HPP_

#include <type_traits>

template<typename T>class Folding;

template<typename ValueType, unsigned int DIM>
class ITENT {
public:
  typedef ValueType valuetype;
  static const unsigned int dim = DIM;

  virtual ValueType get(int indexes[DIM], unsigned int maxPrecision) const = 0;
  virtual void set(int indexes[DIM], unsigned int precision, ValueType value) = 0;
  virtual void del(int indexes[DIM], unsigned int maxPrecision) = 0;
  virtual void fold() = 0;
};

#endif
