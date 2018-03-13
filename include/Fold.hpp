#ifndef FOLD_HPP_
#define FOLD_HPP_

#include <functional>

#include "ITENT.hpp"

template<typename ValueType, unsigned int DIM> requires
class Fold {
  std::function<bool(ITENT<ValueType, DIM>) predicate;
  std::function<ITENT<ValueType, DIM>(bool) action;
};

#endif
