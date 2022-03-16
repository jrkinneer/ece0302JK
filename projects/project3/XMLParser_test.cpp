#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

// TODO Implement tests of your Stack class and XMLParser class here

TEST_CASE( "Test Bag add", "[XMLParser]" )
{
	   INFO("Hint: testing Bag add()");
		// Create a Bag to hold ints
		Bag<int> intBag;
		int testSize = 2;
		int bagSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intBag.add(i);
			REQUIRE(success);
			bagSize = intBag.size();
			success = (bagSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack push", "[XMLParser]" )
{
	   INFO("Hint: testing Stack push()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 3;
		int stackSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test XMLParser tokenizeInputString", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
}

TEST_CASE("Test XMLParser tokenizeInputString string2", "[XMLParser]")
{
	XMLParser myXMLParser;
	string testString = "<head random#!>content</head>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
}

TEST_CASE("Test XMLParser tokenizeInputString string3", "[XMLParser]")
{
	XMLParser myXMLParser;
	string testString = "<starter random#!/>content</starter>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
}

TEST_CASE("Test XMLParser input vector", "[XMLParser]")
{
	XMLParser myXMLParser;
	vector<TokenStruct> vect;
	string testString = "<starter>content</starter>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	vect = myXMLParser.returnTokenizedInput();
	REQUIRE(success);
	REQUIRE(vect[1].tokenType==4);
	REQUIRE(vect[0].tokenString == "starter");
}

TEST_CASE("Test XMLParser parse token", "[XMLParser]")
{
	XMLParser myXMLParser;
	string testString = "<start>content</start>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	REQUIRE(myXMLParser.parseTokenizedInput());
}

TEST_CASE("Test XMLParser parse token string2", "[XMLParser]")
{
	XMLParser myXMLParser;
	string testString = "<?begin?><empty/><start><nest1>content</nest1></start>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	REQUIRE(myXMLParser.parseTokenizedInput());
}

TEST_CASE("Test XMLParser parse token pt3", "[XMLParser]")
{
	XMLParser myXMLParser;
	string testString = "<?begin?><empty/><start><nest1><badnest>content in here</nest1><start>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	REQUIRE(!myXMLParser.parseTokenizedInput());
}

TEST_CASE("Test XMLParser parse content by itself", "[XMLParser]")
{
	XMLParser myXMLParser;
	string testString = "<?begin?><empty/>content by itself<start><nest1>inside content</nest1><start>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	REQUIRE(!myXMLParser.parseTokenizedInput());
}

TEST_CASE("Test XMLParser containsElementName", "[XMLParser]")
{
	XMLParser myXMLParser;
	string testString = "<start>content</start>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	myXMLParser.parseTokenizedInput();
	REQUIRE(myXMLParser.containsElementName("start"));
}

TEST_CASE("Test XMLParser inputVector with no content", "[XMLParser]")
{
	XMLParser myXMLParser;
	vector<TokenStruct> vect;
	string testString = "<start>   </start>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	vect = myXMLParser.returnTokenizedInput();
	REQUIRE(success);
	std::cout<< vect[1].tokenString << std::endl;
	REQUIRE(vect.size() == 2);
}

TEST_CASE("Test XMLParser input vector with exception","[XMLParser]")
{
	XMLParser myXMLParser;
	vector<TokenStruct> vect;
	string testString = "<wontparse>    <starter>content</starter>     ";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	vect = myXMLParser.returnTokenizedInput();

	try {
		myXMLParser.containsElementName("start");
	}
	catch(std::logic_error){
		std::cout<<"caught"<<std::endl;
	}
}