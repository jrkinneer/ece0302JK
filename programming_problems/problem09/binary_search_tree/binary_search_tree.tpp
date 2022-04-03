#include "binary_search_tree.hpp"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    clone(rhs.root);
}

// this is an alternative implementation using a stack to simulate the recursion
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::clone(Node<KeyType, ItemType>* rhs)
{
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(const BinarySearchTree<KeyType, ItemType>& rhs)
{
    if (&rhs == this)
        return *this;

    destroy();

    root = 0;
    clone(rhs.root);

    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    // TODO
    //so we need to compare the key value of the 
    //node to be inserted to the nearest node with open
    //branches and then add it to the left or right
    //to do this i am going to use the searcg function to 
    //find the node with the closest key value that has empty
    //branches that our input key can legally fill
    KeyType placeHolder1 = key;
    ItemType placeHolder2 = item;
    bool duplicate = retrieve(placeHolder1, placeHolder2);
    if (!duplicate){
        //basecase for if empty
        //std::cout<<"passed non duplicate"<<std::endl;
        if (isEmpty()){
            //std::cout<<"isEmpty condition"<<std::endl;
            root = new Node<KeyType, ItemType>;
            root->data = item;
            root->key = key;
            //std::cout<<"\n"<<std::endl;
            return true;
        }
        else{
            std::cout<<"non empty condition"<<std::endl;
            Node<KeyType, ItemType> *currentPtr;
            Node<KeyType, ItemType> *parentPtr;
            //won't really need to use to the parent pointer
            //but I need a filler input
            search(key, currentPtr, parentPtr);

            //so now currentPtr has been updated
            if (key < currentPtr->key){
                //std::cout<<"left branch condition"<<std::endl;
                Node<KeyType, ItemType>* newNodePtr = new Node<KeyType, ItemType>;
                currentPtr->left = newNodePtr;
                newNodePtr->data = item;
                newNodePtr->key = key;
                //std::cout<<"\n"<<std::endl;
                return true;
            }
            else{
                //std::cout<<"right branch condition"<<std::endl;
                Node<KeyType, ItemType>* newNodePtr = new Node<KeyType, ItemType>;
                currentPtr->right = newNodePtr;
                newNodePtr->data = item;
                newNodePtr->key = key;
                //std::cout<<"\n"<<std::endl;
                return true;
            }//end nested if/else
        }//end isEmpty if/else
    }//end check for duplicate item
    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if (isEmpty())
        return false; // empty tree

    // TODO

    Node<KeyType, ItemType> *currentPtr;
    Node<KeyType, ItemType> *parentPtr;
    search(key, currentPtr, parentPtr);

    //check for key match
    if (currentPtr->key != key){
        return false;
    }

    //if our deleted node is a leaf
    if (currentPtr->left == 0 && currentPtr->right == 0){
        //if our deleted node is not the root
        if (parentPtr != nullptr){
            if (parentPtr->key > key){
                parentPtr->left = nullptr;
            }
            else{
                parentPtr->right = nullptr;
            }
        }
        //if our deleted node is the root
        else{
            root = nullptr;
        }
        delete currentPtr;
        return true;
    }
    //deleted node has a right child
    else if(currentPtr->left == 0 && currentPtr->right != 0){
        //check for current node not equal root
        if (parentPtr != 0){
            //compares parent key to delete key, 
            //to know what side to attach to
            if (parentPtr->key > key){
                parentPtr->left = currentPtr->right;
            }
            else{
                parentPtr->right = currentPtr->right;
            }
        }
        else{
            root = currentPtr->right;
        }
        delete currentPtr;
        return true;
    } 
    //deleted node has left child
    else if(currentPtr->left != 0 && currentPtr->right == 0){
        //check for current node not equal root
        if (parentPtr != 0){
            //compares parent key to delete key, 
            //to know what side to attach to
            if (parentPtr->key > key){
                parentPtr->left = currentPtr->left;
            }
            else{
                parentPtr->right = currentPtr->left;
            }
        }
        else{
            root = currentPtr->left;
        }
        delete currentPtr;
        return true;
    }
    //deleted node has two children
    else if(currentPtr->left != 0 && currentPtr->right != 0){
        Node<KeyType, ItemType> *inorder_succ = currentPtr->right;
        Node<KeyType, ItemType> *inorder_succ_par = parentPtr;
        inorder(inorder_succ, currentPtr, inorder_succ_par);
        currentPtr->data = inorder_succ->data;
        currentPtr->key = inorder_succ->key;

        if (inorder_succ->right != 0){
            inorder_succ_par->left = inorder_succ->right;
        }
        else{
            inorder_succ_par->left = nullptr;
        }

        delete inorder_succ;
        return true;
    }
    return false; // default should never get here
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    // TODO: find inorder successor of "curr" and assign to "in"
    if (curr->left == 0){
        in = curr;
        return;
    }

    inorder(curr->left, in, curr);

    return;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(ItemType arr[], int size) {
   
    for (int i = 0; i < size; i++){
        for (int j = 0; j < i; j++){
            if (arr[i] == arr[j]){
                throw std::range_error("cannot have duplicate items");
            }
        }
    }

    BinarySearchTree<KeyType, ItemType> tree;
    Node<KeyType, ItemType>* parentPtr = 0;

    for (int i = 0; i < size; i++){
        tree.insert(arr[i], arr[i]);
    }

    Node<KeyType, ItemType> *index;
    index = tree.root;
    
    for (int i = 0; i < size; i++){
        index = tree.root;
        tree.inorder(tree.root, index, parentPtr);
        arr[i] = index->key;
        tree.remove(index->key);
    }

    tree.destroy();
}
