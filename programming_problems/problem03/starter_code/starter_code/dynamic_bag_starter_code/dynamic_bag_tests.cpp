#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("testing the copy constructor", "[DynamicBag]"){
  DynamicBag<int> b;
  b.add(25);

  DynamicBag<int> a(b);

  REQUIRE(a.getCurrentSize() == 1);
}

TEST_CASE("testing copy operator", "[DynamicBag]"){
  DynamicBag<int> b;
  b.add(25);

  DynamicBag<int> a = b;

  REQUIRE(a.getCurrentSize() == 1);
}

TEST_CASE("testing add func & requiring an expanded array", "[DynamicBag]"){
  DynamicBag<int> b;
  for (int x = 0 ; x < 100 ; x++){
    b.add(x);
  }
  REQUIRE(b.add(101)==true);
  REQUIRE(b.getCurrentSize()==101);
}

TEST_CASE("testing remove function", "[DynamicBag]"){
  DynamicBag<int> b;
  for (int x = 0 ; x < 100 ; x++){
    b.add(x);
  }

  REQUIRE(b.remove(69) == true);
  REQUIRE(b.getCurrentSize() == 99);
}

TEST_CASE("testing is empty function", "[DynamicBag]"){
  DynamicBag<int> b;
  REQUIRE(b.isEmpty() == true);

  DynamicBag<int> a;
  a.add(1);
  REQUIRE(a.isEmpty() == false);
}

TEST_CASE("testing get current size function", "[DynamicBag]"){
  DynamicBag<int> b;
  b.add(0);
  b.add(1);
  b.add(2);
  REQUIRE(b.getCurrentSize() == 3);
}

TEST_CASE("testing contains function", "[DynamicBag]"){
  DynamicBag<int> b;
  for (int x = 0 ; x < 100 ; x++){
    b.add(x);
  }
  REQUIRE(b.contains(69) == true);
}

TEST_CASE("testing clear function", "[DynamicBag]"){
  DynamicBag<int> b;
  b.clear();
  REQUIRE(b.isEmpty()==true);
}

TEST_CASE("testing getFrequencyOf() function", "[DynamicBag]"){
  DynamicBag<int> b;
  b.add(1);
  b.add(1);
  b.add(1);
  REQUIRE(b.getFrequencyOf(1) == 3);
}

  
