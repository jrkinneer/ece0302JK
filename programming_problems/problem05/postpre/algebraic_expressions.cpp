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
  //need to shift the operators to the left by two
  //or i guess shift the operands to the right by two
  
  //place the last character in postfix in a variable
  //then remove it from postfix
  char last = postfix.back();

  //base case is if the last character of post is a letter
  //if it is alpha append to prefix
  if (isalpha(last)){
    for (int i = 0; i < postfix.size(); i++){
      prefix.push_back(postfix.at(i));
    }
  }
  else{
  //if not append anyway, 
  //call convert twice, with any empty string and once with
  //the new prefix
    prefix.push_back(last);
    postfix.pop_back();
    convert(postfix, prefix);
  }
}
