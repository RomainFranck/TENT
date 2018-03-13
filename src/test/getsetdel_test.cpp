#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "TENT.hpp"

TEST_CASE("1000^2") {
  TENT<int, 2> tent;

  int index[2] = {0, 0};

  for (index[0] = 0 ; index[0] < 1000 ; index[0]++) {
    for (index[1] = 0 ; index[1] < 1000 ; index[1]++) {
      tent.set(index, 0, 1);
    }
  }
}


TEST_CASE("10000^3") {
  TENT<int, 3> tent;
  const int edge = 1000;
  int index[3];

  for (index[0] = -edge ; index[0] < edge ; index[0]++) {
    for (index[1] = -edge ; index[1] < edge ; index[1]++) {
      for (index[2] = -edge ; index[2] < edge ; index[2]++) {
	tent.set(index, 0, 1);
      }
    }
  }
}

