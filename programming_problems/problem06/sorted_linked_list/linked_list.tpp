#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  listPtr = nullptr;
  presentSize = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear();
  //since the clear function empties the list
  //we can effectively call it for the destructor
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  presentSize = x.presentSize;
  //check to see if the input has a null topPtr, because if
  //it does then the list is empty and that saves us a lot of work
  Node<T> *originalList = x.listPtr;
  if (originalList == nullptr){
    listPtr = nullptr;
  }
  else{
    //if we get here that means x wasn't empty, so we
    //have to create a list with all the same elements
    listPtr = new Node<T>;

    listPtr->setItem(originalList->getItem());
    //sets the item at topPtr

    //now we have to increment through the list to get
    //equal amounts of nodes in our new list as the old one
    Node<T> *newList = listPtr; //creates a pointer that starts at the beginning of the new list
    originalList = originalList->getNext(); //increments x before the loop
    
    while(originalList != nullptr){
      T newItem = originalList->getItem();
      Node<T> *tempPtr = new Node<T>(newItem);
      //creats a new node to hold the value at the current 
      //location of originalList
      
      newList->setNext(tempPtr);
      //since we originally set newList to point at the beginning
      //of our new list, and originalList has already been incremented
      //once before entering this loop, this ensures that
      //the new list reaches the correct size.

      newList = newList->getNext();
      originalList = originalList->getNext();
      //incrementing our two list pointers
    }//end while

    newList->setNext(nullptr);
    //since we exited the loop that means that newList points at 
    //the last item in the list, and thus, the next node should be null
  
  }//end else

}//end function

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  LinkedList<T> temp = x;
  x = y;
  y = temp;
  ~temp;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  //we can use the same logic from the copy constructor
  presentSize = x.presentSize;
  
  Node<T> *originalList = x.listPtr;
  if (originalList == nullptr){
    listPtr = nullptr;
  }
  else{
    listPtr = new Node<T>;

    listPtr->setItem(originalList->getItem());
    
    Node<T> *newList = listPtr; 
    originalList = originalList->getNext(); 
    
    while(originalList != nullptr){
      T newItem = originalList->getItem();
      Node<T> *tempPtr = new Node<T>(newItem);
      
      newList->setNext(tempPtr);

      newList = newList->getNext();
      originalList = originalList->getNext();
    }//end while

    newList->setNext(nullptr);
    
  }//end else

  return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  //TODO
  if (presentSize == 0){
    return true;
  }
  return false;
}

template <typename T>
std::size_t LinkedList<T>::getLength() const
{
  //TODO
  return presentSize;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  //check to see if the input position is acceptable
  if ((position >= 1 && position <= presentSize+1)){
    Node<T> *newNode = new Node<T>(item);
    //create a new node to hold the input item
    if (position == 1){
      newNode->setNext(listPtr);
      //this sets the next node after newNode to be the current beginning
      //of the list, so listPtr used to point at the first node
      //now it correctly points at the second

      listPtr = newNode;
      //here we shift listPtr back to the beginning of the list

      presentSize++;
      return true;
    }
    else{
      Node<T> *temp = listPtr;
      //create a pointer that starts at the first node

      for (std::size_t i = 1; i < position - 1; i++){
        temp = temp->getNext();
      }//here we increment temp to the right position in the list

      newNode->setNext(temp->getNext());
      //this sets the next attribute of the new node to the 
      //space after temp, for example if our input position 
      //was five, the loop iterates temp to be pointing at 
      //node 4, this line then makes the spot after the new
      //node what is currently node 5

      temp->setNext(newNode);
      //then by running this line, we have connected node4 to 
      //the new node we have placed in spot five

      presentSize++;
      return true;
    }
  }
  else{
    return false;
  }
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  
  //check input position
  if (position >= 1 && position <= presentSize && isEmpty()==false){
    Node<T> *deletedNode = listPtr;
    if (position == 1){
      listPtr = deletedNode->getNext();
      presentSize--;
      return true;
    }
    else{
      Node<T> *temp = listPtr;
      for(std::size_t i = 1; i < position - 1; i++){
        temp = temp->getNext();
      }//this gets the temp pointer to the node right before
      //the remove position

      deletedNode = temp->getNext();
      //sets deletedNode to the desired removed position

      temp->setNext(deletedNode->getNext());
      //this sets the next node after temp to the node after
      //the node at the removed position, effectively 
      //linking the node in front of and behind the deletedNode
      //together in the list
      presentSize--;
      return true;
    }
    //since we need to get rid of the deletedNode
    //in both cases we can just do it once outside of the
    //conditionals
    deletedNode->setNext(nullptr);
    delete deletedNode;
    deletedNode = nullptr;
  }
  return false;
}

template <typename T>
void LinkedList<T>::clear()
{
  for(std::size_t i = presentSize; i > 0; i--){
    remove(i);
  }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //create a temp pointer
  Node<T> *currentPointer = listPtr;
  for(std::size_t i = 1; i < position; i++){
    currentPointer = currentPointer->getNext();
  }//increment pointer to correct position

  T returnVal = currentPointer->getItem();
  //return the item at said position
  return returnVal;
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //can use pretty much the same logic from the get entry function
  //create a temp pointer
  Node<T> *currentPointer = listPtr;
  for(std::size_t i = 1; i < position; i++){
    currentPointer = currentPointer->getNext();
  }//increment pointer to correct position

  currentPointer->setItem(newValue);
}
