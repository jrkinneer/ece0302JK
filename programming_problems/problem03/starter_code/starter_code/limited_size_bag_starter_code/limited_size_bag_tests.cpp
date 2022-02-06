#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("test copy constructor", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(0);
  b.add(1);
  LimitedSizeBag<int> a(b);
  REQUIRE(a.getCurrentSize() == 2);
}

TEST_CASE("test copy operator", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(0);
  b.add(1);
  LimitedSizeBag<int> a = b;
  REQUIRE(a.getCurrentSize() == 2);
}

TEST_CASE("test add function", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  REQUIRE(b.add(0));

  LimitedSizeBag<int> a;
  for (int i = 0; i < 100 ; i++){
    a.add(i);
  }
  REQUIRE(a.add(101) == false);
}

TEST_CASE("test remove function", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  for (int i = 0; i < 100 ; i++){
    b.add(i);
  }
  REQUIRE(b.remove(19));
  REQUIRE(b.getCurrentSize() == 99);
}

TEST_CASE("test isEmpty function", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  REQUIRE(b.isEmpty());
  b.add(0);
  REQUIRE(!b.isEmpty());
}

TEST_CASE("test getCurrentSize", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  for(int i = 0; i < 50 ; i++){
    b.add(i);
  }
  REQUIRE(b.getCurrentSize() == 50);
}

TEST_CASE("test contains", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(0);
  b.add(1);
  REQUIRE(b.contains(0));
  REQUIRE(b.contains(1));
}

TEST_CASE("test clear", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(0);
  b.add(1);
  REQUIRE(b.getCurrentSize() == 2);
  b.clear();
  REQUIRE(b.getCurrentSize() == 0);
}

TEST_CASE("test getFrequencyOf", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(1);
  b.add(1);
  b.add(1);
  REQUIRE(b.getFrequencyOf(1) == 3);
}

   
