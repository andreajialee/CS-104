#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>*parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value>*AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value>*AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value>*AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateRight(AVLNode<Key,Value>* current);
    void rotateLeft(AVLNode<Key,Value>* current);
    void rotateLR(AVLNode<Key,Value>* current);
    void rotateRL(AVLNode<Key,Value>* current);
    bool isNodeBalanced(AVLNode<Key,Value>* current);
    int curHeight(AVLNode<Key,Value>* left, AVLNode<Key,Value>* right);
    void fixInsert(AVLNode<Key,Value>* par, AVLNode<Key,Value>* current);
    void fixRemove(AVLNode<Key,Value>* par);
    AVLNode<Key,Value>* breakTie(AVLNode<Key,Value>* par);

};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
    if(!this->root_){
        AVLNode <Key,Value>* temp = new AVLNode<Key,Value>(new_item.first,new_item.second,NULL);
        temp->setHeight(1);
        this->root_ = temp;
        return;
    }
    AVLNode<Key,Value>* cur = static_cast<AVLNode<Key, Value>*>(this->root_);
    while(cur->getLeft()  || cur->getRight() ){
        // Cur == New Item, replace value with new item
        if(cur->getKey() == new_item.first){
            cur->setValue(new_item.second);
            return;
        }
        // Key < iterate Left
        else if(cur->getKey() > new_item.first){
            if(cur->getLeft()){
                cur = cur->getLeft();
            }
            else{
                break;
            }
        }
        // Key > iterate right
        else if(cur->getKey() < new_item.first){
            if(cur->getRight()){
                cur = cur->getRight();
            }else{
                break;
            }
        }
    }
    // No Key is == so create new node
    if(cur->getKey() != new_item.first){
        AVLNode<Key,Value>* temp = new AVLNode<Key,Value>(new_item.first,new_item.second,NULL);
        // Set Parent Pointers
        if(cur->getKey() < temp->getKey()){
            cur->setRight(temp);
        }
        else if(cur->getKey() > temp->getKey()){
            cur->setLeft(temp);
        }
        // Set Temp's Parent POinters
        temp->setParent(cur);
        int parH = cur->getHeight();
        // If Height is less than 2, it has to be fixed
        if(parH < 2){
            cur->setHeight(2);
            fixInsert(cur,temp);
        }
    }
    // Replace
    else{
        cur->setValue(new_item.second);
    }
}
template<class Key, class Value>
void AVLTree<Key, Value>:: fixInsert(AVLNode<Key,Value>* par, AVLNode<Key,Value>* child)
{
    if(par == NULL || par->getParent() == NULL){ 
        return;
    }
    AVLNode<Key,Value>* cur = par->getParent();
    int height = curHeight(cur->getLeft(),cur->getRight());
    // If Height is same after update, no need to rotate
    if(height == cur->getHeight()){  
        return;
    }
    // If Subtree is balanced
    else if(isNodeBalanced(cur)){ 
        cur->setHeight(height);
        fixInsert(cur,par);
    }
    // If Subtree is not balanced
    else if(!isNodeBalanced(cur)){
        // Two Children
        if(cur->getLeft() && cur->getRight()){  
            if(cur->getLeft()->getHeight() > cur->getRight()->getHeight()){
                // Left Zig-Zig
                if(cur->getLeft()==par && par->getLeft()==child){ 
                    rotateRight(cur);
                }
                // Left Right Zig-Zag
                else if(cur->getLeft()==par && par->getRight()==child){ 
                    rotateRL(cur);
                }
            }
            else{
                // Right Zig Zig
                if(cur->getRight()==par && par->getRight()==child){  
                    rotateLeft(cur);
                }
                // Right Left Zig-Zag
                else if(cur->getRight()==par && par->getLeft()==child){ 
                    rotateLR(cur);
                }
            }
        }
        // Left Child
        else if(cur->getLeft()  && cur->getRight() == NULL){
            // Left Zig-Zig
            if(cur->getLeft()==par && par->getLeft()==child){
                rotateRight(cur);
            }
            // Left Right Zig-Zag
            else if(cur->getLeft()==par && par->getRight()==child){
                rotateRL(cur);
            }
        }
        // Right Child
        else if(cur->getLeft() == NULL && cur->getRight() ){
            // Right Zig-Zig
            if(cur->getRight()==par && par->getRight()==child){
                rotateLeft(cur);
            }
            // Right Left Zig-Zag
            else if(cur->getRight()==par && par->getLeft()==child){
                rotateLR(cur);
            }
        }
    }   
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key,Value>* cur = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if(!cur || !this->root_)
        return;
    AVLNode<Key,Value>* par = cur->getParent();
    // Two Children -> swap with predecessor
    if(cur->getLeft()  && cur->getRight() ){  
        AVLNode<Key,Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(cur));
        if(pred){
            nodeSwap(cur,pred);
        }
    }
    
    // Left Child 
    if(cur->getLeft() && !cur->getRight()){ 
        AVLNode<Key,Value>* par = cur->getParent();
        AVLNode<Key,Value>* child = cur->getLeft();
        if(par){
            child->setParent(par);
            if(par->getLeft() == cur){
                par->setLeft(child);
            }else if(par->getRight() == cur){
                par->setRight(child);
            }
        }
        else{
            child->setParent(NULL);
            if(cur == this->root_){
                this->root_ = child;
            }
        }
    }
    // Right Child
    else if(!cur->getLeft() && cur->getRight() ){ 
        AVLNode<Key,Value>* par = cur->getParent();
        AVLNode<Key,Value>* child = cur->getRight();
        if(par){
            child->setParent(par);
            if(par->getLeft() == cur){
                par->setLeft(child);
            }
            else if(par->getRight() == cur){
                par->setRight(child);
            }
        }
        else{
            child->setParent(NULL);
            if(cur == this->root_){
                this->root_ = child;
            }
        }
    }
    // No Children -> parent's child = NULL || parent == NULL so change root
    else if(!cur->getLeft() && !cur->getRight()){  
        AVLNode<Key,Value>*par = cur->getParent();
        if(par){
            if(par->getLeft() == cur){
                par->setLeft(NULL);
            }
            else if(par->getRight() == cur){
                par->setRight(NULL);
            }
        }
        else if(cur==this->root_){
            this->root_ = NULL;
        }
    }
    
    bool left;
    if(par){
        if(cur == par->getLeft()){
            left = true;
        }
        else if(cur==par->getRight()){
            left = false;
        }
    }
    if(left && par){ 
        if(!isNodeBalanced(par->getLeft())){   
            fixRemove(par->getLeft());
        }
    }
    else if(!left && par){    
        if(!isNodeBalanced(par->getRight())){   
            fixRemove(par->getRight());
        }
    }
    delete cur;
    fixRemove(par);
}
template<class Key, class Value>
void AVLTree<Key,Value>:: fixRemove(AVLNode<Key,Value>* par){
    if(par == NULL){
        return;
    }
    if(!isNodeBalanced(par)){
        AVLNode<Key,Value>* child = breakTie(par);
        AVLNode<Key,Value>* grand = breakTie(child);
        // Left Zig-Zig
        if(par->getLeft()==child && child->getLeft()==grand){   
            rotateRight(par);
            par->setHeight(curHeight(par->getLeft(),par->getRight()));
            child->setHeight(curHeight(child->getLeft(),child->getRight()));
            fixRemove(child->getParent());
        }
        // Right Zig-Zig
        else if(par->getRight()==child && child->getRight()==grand){   
            rotateLeft(par);
            par->setHeight(curHeight(par->getLeft(),par->getRight()));
            child->setHeight(curHeight(child->getLeft(),child->getRight()));
            fixRemove(child->getParent());
        }
        // Left Right Zig-Zag
        else if(par->getLeft()==child && child->getRight()==grand){
            rotateRL(par);
            child->setHeight(curHeight(child->getLeft(),child->getRight()));
            grand->setHeight(curHeight(grand->getLeft(),grand->getRight()));
            par->setHeight(curHeight(par->getLeft(),par->getRight()));
            fixRemove(grand->getParent());
        }
        // Right Left Zig-Zag
        else if(par->getRight()==child && child->getLeft()==grand){  
            rotateLR(par);
            child->setHeight(curHeight(child->getLeft(),child->getRight()));
            grand->setHeight(curHeight(grand->getLeft(),grand->getRight()));
            par->setHeight(curHeight(par->getLeft(),par->getRight()));
            fixRemove(grand->getParent());
        }
    }
    // Heights are == so no need to rotate
    else if(par->getHeight() == curHeight(par->getLeft(),par->getRight())){
        return;
    }
    // Rotate to fix tree
    else{
        par->setHeight(curHeight(par->getLeft(),par->getRight()));
        fixRemove(par->getParent());
    }
}
template<class Key, class Value>
void AVLTree<Key, Value>:: rotateLeft(AVLNode<Key,Value>* cur)
{
    // TODO
    if(!cur && !cur->getRight()){
        return;
    }
    AVLNode<Key,Value>* mid = cur->getRight();
    AVLNode<Key,Value>* midLeft = mid->getLeft();
    mid->setParent(cur->getParent());
    if(cur->getParent()){
        if(cur==cur->getParent()->getLeft()){   // Left Child
            cur->getParent()->setLeft(mid);
        }
        else{   // Right Child
            cur->getParent()->setRight(mid);
        }
    }
    if(midLeft){
       midLeft->setParent(cur);
    }
    cur->setParent(mid);
    mid->setLeft(cur);
    cur->setRight(midLeft);
    // Replace root_
    if(cur == this->root_){
        this->root_ = mid;
    }
    // Change Height
    cur->setHeight(curHeight(cur->getLeft(), cur->getRight()));
    mid->setHeight(curHeight(mid->getLeft(), mid->getRight()));
}
template<class Key, class Value>
void AVLTree<Key, Value>:: rotateRight(AVLNode<Key,Value>* cur)
{
    // TODO
    if(!cur && !cur->getRight()){
        return;
    }
    AVLNode<Key,Value>* mid = cur->getLeft();
    AVLNode<Key,Value>* midRight = mid->getRight();
    mid->setParent(cur->getParent());
    if(cur->getParent()){
        if(cur==cur->getParent()->getLeft()){   // Left Child
            cur->getParent()->setLeft(mid);
        }
        else{   // Right Child
            cur->getParent()->setRight(mid);
        }
    }
    if(midRight){
        midRight->setParent(cur);
    }
    cur->setParent(mid);
    mid->setRight(cur);
    cur->setLeft(midRight);
    // Replace root_
    if(cur == this->root_){
        this->root_ = mid;
    }
    // Change Height
    cur->setHeight(curHeight(cur->getLeft(), cur->getRight()));
    mid->setHeight(curHeight(mid->getLeft(), mid->getRight()));
}
template<class Key, class Value>
void AVLTree<Key, Value>:: rotateRL(AVLNode<Key,Value>* cur)
{
    // TODO
    AVLNode<Key,Value>* mid = cur->getLeft()->getRight();
    nodeSwap(cur,mid);
    AVLNode<Key,Value>* midRight = mid->getRight();
    // Fix Nodes
    AVLNode<Key,Value>* left = cur->getLeft();
    AVLNode<Key,Value>* right = cur->getRight();
    mid->setRight(cur);
    cur->setParent(mid);

    mid->getLeft()->setRight(left);
    if(left){
        left->setParent(mid->getLeft());
    }
    cur->setLeft(right);
    if(right){
        right->setParent(cur);
    }
    cur->setRight(midRight);
    if(midRight){
        midRight->setParent(cur);
    }
    // Update Height
    mid->getLeft()->setHeight(curHeight(mid->getLeft()->getLeft(),mid->getLeft()->getRight()));
}
template<class Key, class Value>
void AVLTree<Key, Value>:: rotateLR(AVLNode<Key,Value>* cur)
{
    // TODO
    AVLNode<Key,Value>* mid = cur->getRight()->getLeft();
    nodeSwap(cur,mid);
    AVLNode<Key,Value>* midLeft= mid->getLeft();
    // Fix Nodes
    AVLNode<Key,Value>* left = cur->getLeft();  
    AVLNode<Key,Value>* right = cur->getRight();
    mid->setLeft(cur);
    cur->setParent(mid);
    mid->getRight()->setLeft(right);

    mid->getRight()->setLeft(right);
    if(right){
        right->setParent(mid->getRight());
    }
    cur->setLeft(midLeft);
    if(midLeft){
        midLeft->setParent(cur);
    }
    cur->setRight(left);
    if(left){
        left->setParent(cur);
    }
    
    //middate height
    mid->getRight()->setHeight(curHeight(mid->getRight()->getLeft(),mid->getRight()->getRight()));
}
template<class Key, class Value>
bool AVLTree<Key, Value>::isNodeBalanced(AVLNode<Key,Value>*cur){
    if(cur){
        // Two Children
        if(cur->getLeft()  && cur->getRight() ){
            if(abs(cur->getLeft()->getHeight()-cur->getRight()->getHeight()) > 1){
                return false;
            }
        }
        // Left Child
        if(cur->getLeft()!=NULL && cur->getRight()==NULL){
            if(cur->getLeft()->getHeight() > 1){
                return false;
            }
        }
        // RIght Child
        else if(cur->getLeft()==NULL && cur->getRight()!=NULL){
            if(cur->getRight()->getHeight() > 1){
                return false;   
            }
        }
        return true;
    }
    return false;
}
template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key,Value>:: breakTie(AVLNode<Key,Value>*par){
    // Left Child
    if(par->getLeft()!=NULL && par->getRight()==NULL){
        return par->getLeft();
    }
    // Right Child
    else if(par->getLeft()==NULL && par->getRight()!=NULL){
        return par->getRight();
    }
    // Two Children
    else if(par->getLeft()!=NULL && par->getRight()!=NULL){ // Returns child with larger height
        if(par->getLeft()->getHeight()<par->getRight()->getHeight()){  
            return par->getRight();
        }
        else if(par->getLeft()->getHeight()>par->getRight()->getHeight()){
            return par->getLeft();
        }
        else{   // Height is equal
            if(par==par->getParent()->getLeft()){   // Left Child
                return par->getLeft();
            }
            else if(par==par->getParent()->getRight()){
                return par->getRight();
            }
        }
    }
    return NULL;
}
template<class Key, class Value>
int AVLTree<Key, Value>::curHeight(AVLNode<Key,Value>* left,AVLNode<Key,Value>* right){
    // Left Child
    if(left&&!right){
        return left->getHeight()+1;
    }
    // Right Child
    else if(!left&&right){
        return right->getHeight()+1;
    }
    // Two Children
    else if(left&&right){
        return std::max(left->getHeight(), right->getHeight()) + 1;
    }
    return 1;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
