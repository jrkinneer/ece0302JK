#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

TEST_CASE("Testing Priority Queue", "[priority queue]") {
  typedef SortedList<int, DynamicArrayList<int> > SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;

  // TODO
  REQUIRE(pq.isEmpty());
  pq.add(1);
  pq.add(10);
  pq.add(5);
  REQUIRE(pq.peek() == 10);
  pq.remove();
  REQUIRE(pq.peek() == 5);
  pq.remove();
  REQUIRE(pq.peek() == 1);
  pq.remove();
  REQUIRE(pq.isEmpty());
}
