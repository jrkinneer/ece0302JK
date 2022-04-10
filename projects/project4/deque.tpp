#include "deque.hpp"

template <typename T>
Deque<T>::Deque(){
    headPtr = nullptr;
    tailPtr = nullptr;
    count = 0;
}

template <typename T>
Deque<T>::~Deque(){
    while(!isEmpty()){
        popFront();
    }
}

template <typename T>
Deque<T>::Deque(const Deque<T> &rhs){
    count = rhs.count;
    Node<T> *originalPtr = rhs.headPtr;

    //if input deque is empty
    if (originalPtr == nullptr){
        headPtr = nullptr;
        tailPtr = nullptr;
    }
    else{
        //creates a new node for the headpointer with
        //the same item as rhs has at the head
        headPtr = new Node<T>(originalPtr->getItem());
        
        //so here we point the tail at the head because that is the base
        //case then we create a new list pointer that also points at the heac
        //and we increment the originalPtr once
        tailPtr = headPtr;
        Node<T>* newListPtr = headPtr;
        originalPtr = originalPtr->getNext();

        //now we increment through all the nodes in the original
        //list setting items correctly and incrementing the originalPTr
        while(originalPtr != nullptr){
            Node<T>* newPtr = new Node<T>(originalPtr->getItem());
            
            //sets the newest node to be next in the list
            newListPtr->setNext(newPtr);

            //increments the new list ptr
            newListPtr = newListPtr->getNext();

            //updates tail ptr to be the new node
            tailPtr = newListPtr;

            //increment original ptr
            originalPtr = originalPtr->getNext();
        }
    }
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T> &rhs){
    //can use same logic as copy constructor
    count = rhs.count;
    Node<T> *originalPtr = rhs.headPtr;

    if (originalPtr == nullptr){
        headPtr = nullptr;
        tailPtr = nullptr;
    }
    else{
        headPtr = new Node<T>(originalPtr->getItem());
        tailPtr = headPtr;
        Node<T>* newListPtr = headPtr;
        originalPtr = originalPtr->getNext();
        while(originalPtr != nullptr){
            Node<T>* newPtr = new Node<T>(originalPtr->getItem());
            newListPtr->setNext(newPtr);
            newListPtr = newListPtr->getNext();
            tailPtr = newListPtr;
            originalPtr = originalPtr->getNext();
        }
    }
    return *this;
}

template <typename T>
bool Deque<T>::isEmpty() const noexcept{
    return count==0;
}

template <typename T>
void Deque<T>::pushFront(const T &item){
    //creates a new node and pointer
    Node<T>* newPtr = new Node<T>(item);

    //check to see if the list is empty
    if (isEmpty()){
        headPtr = newPtr;
        tailPtr = newPtr;
    }
    else{
        //set the node after the new node
        //to the old head and move the old head
        //to the new node
        newPtr->setNext(headPtr);
        headPtr= newPtr;
    }
    count = count + 1;

}

template <typename T>
void Deque<T>::popFront(){
    //first we have to check to see if list is empty and if it 
    //is then we throw an exception
    if (isEmpty()){
        throw std::runtime_error("ERROR! Queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    //create a temp Ptr that points at the beginning of the list
    Node<T>* tempPtr = headPtr;

    //the rest is dependent on the size of the list
    if (count == 1){
        headPtr = nullptr;
        tailPtr = nullptr;
    }
    else{
        //shifts headPtr to be the second node
        headPtr = headPtr->getNext();
        
        //disconnects temp from the list
        tempPtr->setNext(nullptr);
    }
    //decrement count and delete memory
    count = count - 1;
    delete tempPtr;
    tempPtr = nullptr;
}

template <typename T>
T Deque<T>::front() const{
    return headPtr->getItem();
}

template <typename T>
void Deque<T>::pushBack(const T &item){
    //create the new node
    Node<T>* newPtr = new Node<T>(item);
    
    if (!isEmpty()){
        //attach old tail to this new node
        tailPtr->setNext(newPtr);
    }
    else{
        headPtr = newPtr;
        tailPtr = newPtr;
    }

    //increment tailPtr to new node
    tailPtr = newPtr;

    //increment count
    count = count + 1;
}

template <typename T>
void Deque<T>::popBack(){
    
    //check for empty list/exception
    if (isEmpty()){
        throw std::runtime_error("ERROR! Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    
    //check size
    if(count==1){
        headPtr = nullptr;
        tailPtr = nullptr;
        count = 0;
    }
    else{
        //creates a temporary ptrs to point at head and tail
        Node<T>* tempPtr = headPtr;
        
        //increments tempPtr until the second to last node
        while(tempPtr->getNext() != tailPtr){
            tempPtr = tempPtr->getNext();
        }
        //disconnect the new tail from the old tail
        //and shift the tailptr to the new tail
        tempPtr->setNext(nullptr);
        delete tailPtr;
        tailPtr = tempPtr;

        //decrement count
        count = count - 1;
    }
}

template <typename T>
T Deque<T>::back() const{
    return tailPtr->getItem();
}