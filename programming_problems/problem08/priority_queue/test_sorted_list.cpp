#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.hpp"
#include "sorted_list.hpp"

TEST_CASE("Testing Sorted List", "[sorted list]"){
    typedef SortedList<int, DynamicArrayList<int> > slst;

    slst list;
    list.insert(1);
    list.insert(10);
    list.insert(10000);
    list.insert(100);
    list.insert(1000);
    REQUIRE(list.getEntry(0) == 1);
    REQUIRE(list.getEntry(1) == 10);
    REQUIRE(list.getEntry(2) == 100);
    REQUIRE(list.getEntry(3) == 1000);
    REQUIRE(list.getEntry(4) == 10000);
    REQUIRE(list.getLength() == 5);

    list.remove(1);
    REQUIRE(list.getEntry(0) == 10);
    REQUIRE(list.getEntry(1) == 100);
    REQUIRE(list.getEntry(2) == 1000);
    REQUIRE(list.getEntry(3) == 10000);

    list.removeAt(0);
    REQUIRE(list.getEntry(0) == 100);
    REQUIRE(list.getEntry(1) == 1000);
    REQUIRE(list.getEntry(2) == 10000);

    list.remove(1000);
    REQUIRE(list.getEntry(0) == 100);
    REQUIRE(list.getEntry(1) == 10000);

    list.clear();
    REQUIRE(list.isEmpty());
}