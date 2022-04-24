#include "frontier_queue.hpp"

// TODO implement the member functions here

//this function is to rebuild the heap after a pop operation
template <typename T>
void heapRebuild(int nodeIndex, std::vector<State<T>> &queue){
  bool leaf = 0;
  if ((2*nodeIndex+1 > queue.size()) && (2*nodeIndex+2 > queue.size())){
    //this is checking to see that the nodeIndex is a leaf
    //and the 2*node + 1 and 2*node + 2 would be the numbers
    //of the left and right child respectively
    leaf = true;
  }
  if (leaf == false){
    //if the previous statement didn't change the value
    //of the leaf variable we enter here

    //this gives number values to the children of the current node Index
    std::size_t leftChild = 2*nodeIndex + 1;
    std::size_t rightChild = leftChild + 1;
    std::size_t smallChild = rightChild;

    if (smallChild>=queue.size() || queue[leftChild].getFCost()<queue[rightChild].getFCost()){
      //this conditional is seeing if only the left child exists, 
      //or if the left child is correctly smaller than the right child
      //and thus sets the number index of the small child to the left child
      smallChild = leftChild;
    }
    if (queue[smallChild].getFCost() < queue[nodeIndex].getFCost()){
      //if the value of the smallChild aka the right child is 
      //smaller than the parent node Index we swap the parent node
      //with the right child
      
      //this works because iter_swap takes two iterator pointers to swap,
      //and the .begin() function returns an iterator pointer,
      //that we then shift by adding nodeIndex and smallChild respectively
      std::iter_swap(queue.begin()+nodeIndex,queue.begin()+smallChild);

      //then we recursively call heapRebuild with smallChild, as the node Index
      //to check the rest of the tree
      heapRebuild(smallChild, queue);
    }
  }
}

template <typename T>
State<T> frontier_queue<T>::pop() {

  //TODO
  //implement this the same way we implemented pop in the heap lecture. Compare using getFCost
  // needs return statement

  if (queue.size() == 1){
    //if there is only one element in the vector, store
    //queue[0] in a temp variable, eliminated q[0] from memory
    //and return temp
    State<T> temp = queue[0];
    queue.pop_back();
    return temp;
  }
  else{
    State<T> temp = queue[0];
    queue[0]=queue[queue.size()-1];
    queue.pop_back();

    heapRebuild(0, queue);
    return temp;
  }
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {

  //TODO
  
  //implement this the same way we implemented push in the heap lecture.
  State<T> S(p, cost, heur);

  int newIndex = queue.size();
  bool inPlace = false;
  int parentIndex;
  queue.push_back(S);

  while (newIndex>=0 && !inPlace){
    //here we continuously run this loop as newIndex isn't less than zero
    //or inPlace has been updated

    parentIndex = (newIndex-1)/2; //set parentIndex to appropriate num.
    if (queue[newIndex].getFCost() >= queue[parentIndex].getFCost()){
     //if the newIndex child value is greater than the parentIndex value
     //then the new value has been correctly and successfully added
     inPlace = true;
    }
    else{
      //if the opposite is true, we swap the new Node with its parent
      State<T> swap = queue[newIndex];
      queue[newIndex] = queue[parentIndex];
      queue[parentIndex] = swap;
      newIndex = parentIndex;
    }
  }
}

template <typename T>
bool frontier_queue<T>::empty() {

  //TODO
  return (queue.size() == 0);
}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) {

  //TODO
  //simple for loop that checks contents
  for (int i = 0; i < queue.size(); i++){
    if (queue[i].getValue()==p){
      return true;
    }
    return false;
  }

}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {

  //TODO
  //simple for loop that checks values and pathCost
  for (int i=0; i < queue.size(); i++){
    if (queue[i].getValue() == p && queue[i].getPathCost()>cost){
      queue[i].updatePathCost(cost);
    }
  }
}


