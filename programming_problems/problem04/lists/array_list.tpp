#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList() {
	arrSize = 0;
	arr = new T [arrSize];
}

template <typename T>
ArrayList<T>::~ArrayList() {
	arrSize = 0;
	delete [] arr;
	arr = nullptr;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList & rhs){
	delete [] arr;
	arr = nullptr;
	arrSize = rhs.arrSize;
	arr = new T [arrSize];
	for (std::size_t i = 0 ; i < arrSize ; i++){
		arr[i] = rhs.arr[i];
	}
}

template <typename T>
ArrayList<T> & ArrayList<T>::operator=(const ArrayList & rhs){
	delete [] arr;
	arr = nullptr;
	this->arrSize = rhs.arrSize;
	arr = new T [arrSize];
	for (std::size_t i = 0; i < arrSize ; i++){
		arr[i] = rhs.arr[i];
	}
  return *this;
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept {
  if (arrSize == 0){
	return true;
  }
  else{
	return false;
  }
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept {
  return arrSize; //since arrIndex keeps track of how many items are in the arry it can be used as the return value of this function
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){
	//checks if the position is less then one because the user
	//is using 1 indexing or larger than the current list
	if ((position < 1) || ((position - 1) > arrSize)) {
		return false;
	}
	//executes if the position input is acceptable
	else{
		T *temp = new T [arrSize];
		for (std::size_t i = 0; i < arrSize ; i++){
			temp[i] = arr[i];
		}//copies existing array into a temporary one
		
		delete [] arr;
		arr = nullptr;
		arrSize ++; 
		arr = new T [arrSize]; //creates a new array one bigger
		
		std::size_t spot = 0; 
		for (std::size_t i = 0; i < arrSize  ; i++){
			if (i != (position - 1)){
				arr[i] = temp[spot];
				spot++;
			}
			else{
				arr[i] = item;
			}
		} //cycles through the new number of items, if the index i doesn't correspond to the desired insert position then the old array is copied over, if it is then item is inserted at arr[i]
//spot and i increment at different rates so that item can be inserted when it is appropriate
		delete [] temp;
		temp = nullptr;
		return true;
	}	
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position){
	if (((position - 1) > arrSize) || position < 1){
		return false;
	}
	else{
		T *temp = new T [arrSize - 1];
		std:size_t index = 0;
		for (std::size_t i = 0; i < arrSize ; i++){
			if (i != (position - 1)){
				temp[i] = arr[index++];
			}
		}
		arrSize--;
		delete [] arr;
		arr = nullptr;
		arr = new T [arrSize];
		for (std::size_t i = 0; i < arrSize; i++){
			arr[i] = temp[i];
		}
		delete [] temp;
		temp = nullptr;
		return true;
	}
}

template <typename T>
void ArrayList<T>::clear() {
	delete [] arr;
	arr = nullptr;
	arrSize = 0;
	arr = new T [arrSize];
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  return (arr[position - 1]);
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
	if (((position - 1) <= arrSize) and (position >= 1)){
		arr[position - 1] = newValue;
	}
}
