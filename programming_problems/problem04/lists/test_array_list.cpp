#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE( "test is empty", "[ArrayList]" ) {
  ArrayList<int> list;
  REQUIRE(list.isEmpty());
}

TEST_CASE("test get length", "[ArrayList]"){
  ArrayList<int> list;
  list.insert(1,1);
  list.insert(2,2);
  list.insert(3,3);
  REQUIRE(list.getLength() == 3);
}

TEST_CASE("test get first entry", "[ArrayList]"){
  ArrayList<int> list;
  list.insert(1,1);
  REQUIRE(list.getEntry(1) == 1);
}

TEST_CASE("test get entry", "[ArrayList]"){
  ArrayList<int> list;
  list.insert(1,1);
  list.insert(2,2);
  list.insert(3,3);
  REQUIRE(list.getEntry(3) == 3);
  REQUIRE(list.getEntry(2) == 2);
}

TEST_CASE("test remove", "[ArrayList]"){
  ArrayList<int> list;
  list.insert(1,1);
  list.insert(2,2);
  list.insert(3,3);
  REQUIRE(list.getLength() == 3);
  list.remove(2);
  REQUIRE(list.getLength() == 2);
  REQUIRE(list.getEntry(2) == 3);
}

TEST_CASE("test clear", "[ArrayList]"){
  ArrayList<int> list;
  list.insert(1,1);
  list.insert(2,2);
  list.insert(3,3);
  list.clear();
  REQUIRE(list.isEmpty());
}

TEST_CASE("test set entry", "[ArrayList]"){
  ArrayList<int> list;
  list.insert(1,1);
  list.setEntry(1, 5);
  REQUIRE(list.getEntry(1) == 5);
}
