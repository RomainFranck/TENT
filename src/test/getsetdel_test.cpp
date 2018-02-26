#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "TENT.hpp"

TEST_CASE("GetSetDel") {
  TENT<int, 2> tent;

  int a[2] = {0, 0};
  int b[2] = {1, 1};

  tent.set(a, 0, 42);
  tent.set(a, 1, 12);
  tent.set(b, 1, 62);
  REQUIRE(tent.get(a, 0) == 42);
  REQUIRE(tent.get(a, 1) == 12);
  REQUIRE(tent.get(b, 1) == 62);
  tent.del(b, 1);
  REQUIRE(tent.get(b, 1) == 42);
}
