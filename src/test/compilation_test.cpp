#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "TENT.hpp"

TEST_CASE("Size") {
  REQUIRE(TENT<int, 3>().children.size() == 8);
}
