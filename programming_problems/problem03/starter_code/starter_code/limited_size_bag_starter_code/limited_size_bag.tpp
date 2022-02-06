#include "limited_size_bag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
	arr = new T [maxSize];
}
  

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag(const LimitedSizeBag& x){
	currentIndex = x.currentIndex;
	arr = new T [maxSize];
	for(int i = 0; i < maxSize; i++){
		arr[i] = x.arr[i];
	}
}
    
template<typename T>
LimitedSizeBag<T>::~LimitedSizeBag(){
	currentIndex = 0;
	delete[] arr;
}
  
template<typename T>
LimitedSizeBag<T>& LimitedSizeBag<T>::operator=(LimitedSizeBag<T>& x)
{  
  delete[] arr;
  this -> currentIndex = x.currentIndex;
  this -> arr = new T [maxSize];
  for (int i = 0; i < maxSize ; i++){
	arr[i] = x.arr[i];
  }
  return *this;
}

template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  if (currentIndex < maxSize){
	arr[currentIndex] = item;
	currentIndex++;
	return true;
  }
  else{
	return false;
  }
}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  T *placeHolder = new T [maxSize];
  int loc = -1;
  for(int i = 0; i < maxSize ; i++){
	placeHolder[i] = arr[i];
	if (arr[i] == item){
		loc = i;
	}
  }
  if(loc == -1){
	return false;
  }
  else{
	delete[] arr;
	arr = new T [maxSize];
	for (int i = 0; i < loc ; i++){
		arr[i] = placeHolder[i];
	}
	for (int i = loc; i < (maxSize - 1) ; i++){
		arr[i] = placeHolder[i-1];
	}
	currentIndex--;
	return true;
  }
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  if (currentIndex == 0){
  	return true;
  }
  else{
	return false;
  }	
}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return currentIndex;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  for(int i = 0; i < maxSize ; i++){
	if (arr[i] == item){
		return true;
	}
  }
  return false;
}

template<typename T>
void LimitedSizeBag<T>::clear(){
	currentIndex = 0;
	delete[] arr;
	arr = new T [maxSize];
}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  std:size_t freq = 0;
  for (int i = 0; i < currentIndex ; i++){
	if (arr[i] == item){
		freq++;
	}
  }
  return freq;
};
