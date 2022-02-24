#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList(): LinkedList<T>()
{
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x)
{
}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(const SortedLinkedList<T>& x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty()
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength()
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{
  std::size_t index = 0;
  //this checks to see if the array is empty
  //if so item will be inserted in the first position
  if (isEmpty()){
    LinkedList<T>::insert(index + 1, item);
    //we shift the index by one in order to 
    //adjust to the 1 based indexing of the 
    //linkedList class
  }
  else{
    while(index < getLength() && item > getEntry(index)){
      index++;
    }//this increments the position variable, checking to see
    //if the enty at the current index is either still less than
    //the input item, and less than

    LinkedList<T>::insert(index + 1, item);
    //this inserts the item at the proper index
  }
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("empty list in remove");
  std::size_t index = 0;
  while(index < getLength()){
    if (getEntry(index) == item){
      break;
    }
    else{
      index++;
    }
  } 
  //here we are incrementing through the list until
  //we find where the desired item is, then we remove it
  LinkedList<T>::remove(index + 1);
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  //this is another place where we need to check and see if
  //the list is empty or if the position input is too high,
  //if either is true a range error is thrown
  if(isEmpty() || position >= getLength()){
    throw std::range_error("empty list in remove");
  }
  else{
    LinkedList<T>::remove(position + 1);
  }
}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position)
{
  //in the case where the list is empty or the 
  //position is higher than allowed then we need to throw 
  //a range expception
  if(isEmpty() || position >= getLength()){ 
    throw std::range_error("empty list in getEntry");
  }
  else{
    return LinkedList<T>::getEntry(position+1);
  }
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& newValue)
{
  // to do this, we can use the similiar logic to the 
  //insert function, just without actually inserting the 
  //new Value and just returning what index it would go at
  long int index = 0;
   while(index < getLength() && newValue > getEntry(index)){
    index++;
   }
  return index;
}
