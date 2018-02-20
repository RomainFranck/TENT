#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Compilation") {
  int c = 0;

  REQUIRE(0 == c);
}
