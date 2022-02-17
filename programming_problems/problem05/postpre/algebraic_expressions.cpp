#include <string>
using std::string;

#include <iostream>

#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix) {
  //finds the last character in postfix
  char last = postfix.back();

  //if last is a letter, that means we have already gotten
  //all of the operators to the front of prefix
  //so we cycle through all of remainig post fix, keeping the
  //order of the letters in postfix, and appending them to 
  //prefix
  if (isalpha(last)){
    for (int i = 0; i < postfix.size(); i++){
      prefix.push_back(postfix.at(i));
    }
  }
  else{
    //if last isn't a letter that makes it an operator,
    //so we append it to prefix and then remove it from postfix
    //then we call the function recursively until all the 
    //operators are moved and only letters remain
    prefix.push_back(last);
    postfix.pop_back();
    convert(postfix, prefix);
  }
}
