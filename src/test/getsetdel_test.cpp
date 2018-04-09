#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "TENT.hpp"
#include "BigTENT.hpp"

TEST_CASE("1000^2") {
  TENT<int, 2> tent;

  int index[2] = {0, 0};
  
  for (index[0] = 0 ; index[0] < 1000 ; index[0]++)
    for (index[1] = 0 ; index[1] < 1000 ; index[1]++)
      tent.set(index, 0, 1);
}


TEST_CASE("getset") {
  TENT<int, 2> tent;
  
  int index[2] = {0, 0};
  
  tent.set(index, 1, 1);
  REQUIRE( tent.get(index, 1) == 1 );
}

TEST_CASE("getsetBIGTENT") {
  BigTENT<int, 2> bigtent;

  int index[2] = {2, 1};

  bigtent.set(index, 2, 1);
  REQUIRE( bigtent.get(index, 2) == 1);
}
