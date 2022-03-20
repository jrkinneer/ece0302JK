#include "dynamic_array_list.hpp"

#include <algorithm>
#include <stdexcept>

#include <iostream>

template <typename T>
DynamicArrayList<T>::DynamicArrayList()
{
  capacity = 10;
  size = 0;
  data = new T [capacity];
}
  
template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList<T>& x)
{
  capacity = x.capacity;
  size = x.size;
  data = new T [capacity];

  for (std::size_t i = 0; i < capacity; i++){
    data[i] = x.data[i];
  }

}
    
template <typename T>
DynamicArrayList<T>::~DynamicArrayList()
{
  size = 0;
  delete [] data;
  data = nullptr;
}

template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(DynamicArrayList<T> x)
{
  if (this != &x){
    capacity = x.capacity;
    size = x.size;
    delete [] data;
    data = new T [capacity];

    for (std::size_t i = 0; i < size; i++){
      data[i] = x.data[i];
    }

    return *this;
  }
}

template <typename T>
bool DynamicArrayList<T>::isEmpty()
{
  if (size > 0){
    return false;
  }
  return true;
}

template <typename T>
std::size_t DynamicArrayList<T>::getLength()
{
  return size;
}

template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& item)
{
  //I am assuming that a postion input outside the current
  //capacity of the array will not be recieved
  
  //so first I check to see if position equals size because if 
  //it does then that is the easiest insertion because of how 
  //zero indexing works
  //if an array of size five, has elements 0,1,2 filled then the 
  //size is three, and position 3 is also open
  if (position == size){
    data[position] = item;
    size++;
    //check to see if the array needs resized
    if (size == capacity){
      T* temp = new T [capacity];
      for (std::size_t i = 0; i < size; i++){
        temp[i] = data[i];
      }//hold old list

      delete [] data;
      data = nullptr; //delete old mem. allocation

      //allocate more mem.
      capacity *= 2;
      data = new T [capacity];

      //new list
      for (std::size_t j = 0; j < size; j++){
        data[j] = temp[j];
      }//we can compare j against size as size==capacity
      //and temp holds no value past size
      delete [] temp;
      temp = nullptr;
    }//end resize
  }//end position == size
  else if(position < size){
    //increment size and check to see if the array needs resized
    size++;
    if (size == capacity){
      capacity *= 2;
    }
    //store the old data and the new input item into a temp
    //array
    T* temp= new T [capacity];
    std::size_t ind = 0;
    for (std::size_t i = 0; i < size; i++){
      if (position != i){
        temp[i] = data[ind];
        ind++;
      }
      else{
        temp[i] = item;
      }
    }

    //delete old array and relocate temp into data
    delete [] data;
    data = nullptr;
    data = new T [capacity];
    for (std::size_t j = 0; j < size; j++){
      data[j] = temp[j];
    }

    //delete the temp storage
    delete [] temp;
    temp = nullptr;
  }//end else if
  
}

template <typename T>
void DynamicArrayList<T>::remove(std::size_t position)
{
  if (position >= 0 || position < size){
    //checks that position is okay
    
    std::size_t ind = 0;
    T* temp = new T [size];
    
    //loops through old data and adds it to a temp variable
    //as long as its not the desired remove index
    for (std::size_t i = 0; i < size; i++){
      if (position != i){
        temp[ind] = data[i];
        ind++;
      }
    }

    //decrements size and deletes old data
    size--;
    delete [] data;
    data = nullptr;

    //stores new data into the correct array
    data = new T [capacity];
    for (std::size_t j = 0; j < size; j++){
      data[j] = temp[j];
    }

    //deletes temporary storage
    delete [] temp;
    temp = nullptr;
  }
  
}//end remove

template <typename T>
void DynamicArrayList<T>::clear()
{
  delete [] data;
  data = nullptr;
  size = 0;
}

template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position)
{
  return data[position];
}

template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position > -1 && position < size){
    data[position] = newValue;
  }
  
}
