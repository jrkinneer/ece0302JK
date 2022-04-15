
#ifndef _HEAP_PRIORITY_QUEUE_H_
#define _HEAP_PRIORITY_QUEUE_H_

#include "abstract_priority_queue.hpp"
#include "dynamic_array_list.hpp"

template <typename T>
class HeapPriorityQueue: public AbstractPriorityQueue<T>
{
public:
    
    // return true if the priority queue is empty
    bool isEmpty();
    
    // insert item into the queue
    void add(const T& item);
    
    // remove highest priority item from the queue
    void remove();
    
    // get the item with the highest priority from the queue
    T peek();
    
private:
    
    DynamicArrayList<T> lst;
};

template <typename T>
bool HeapPriorityQueue<T>::isEmpty()
{
    //todo
    return lst.isEmpty();
}

template <typename T>
void HeapPriorityQueue<T>::add(const T& item)
{
    //todo
    //gets the length of the dynamic list and inserts the 
    //new item at the last node
    std::size_t newIndex = lst.getLength();
    lst.insert(newIndex, item);

    //temporary storage variables
    bool inPlace = false;
    std::size_t parentIndex;
    T temp;

    while (newIndex > 0 && !inPlace){
        //loop runs as long as the new index hasn't hit zero
        //or the new item has been put in place
        parentIndex = (newIndex - 1)/2;
        if (lst.getEntry(newIndex)<= lst.getEntry(parentIndex)){
            inPlace = true;
        }
        else{
            //if the value at newIndex isn't less than the parentIndex
            //then we set temp to the new value
            temp = lst.getEntry(newIndex);
            //then move the value at the parent index down to the new index
            lst.setEntry(newIndex, lst.getEntry(parentIndex));
            //move the new value up to the parent index
            lst.setEntry(parentIndex, temp);
            //then set the newIndex to equal the parent index
            newIndex = parentIndex;
        }
    }
}

template <typename T>
void HeapPriorityQueue<T>::remove()
{
    //todo
    if (lst.getLength()>0){
        bool inPlace = false;
        std::size_t leftChild, rightChild, bigChild, bigChildIndex;
        std::size_t newIndex = 0;
        
        //sets root value to the last node to the last node that got added.
        lst.setEntry(0, lst.getEntry(lst.getLength()-1));
        lst.remove(lst.getLength() - 1); //removes the most recent node
        T temp;

        while(!inPlace){
            if (2*newIndex + 1 >= lst.getLength()){
                inPlace = true;
                continue;
            }
            else if(2*newIndex + 2 >= lst.getLength()){
                bigChildIndex = 2*newIndex + 1;
                bigChild = lst.getEntry(bigChildIndex);
            }
            else{
                leftChild = lst.getEntry(2*newIndex + 1);
                rightChild = lst.getEntry(2*newIndex + 2);
                if (leftChild >= rightChild){
                    bigChild = leftChild;
                    bigChildIndex = 2*newIndex + 1;
                }
                else{
                    bigChild = rightChild;
                    bigChildIndex = 2*newIndex + 2;
                }
            }
            temp = lst.getEntry(newIndex);
            if (temp < bigChildIndex){
                lst.setEntry(newIndex, bigChild);
                lst.setEntry(bigChildIndex, temp);
                newIndex = bigChildIndex;
            }
            else{
                inPlace = true;
            }
        }//end while
    }//end main if
}

template <typename T>
T HeapPriorityQueue<T>::peek()
{
    //todo
    return lst.getEntry(0);
}


#endif // _HEAP_PRIORITY_QUEUE_H_
