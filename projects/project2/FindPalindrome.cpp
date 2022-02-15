#include <string>
#include <vector>
#include <iostream>
#include <locale>
#include <stdio.h>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
  if (currentStringVector.size() == 0){
    string test = "";
    for (int i = 0; i < candidateStringVector.size(); i++){
      test = test + candidateStringVector[i];
    }
    if (isPalindrome(test)){
      numPals++;
      palin.push_back(candidateStringVector);
    }
  }
  else{
    for (int i = 0; i <currentStringVector.size(); i++){
      vector<string> tempCan = candidateStringVector;
      vector<string> tempCur = currentStringVector;
      tempCan.push_back(tempCur[i]);
      tempCur.erase(tempCur.begin() + i);
      if (cutTest2(tempCan, tempCur)){
	recursiveFindPalindromes(tempCan, tempCur);
      }
    }
  }
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
  numPals = 0;
}

FindPalindrome::~FindPalindrome()
{
  clear();
}

int FindPalindrome::number() const
{
  return numPals;
}

void FindPalindrome::clear()
{
  empty.clear();
  sentence.clear();
  palin.clear();
  numPals = 0;
  //this empties the vectors, freeing up the memory, and resets numPals to 0
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
  string test = "";
  string odd = "";
  int count = 0;
  vector<string> temp1 = stringVector;

  //this creates a test string that will hold the lower case version of
  //string vector, an odd string and a count integer,

  for(int i = 0; i < stringVector.size() ; i++){
    convertToLowerCase(temp1.at(i));
    test+=temp1[i];
  }//creates a string in lowercase equivalent to the input variable

  for(int i = 0; i < stringVector.size() ; i++){
    count = 0;
    for (int j = 0; j < test.length() ; j++){
      if (test[j] == test[i]){
	count++; //this counts to find the amount of times the character at
	//test[j] appears in the string
      }
    }
    if (count%2==1){
      odd+=test[i]; //this checks to see if the count is odd, and if it is
      //then test[i] is added to odds
    }
  }
  
  for (int i = 0 ; i < odd.length() ; i++){
    for (int j = 0 ; j < odd.length() ; j++){
      if (odd[i] != odd[j]){
        return false;
      }
    }
  }

    //this checks the length of the odd string to find out if there are any
    //two or more different characters that appear an odd number of times
    //the reason I can't just use a base the return value on the length of
    //the odd string, like I previously thought I might be able to, is that
    //even if only one character shows up an odd amount of times, it will be
    //added to the odds string one time for each instance it shows up, for
    //example if the letter a shows up 3 times in the original string then,
    //it will be in odds three times
  return true;
}
bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
  string test1, test2, longer, shorter;
  char letter;
  int count1, count2;
  vector<string> temp1 = stringVector1;
  vector<string> temp2 = stringVector2;
  //creates the necessary variables to compare the two inpur stringVectors
  //and makes sure that all the characters in 1 show up in 2

  //first we have to convert temp1 and test2 into lowercase and turn them
  //into strings test1 and test 2
  for (int i = 0; i < stringVector1.size(); i++){
    convertToLowerCase(temp1.at(i));
    test1 += temp1[i];
  }
  for (int i = 0; i < stringVector2.size(); i++){
    convertToLowerCase(temp2.at(i));
    test2 += temp2[i];
  }

  //next we check which of test1 and test2 is longer and set them equal to
  //the longer and shorter variables accordingly, this just makes
  //operating with them from here on out simpler;
  if(test1.length() > test2.length()){
    longer = test1;
    shorter = test2;
  }
  else{
    longer = test2;
    shorter = test1;
  }

  //now we check to see that the frequency of letters is the same or greater
  //in the longer string compared to the short one
  for (int i = 0; i<shorter.length(); i++){
    letter = shorter.at(i);
    for (int j = 0; j < shorter.length(); j++){
      if(shorter.at(j) == letter){
	count1++;
      }
    }//this increments count one for the amount of times letter appears in
    //the shorter string
    for (int k = 0; k < longer.length(); k++){
      if(longer.at(k) == letter){
	count2++;
      }
    }//increments count two for the amount of times letter appears in the
    //longer string
    if (count1>count2){
      return false;
    }//now we compare the count1 and count2 for each instance of i,
    //because as soon as it fails once we know it can no longer be
    //a palindrome
  }
  return true;
  //if we make it all the way to the end we know it is safe to return
  //true without checking any other conditions
}

bool FindPalindrome::add(const string & value)
{
  string temp = value; //storing the input variable since it is passed by
  //reference
  vector<string> lowercase = sentence;
  convertToLowerCase(temp); //gets the input in lowercase form

  //now we check to see if the input is only characters
  for (int i = 0; i < temp.length(); i++){
    if (!isalpha(temp[i])){
      return false;
    }
  }//this uses the isalpha function to determine if a the char value at
  //temp[i] is a letter

  for (int i = 0; i < sentence.size(); i++){
    convertToLowerCase(lowercase[i]);
    if (temp == lowercase[i]){
      return false;
    }
  }//since lowercase is a copy of the sentence vector, comparing temp to a
  //lowercase version of each string at location i in the sentence vector
  //determines if we have any repeat words

  //if we pass those tests then we can safely add our input value to our
  //sentence vector
  sentence.push_back(value);

  if(cutTest1(sentence)){
    recursiveFindPalindromes(empty, sentence);
  }
  return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
  string test;
  vector<string> temp = stringVector;
  vector<string> lowercase = sentence;
  //because with this function we are getting the input as a vector of
  //strings rather than an individual one, we will have to use the same logic
  //as before just scaled up.

  //this converts all the strings in the input vector to lowercase and adds
  //the lower case version to our test string
  for(int i = 0; i < stringVector.size(); i++){
    convertToLowerCase(temp.at(i));
    test = test + temp[i];
  }

  //now we test that every character is a letter;
  for (int i = 0; i < test.length(); i++){
    if (!isalpha(test[i])){
      return false;
    }
  }

  //now we convert the current sentence string to lower case to check for
  //repeat words
  for (int i = 0; i < lowercase.size(); i++){
    convertToLowerCase(lowercase.at(i));
  }

  //now we check for repeated words in stringVector and sentence
  for (int i = 0; i < stringVector.size(); i++){
    //this first nested loop checks for redundacy in the input
    for (int j = 0; j < stringVector.size(); j++){
      if ((temp[i] == temp[j]) and (j!=i)){
	return false;
      }//I add the (j!=i) conditional because without it, it would throw
      //false everytime the j loop got to the same spot as the i loop
    }

    //now we test for repreats in sentence
    for (int k = 0; k < sentence.size(); k++){
      if (temp[i] == lowercase[k]){
	return false;
      }
    }//end second nested loop
  }//end main loop

  //now we add each string in the input vector to the sentence vector
  //because we can assume everything else passed

  for (int i = 0; i < stringVector.size(); i++){
    sentence.push_back(stringVector[i]);
  }

  //now we reset our counter to zero and check and see if the first cut test
  //still passes and if it does then the numPal will be correctly found again
  //if not then it is then correctly still set to zero
  numPals = 0;
  if (cutTest1(sentence)){
    recursiveFindPalindromes(empty, sentence);
  }

  return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return palin;
}

