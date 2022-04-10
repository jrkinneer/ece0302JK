#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

// TODO

TEST_CASE( "Test construct/destruct/pushFront", "[deque]" ) {
    Deque<int> deq;
    deq.pushFront(1);
    deq.~Deque();
    REQUIRE(deq.isEmpty());
}

TEST_CASE("test pushFront/Back for one item", "[deque]"){
    Deque<int> deq;
    deq.pushFront(1);
    REQUIRE(deq.back() == 1);
    REQUIRE(deq.front() == 1);
    REQUIRE(!deq.isEmpty());

    Deque<int> deq1;
    deq1.pushBack(1);
    REQUIRE(deq1.back() == 1);
    REQUIRE(deq1.front() == 1);
    REQUIRE(!deq1.isEmpty());
}

TEST_CASE("test copy operator and constructor", "[deque]"){
    Deque<int> deq1;
    deq1.pushFront(3);
    deq1.pushFront(2);
    deq1.pushFront(1);

    Deque<int> deq2(deq1);
    Deque<int> deq3 = deq1;

    REQUIRE(deq2.back() == 3);
    REQUIRE(deq2.front() == 1);
    REQUIRE(deq3.back() == 3);
    REQUIRE(deq3.front() == 1);
}

TEST_CASE("test pop front/ push front", "[deque]"){
    Deque<int> deq;
    deq.pushFront(3);
    deq.pushFront(2);
    deq.pushFront(1);

    deq.popFront();
    REQUIRE(deq.front() == 2);
    deq.popFront();
    REQUIRE(deq.front() == 3);
    REQUIRE(deq.back() == 3);
    deq.popFront();
    REQUIRE(deq.isEmpty());
}

TEST_CASE("test pop back/ push back", "[deque]"){
    Deque<int> deq;
    deq.pushBack(1);
    REQUIRE(deq.front()==1);
    REQUIRE(deq.back()==1);
    
    deq.pushBack(2);
    REQUIRE(deq.back()==2);
    
    deq.pushBack(3);
    REQUIRE(deq.back()==3);
    
    deq.popBack();
    REQUIRE(deq.back()==2);
    
    deq.popBack();
    REQUIRE(deq.back()==1);
    REQUIRE(deq.front()==1);
    deq.popBack();
    REQUIRE(deq.isEmpty());
}