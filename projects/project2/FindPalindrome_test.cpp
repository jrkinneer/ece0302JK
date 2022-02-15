#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test FindPalindrome add a non-allowable word", "[FindPalindrome]" )
{
	INFO("Hint: add a single non-allowable word");
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE ("Testing FindPalindrome cutTest1", "[cutTest1]"){
  std::vector<std::string> test{"ranch","hcnar"};
  FindPalindrome f;
  REQUIRE(f.cutTest1(test));
}

TEST_CASE ("Testing FindPalindrome cutTest2", "[cutTest2]"){
  std::vector<std::string> sub1{"ranch", "hcnar"};
  std::vector<std::string> sub2{"ranch", "hcnary"};
  FindPalindrome e;
  REQUIRE(e.cutTest2(sub1, sub2));
}

TEST_CASE("testing add string", "[addString]"){
  std::vector<std::string> test1{"cat", "dog"};
  FindPalindrome b;
  b.add(test1);

  REQUIRE(!b.add("CAT"));
}

TEST_CASE("testing add vector", "[addVector]"){
  std::vector<std::string> test1{"cat", "dog"};
  std::vector<std::string> test2{"CAT", "DOG"};

  FindPalindrome b;
  b.add(test1);
  REQUIRE(!b.add(test2));
}
