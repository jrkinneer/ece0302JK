#include "bitset.hpp"

#include <iostream>
#include <string>

Bitset::Bitset(){
  length = 8;
  validity = true;
  bset = new intmax_t[length];
  for (int i = 0; i < length ; i++){
    bset[i] = 0;
  }
}

Bitset::Bitset(intmax_t size){
  if (size<=0){
    validity = false;
  }
  else{
    length = size;
    validity = true;
    bset = new intmax_t[length];
    for (int i = 0; i < length ; i++){
      bset[i] = 0;
    }
  }
}

Bitset::Bitset(const std::string & value){
  length = value.length();
  bset = new intmax_t[length];
  for (int i = 0; i < length ; i++){
    if (value.at(i) == '0' or value.at(i) == '1'){
      bset[(length-1)-i] = value.at(i) - '0';
      validity = true;
    }
    else{
      validity = false;
    }
  }
}

Bitset::~Bitset(){
  delete [] bset;
  bset = nullptr;
  length = 0;
  validity = false;
}

//end of constructors and destructors

//member functions
intmax_t Bitset::size() const{
  return length;
}

bool Bitset::good() const{
  return validity;
}

void Bitset::set(intmax_t index){
  if ((index <= length-1) and (index >= 0)){
    bset[index] = 1;
  }
  else{
    validity = false;
  }
}

void Bitset::reset(intmax_t index){
  if ((index <= length-1) and (index >= 0)){
    bset[index] = 0;
  }
  else{
    validity = false;
  }
}

 void Bitset::toggle(intmax_t index){
   if ((index <= length-1) and (index >= 0)){
       if (bset[index] == 0){
	 bset[index] = 1;
       }
       else{
	 bset[index] = 0;
       }
     }
   else{
     validity = false;
   }
 }
 
bool Bitset::test(intmax_t index){
  if ((index <= length-1) and (index >= 0)){
    if (bset[index] == 1){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    validity = false;
    return false;
  }
}

std::string Bitset::asString() const{
  std::string sB;
  for (int i = 0; i < length ; i++){
    if (bset[(length-1)-i] == 0){
      sB = sB + "0";
    }
    if (bset[(length-1)-i] == 1){
      sB = sB + "1";
    }
  }
  return sB;
}
 
