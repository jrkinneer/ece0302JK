#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "fancyPower.hpp"

// write your test cases here
TEST_CASE("test case, 2 to the second power", "fancyPower"){
  int b;
  b = fancyPower(2, 2);
  REQUIRE(b==4);
}

TEST_CASE("test case, 2 to the third power", "fancyPower"){
  int b;
  b = fancyPower(3, 2);
  REQUIRE(b==8);
}
