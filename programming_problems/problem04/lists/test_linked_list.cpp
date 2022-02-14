#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE( "test constructor", "[LinkedList]" ) {
  LinkedList<int> L;
  REQUIRE(L.getLength() == 0);
}

TEST_CASE( "test insert", "[LinkedList]" ) {
  LinkedList<int> L;
  L.insert(1,1);
  REQUIRE(L.getEntry(1) == 1);
  REQUIRE(L.getLength() == 1);
  L.insert(2, 69);
  L.insert(3, 99);
  L.insert(4, 44);
  //list should be {1, 69, 99, 44}
  REQUIRE(L.getEntry(2) == 69);
  REQUIRE(L.getEntry(3) == 99);
  REQUIRE(L.getEntry(4) == 44);
}

TEST_CASE( "test remove", "[LinkedList]" ) {
  LinkedList<int> L;
  L.insert(1,1);
  L.insert(2,2);
  L.insert(3,3);
  L.remove(2);
  REQUIRE(L.getLength() == 2);
  REQUIRE(L.getEntry(2) == 3);
}

TEST_CASE( "test clear", "[LinkedList]" ) {
  LinkedList<int> L;
  L.insert(1,1);
  L.insert(2,2);
  L.insert(3,3);
  L.clear();
  REQUIRE(L.isEmpty());
}

TEST_CASE( "test copy constructor", "[LinkedList]" ) {
  LinkedList<int> L;
  L.insert(1,1);
  L.insert(2,2);
  L.insert(3,3);
  LinkedList<int> F(L);
  REQUIRE(F.getLength() == 3);
  REQUIRE(F.getEntry(3) == 3);
}

TEST_CASE( "test copy operator", "[LinkedList]" ) {
  LinkedList<int> L;
  L.insert(1,1);
  L.insert(2,2);
  L.insert(3,3);
  LinkedList<int> F = L;
  REQUIRE(F.getLength() == 3);
  REQUIRE(F.getEntry(3) == 3);
}
