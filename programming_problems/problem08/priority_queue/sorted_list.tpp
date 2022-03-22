#include "sorted_list.hpp"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> & x)
{
  plist = x.plist; // use copy assignment to implement copy construction
}

template <typename T, typename L>
SortedList<T, L>& SortedList<T, L>::operator=(const SortedList<T, L>& x)
{
  plist = x.plist;
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty()
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength()
{
  return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T& item)
{
  // TODO
  //here we determine if the plist is empty or not
  std::size_t ind = 0;
  if (isEmpty()){
    //if it is empty we insert item at the beginning or ind = 0
    plist.insert(ind, item);
  }
  else{
    //if plist is not empty then we increment it using this while loop
    //this loop is checking to make sure that ind is not larger than 
    //the total length of the list, and that the data at the current value
    //of ind is not larger than item, these two checks gaurantee  that the
    //the plist remains sorted correctly.
    while (ind < getLength() && item > getEntry(ind)){
      ind++;
    }
    //then when we get the correct final value for ind, we simply
    //insert it accordingly
    plist.insert(ind, item);
  }
}

template <typename T, typename L>
void SortedList<T, L>::remove(const T& item)
{
  // TODO
  //again we check if the list is empty, this time the if is 
  //checking to make sure it isn't empty
  if (!isEmpty()){
    std::size_t pos = getPosition(item);
    if (pos != -1){
      plist.remove(pos);
    }
  }
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position)
{
  return plist.getEntry(position);
}

template <typename T, typename L>
long int SortedList<T, L>::getPosition(const T& newValue)
{
  // TODO
  std::size_t ind = 0;
  while (ind < getLength()){
    if (getEntry(ind) == newValue){
      return ind;
    }
    ind++;
  }
  return -1;
}
