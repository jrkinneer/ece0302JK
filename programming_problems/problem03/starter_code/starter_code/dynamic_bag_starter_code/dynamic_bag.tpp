#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() {
	currentIndex = 0;
	presentSize = 100;
	arr = new T [presentSize];
}
  
template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag& x){
	presentSize = x.presentSize;
	currentIndex = x.currentIndex;
	arr = new T [presentSize];
	for (std::size_t i = 0 ; i < presentSize ; i++){
		arr[i] = x.arr[i];
	}
}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){
	presentSize = 0;
	delete [] arr;
}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T>& x)
{  
	presentSize = x.presentSize;
	arr = new T [presentSize];
	currentIndex = x.currentIndex;
	for (std::size_t i = 0 ; i < presentSize ; i++){
		arr[i] = x.arr[i];
  	}
  	return *this;
}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{ 
  if (currentIndex >= 0){
	  if (currentIndex < presentSize){
		arr[currentIndex] = item;
		currentIndex++;
		return true;
	  }
	  else{
		//psuedo code
		T *placeHolder = new T [presentSize]; //creates a 			placeholder array to hold the current values of arr while 			the memory that arr points to is re-allocated
		for (std::size_t i = 0; i < presentSize ; i++){
	  		placeHolder[i] = arr[i]; //copies arr[] to 							  placeHolder[]
	  	}
		presentSize = presentSize + 100; //increase the size of the 							  new array
		delete [] arr; //dealocates the existing arr mem.
		arr = new T [presentSize]; //dynamically allocates a larger 							array
		for (std::size_t i = 0 ; i < currentIndex ; i++){
			arr[i] = placeHolder[i]; //recopies the previous 						values of arr to the larger array
		}
		arr[currentIndex] = item; //adds item to the latest index 							in arr[]
		currentIndex ++; //increments the index
		
	  	return true;
	  } //end nested else
  } // end large if
  else{
	return false;
  }
}

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  T *placeHolder = new T [presentSize];
  for (std::size_t i = 0 ; i < presentSize ; i++){
	placeHolder[i] = arr[i];
  }//copies the existing arr into the placeholder
  
  std::size_t loc = -1;
  for (std::size_t i = 0 ; i<presentSize ; i++){
	if (arr[i] == item){
		loc = i;
	}
  } //this finds the location of the item to be removed
  
  if (loc == -1){ //if loc is still negative then the item does not exist and cannot be removed
	return false;
  }
  else{
	delete [] arr;
	arr = new T [presentSize];
	for (std::size_t x = 0; x < loc ; x++){
		arr[x] = placeHolder[x];
	}//adds the original values of arr before the removed item back into the array
	for (std::size_t x = loc ; x <(presentSize - 1) ; x++){
		arr[x] = placeHolder[x+1];
	}//adds the remaing half of the original values back to the new array
	currentIndex--;
	return true;
  }
}

template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  if (currentIndex == 0){
	return true;
  }
  else{
	return false;
  }
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return currentIndex;
  //I chose to return this value over presentSize because currentIndex shows how many values have been added to the array
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  for (std::size_t i = 0; i < presentSize ; i++){
	if (arr[i] == item){
		return true;
	}
  }
  return false;
}

template<typename T>
void DynamicBag<T>::clear(){
  currentIndex = 0;
  delete[] arr;
  arr = new T [presentSize];
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t freq;
  for (std::size_t i = 0 ; i < presentSize ; i++){
	if (arr[i] == item){
		freq++;
	}
  }
  return freq;
};
