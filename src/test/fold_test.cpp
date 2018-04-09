#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

#include <TENT.hpp>
#include <Folding.hpp>

TEST_CASE("Fold") {
  TENT<int, 3> tent;

  std::function<void(ITENT<int, 3>&)> f = [&](ITENT<int, 3> &t) {
    std::cout << "TENT" << std::endl;
  };

  Folding<TENT<int, 3>>::instance().continuous.push_back(f);

  f = [&](ITENT<int, 3> &t) {
    std::cout << "ITENT" << std::endl;
  };

  Folding<TENT<int, 3>>::instance().continuous.push_back(f);
  
  int index[3] = {0, 0, 0};
  tent.set(index, 1, 1);
  std::cout << "--------------------------" << std::endl;
  tent.set(index, 3, 1);
}
