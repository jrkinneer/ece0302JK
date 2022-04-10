#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "abstract_deque.hpp"
#include <exception>
#include <iostream>
#include <cstdlib>
#include "abstract_deque.hpp"
#include "Node.hpp"

template <typename T>
class Deque : public AbstractDeque<T>{

  public:
    //constructor
    Deque();

    //destructor
    ~Deque();

    //copy constructor and operator
    Deque(const Deque<T> &rhs);
    Deque& operator=(const Deque& rhs);

    //overwriting virtual functions
    bool isEmpty() const noexcept;
    void pushFront(const T & item);
    void popFront();
    T front() const;
    void pushBack(const T & item);
    void popBack();
    T back() const;
    
  private:
    Node<T> *headPtr;
    Node<T> *tailPtr;
    std::size_t count;
    //the two pointers point to the beginning and end nodes
    //of the deque respectively, and then count just keeps
    //track of the total number of items in the deque
  
};

#include "deque.tpp"

#endif
