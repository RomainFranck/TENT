#ifndef ITENT_HPP_
#define ITENT_HPP_

template<typename ValueType, unsigned int DIM>
class ITENT {
public:
  virtual ValueType get(int indexes[DIM], unsigned int maxPrecision) const = 0;
  virtual void set(int indexes[DIM], unsigned int precision, ValueType value) = 0;
  virtual void del(int indexes[DIM], unsigned int maxPrecision) = 0;
};

#endif
