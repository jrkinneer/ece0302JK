#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  count = 0;
  headlistptr = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  count = x.count;
  Node<T> *tempPtr = x.headlistptr;
  //makes the count of x and this the same
  //also makes a pointer, tempPtr, equal to the existing headlistptr of x
  if (tempPtr == nullptr){
	headlistptr == nullptr;
  }
  else{
	Node<T> *newPtr = new Node<T>;
	headlistptr = newPtr; //dynamically allocates a new Node pointer to headlist poster
	headlistptr->setItem(tempPtr->getItem());
	//these lines determine the item at the headlistptr of list x
	//and set it as the item at headlistptr of our current list
	for (std::size_t i = 1; i < count; i++){
		tempPtr = tempPtr->getNext(); 
		//finds the next node of list x
		
		Node<T> *nodePtr = new Node<T>();
		//creates a pointer to a new node
		
		nodePtr->setItem(tempPtr->getItem());
		//sets the item at the new nodePtr to the item currently
		//at tempPtr
		
		newPtr->setNext(nodePtr);
		//sets the next variable of newPtr to the nodePtr
		
  		newPtr = newPtr->getNext();
  		//shifts the node of nodePtr forward
  	}
        newPtr->setNext(nullptr);
        //this loop cycles through the nodes of list x, adding nodes, and shifting the next node until the lists are the same length, and finally outside of the loop making the next pointer point to nothing
        }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  //mostly the same logic as the copy constructor except for the addition of the clear() function to ensure no memory leaks
  clear();
  
  count = x.count;
  
  Node<T> *tempPtr = x.headlistptr;
  
  if (tempPtr == nullptr){
	headlistptr == nullptr;
  }
  else{
	Node<T> *newPtr = new Node<T>;
	
	headlistptr = newPtr; 
	
	headlistptr->setItem(tempPtr->getItem());
	
	for (std::size_t i = 1; i < count; i++){
		tempPtr = tempPtr->getNext(); 
		
		Node<T> *nodePtr = new Node<T>();
		
		nodePtr->setItem(tempPtr->getItem());
		
		newPtr->setNext(nodePtr);
		
  		newPtr = newPtr->getNext();
  	}
        newPtr->setNext(nullptr);
  }
  return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
	if (count == 0){
		return true;
	}
	else{
		return false;
	}
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return count;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  //first we check to see if position is 1 because that is like the base case I think
  if (position == 1){
	count++; //increment count because we are inputing an item
	Node<T> *tempPtr;
	tempPtr = headlistptr; //creates a new node that points to the current headlistptr
	Node<T> *newPtr = new Node<T>;
	headlistptr = newPtr; //this allocates a new pointer for our previously null headlistptr to be set equal to
	newPtr->setItem(item);
	newPtr->setNext(tempPtr); //links the next pointer to null;
  	return true;
  }
  //this checks to see if position input is greater than one but also not too much larger than the current size of the list
  else if ((position <= (count + 1)) && position>1){
  	count++;
  	Node<T> *tempPtr;
  	tempPtr = headlistptr;
  	for(std::size_t i = 2; i < position; i++){
		tempPtr = tempPtr->getNext();
		//this increments the tempPtr forward to the appropraite location in the list, which is one less than that of the insert location
	}
	Node<T> *nextPtr;
	nextPtr = tempPtr->getNext();
	Node<T> *newPtr = new Node<T>(item, nextPtr);
	tempPtr->setNext(newPtr);
	//these lines create a pointer nextPtr, that points to the location after tempPtr, which happens to be the desired input location, then a new node is created with pointer name newPtr, newPtr's constructor inputs are the desired input item and nextPtr because nextPtr points to the correct address of the desired input position, then tempPtr sets its next value as newPtr, because newPtr now sits in the following space in the list
	return true;
  }
  return false;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  //again check for position == 1 base case
  if (position == 1){
	count--;
	Node<T> *tempPtr;
	tempPtr = headlistptr->getNext();
	delete [] headlistptr;
	headlistptr = tempPtr;
	return true;
	//this condition creates a temporary ptr and its location is the location after the headlistptr, in this case, the original position 2, then the current value of headlistptr is deleted, removing that item and node, then headlistptr is made equal to tempPtr making the original second node now the first one
  }
  else if ((position <= count) && position>1){
	count--;
	Node<T> *tempPtr;
	Node<T> *deletedPtr;
	tempPtr = headlistptr;
	for (std::size_t i = 2; i < position; i++){
		tempPtr = tempPtr->getNext();
	}
	deletedPtr = tempPtr->getNext();
	tempPtr->setNext(deletedPtr->getNext());
	delete [] deletedPtr;
	deletedPtr = nullptr;
	return true;
	//this conditional first decrements the count, and then creates two new pointers, tempPtr is then set to the headlistptr, then it is incremented by the for loop to stop at the position right before the desired removal position, then deletedPtr is set to that location using tempPtr->getNext(), tempPtr is then set to the position after the removed index, the node and item at deletedPtr then gets deleted
  }
  return false;
}

template <typename T>
void LinkedList<T>::clear()
{
  count = 0;
  Node<T> *tempPtr = headlistptr;
  while(headlistptr != nullptr){
  	headlistptr = headlistptr->getNext();
  	tempPtr->setNext(nullptr);
  	delete tempPtr;
  	tempPtr = headlistptr;
  }
  //this logic increments through a all the nodes in the list, each time setting that node to nullptr, until headlistptr == nullptr, at which point the list is empty
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //check for position == 1 base case
  if (position == 1){
	return headlistptr->getItem();
  }
  else if ((position <= count) and (position>1)){
	Node<T> *tempPtr;
	tempPtr = headlistptr->getNext();
	for (std::size_t i = 2; i < position; i++){
		tempPtr = tempPtr->getNext();
	}
	return tempPtr->getItem();
	//this logic creates a temporary ptr and sets it as the second item in the list, then the tempPtr gets incremented forward until it is the value of position, which happens at position = i - 1, then the item at that ptr is returned
  }
  else{
	std::cout<<"Error, invalid input"<<std::endl;
  }
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //check for position == 1 base case
  if (position == 1){
	headlistptr->setItem(newValue);
  }
  else if ((position <= count) and (position>1)){
	Node<T> *tempPtr;
	tempPtr = headlistptr->getNext();
	for (std::size_t i = 2; i < position; i++){
		tempPtr = tempPtr->getNext();
	}
	tempPtr->setItem(newValue);
	//this logic creates a temporary ptr and sets it as the second item in the list, then the tempPtr gets incremented forward until it is the value of position, which happens at position = i - 1, then the item at that ptr is returned
  }
  else{
	std::cout<<"Error, invalid input"<<std::endl;
  }
}
