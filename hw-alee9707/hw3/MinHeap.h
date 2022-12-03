
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <ctime>
#include <iostream>

template <class T>
class MinHeap {
    public:
        MinHeap (int d);
        /* Constructor that builds a d-ary Min Heap
        This should work for any d >= 2,
        but doesn't have to do anything for smaller d.*/

        ~MinHeap ();

        void add (T item, int n);
        /* adds the item to the heap, with the given priority. */

        const T & peek () const;
        /* returns the element with smallest priority.  
		Break ties however you wish.  
		Throws an exception if the heap is empty. */

        int peekValue () const;
        /* returns the element with smallest priority.  
		Break ties however you wish.  
		Throws an exception if the heap is empty. */

       void remove ();
        /* removes the element with smallest priority.
		Break ties however you wish.
        Throws an exception if the heap is empty. */

        bool isEmpty ();
        /* returns true iff there are no elements on the heap. */

        void print();

        void update(T item, int n);

        int size();

        const T & returnVal(int i) const;
        
    private:
        std::vector <std::pair<T,int> > min; 
        int size_;
        int d_;
        void trickleDown(int n); 
        void bubbleUp(int n);
};

template<typename T> 
MinHeap<T>::MinHeap(int d){
    if(d >= 2){
        d_ = d;
    }
    size_ = 0;
}

template<typename T> 
MinHeap<T>::~MinHeap<T>(){
}

template<typename T>
void MinHeap<T>::add(T item, int n){
    min.push_back(std::pair<T,int>(item, n));
    size_++;
    bubbleUp(size_-1);
}

template<typename T>
void MinHeap<T>::update(T item, int n){
    int val = 0;
    for(int i=0; i<size_; i++){
        if(min[i].first==item) {
            val = i;
            break;
        }
    }
    min[val].second = n;
    bubbleUp(val);
    trickleDown(val);
}

template<typename T>
const T & MinHeap<T>::peek() const{
    if(min.empty()){
        throw std::length_error("Error: cannot peek from empty heap");
    }
    return min[0].first;
}

template<typename T>
int MinHeap<T>::peekValue() const{
    if(min.empty()){
        throw std::length_error("Error: cannot peek from empty heap");
    }
    return min[0].second;
}

template<typename T>
const T & MinHeap<T>::returnVal(int i) const{
    if(min.empty()){
        throw std::length_error("Error: cannot peek from empty heap");
    }
    return min[i].first;
}

template<typename T>
void MinHeap<T>::remove(){
    if(isEmpty()){
        throw std::length_error("Error: cannot remove from empty heap");
    }
   swap(min[0], min.back());    // Swap top and bottom priority 
    min.pop_back();     // Remove
    size_--;
    trickleDown(0); // Sort
}

template<typename T>
bool MinHeap<T>::isEmpty(){
    if(size_ == 0){
        return true;
    }
    return false;
}

template<typename T>
void MinHeap<T>::trickleDown(int n){
    // Check Bounds
    if(d_*n+1 >= size_){
        return;
    }
    // Find Smallest Priority Node
    int child = (d_*n)+1;
    int temp = child;
    for(int i = 2; i <= d_; i++){
        if(temp+i-1 < size_){
            if(min[child].second > min[temp+(i-1)].second){
                child = temp+(i-1);
            }
        }
    }
    // If node < child
    if(min[n].second > min[child].second){
        swap(min[n], min[child]);
        trickleDown(child);
    }
    if(min[n].second == min[child].second){
        if(min[n].first < min[child].first){
            swap(min[n],min[child]);
            trickleDown(child);
        } 
    }
}

template<typename T>
void MinHeap<T>::bubbleUp(int n){
    int parent = (n-1)/d_; // Node of Parent

    if (min[n].second < min[parent].second) {
        swap(min[parent], min[n]);
        bubbleUp(parent);
    }
    if(min[n].second == min[parent].second) {
        if (min[n].first > min[parent].first) {
            swap(min[parent], min[n]);
            bubbleUp(parent);
        }
    }
}

template<typename T>
void MinHeap<T>::print(){
    for(int i = 0; i < size_; i++){
        std::cout << min[i].first << " ";
    }
    std::cout << std::endl;
}

template<typename T>
int MinHeap<T>::size(){
    return size_;
}
