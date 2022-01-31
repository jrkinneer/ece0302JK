#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"
#include <iostream>

// THIS IS JUST AN EXAMPLE
// There should be at least one test per Bitset method

TEST_CASE( "Test bitset construction", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "test bitset construction with input length", "[cons_length]" ){

  Bitset b(6);
  REQUIRE(b.size() == 6);
  REQUIRE(b.good());
}

TEST_CASE( "test bitset construction with string input", "[cons_string]"){
  Bitset b("11110000");
  REQUIRE(b.size() == 8);;
  REQUIRE(b.good());
  REQUIRE(b.asString() == "11110000");
}

TEST_CASE( "test size function", "[size_func]"){
  Bitset b(10);
  REQUIRE(b.size() == 10);
  REQUIRE(b.good());
}

TEST_CASE( "test good() function", "[good_func]"){
  Bitset b;
  b.toggle(10);
  REQUIRE(!b.good());
}

TEST_CASE( "test set function", "[set_func]"){
  Bitset b;
  REQUIRE(b.good());
  b.set(7);
  REQUIRE(b.test(7));
}

TEST_CASE( "test reset function", "[reset_func]"){
  Bitset b("11110000");
  REQUIRE(b.good());
  b.reset(7);
  REQUIRE(!b.test(7));
}

TEST_CASE( "test toggle function", "[toggle_func]"){
  Bitset b;
  REQUIRE(b.good());
  b.toggle(7);
  REQUIRE(b.test(7));
}

TEST_CASE( "testing the test function", "[test_func]"){
  Bitset b;
  REQUIRE(b.good());
  REQUIRE(!b.test(0));
}

TEST_CASE( "test asString function", "[string_func]"){
  Bitset b;
  REQUIRE(b.good());
  b.toggle(7);
  REQUIRE(b.test(7));
  REQUIRE(b.asString() == "10000000");
}


