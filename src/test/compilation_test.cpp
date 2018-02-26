#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "TENT.hpp"

TEST_CASE("Size") {
  REQUIRE(TENT<int, 0>().children.size() == 1);
  REQUIRE(TENT<int, 1>().children.size() == 2);
  REQUIRE(TENT<int, 2>().children.size() == 4);
  REQUIRE(TENT<int, 3>().children.size() == 8);
}
