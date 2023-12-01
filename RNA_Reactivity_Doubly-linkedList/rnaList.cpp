////  rnaList.cpp
//// 2023/8/21.
////
////here are the implementation of class dlist and class iterator.
//
////#include "rnaList.h"
//using namespace Project2;
//
////default constructor
//template <typename T>
//dlist<T>::dlist() : head(new node), tail(new node), listSize(0) {
//    //defualt construct list only has head and tail nodes
//    //head and tail are sentinel nodes that don't hold data
//    head->next = tail;
//    tail->prev = head;
//}
//
////copy constructor
//template <typename T>
//dlist<T>::dlist(const dlist & other)
//    : head(new node), tail(new node), listSize(0){
//    //initialized the list with just head and tail
//    head->next = tail;
//    tail->prev = head;
//    //call push back to insert new node at the end before tail node.
//    for (auto itr = other.begin(); itr != other.end(); ++itr) {
//        push_back(*itr);
//    }
//}
//
////iterator range constructor
//template <typename T>
//template <typename InputIterator>
//dlist<T>::dlist(InputIterator first, InputIterator last)
//    : head(new node), tail(new node), listSize(0) {
//    //similar to copy construction but with input iterators
//    head->next = tail;
//    tail->prev = head;
//    for (InputIterator itr = first; itr != last; ++itr) {
//        push_back(*itr);
//    }
//}
//
////destructor
//template <typename T>
//dlist<T>::~dlist() {
//    //remove nodes one by one starting at the end
//    while (!empty()) {
//        pop_back();
//    }
//    delete head;
//    delete tail;
//}
//
////copy assignment
//template <typename T>
//dlist<T> & dlist<T>::operator=(const dlist & other) {
//    //check for self assign
//    if (this != &other) {
//        //remove old nodes
//        while (!empty()) {
//            pop_back();
//        }
//        //push on copied new nodes
//        for (auto itr = other.begin(); itr != other.end(); ++itr) {
//            push_back(*itr);
//        }
//    }
//    return *this;
//}
//
////whether empty
//template <typename T>
//bool dlist<T>::empty() const{
//    return size() == 0;
//}
//
////return size of the list
//template <typename T>
//typename dlist<T>::size_type dlist<T>::size() const{
//    return listSize;
//}
//
////return the data of the first node
//template <typename T>
//T & dlist<T>::front() {
//    return *begin();
//}
//
////constant version of front()
//template <typename T>
//const T & dlist<T>::front() const{
//    return *begin();
//}
//
////return the last node's data
//template <typename T>
//T & dlist<T>::back() {
//    return *(--end());
//}
//
////constant version of end()
//template <typename T>
//const T & dlist<T>::back() const{
//    //since end() returns tail node, decrement is needed
//    return *(--end());
//}
//
////use insert function to push node with new data to the front
//template <typename T>
//void dlist<T>::push_front(const T & val) {
//    insert(begin(), val);
//}
//
////use erase() to remove the first node
//template <typename T>
//void dlist<T>::pop_front() {
//    if (!empty()) {
//        erase(begin());
//    }
//}
//
////use insert function to push node with new data to the back
//template <typename T>
//void dlist<T>::push_back(const T & val) {
//    insert(end(), val);
//}
//
////use erase() to remove the last node
//template <typename T>
//void dlist<T>::pop_back() {
//    if (!empty()) {
//        erase(--end());
//    }
//}
//
////insert new node with new data
//template <typename T>
//typename dlist<T>::iterator dlist<T>::
//insert(typename dlist<T>::iterator itr, const T &val) {
//    //creat a pointer to current node and increase list size
//    node *pitr = itr.current;
//    listSize++;
//    //create new node used to insert
//    node *newNode = new node(val, pitr->prev, pitr);
//    //assignment of adjacent nodes' prev, next pointer to connect the inserted
//    //node
//    pitr->prev->next = newNode;
//    pitr->prev = newNode;
//    //return iterator at inserted place
//    return iterator(newNode);
//}
//
//template <typename T>
//typename dlist<T>::iterator dlist<T>::
//erase(typename dlist<T>::iterator itr) {
//    //creat a pointer to current node.
//    node *pitr = itr.current;
//    iterator postErase(pitr->next);
//    //reassign the adjacent nodes connection to each other.
//    pitr->prev->next = pitr->next;
//    pitr->next->prev = pitr->prev;
//    //decrease list size, delete node, return iterator at post erased place.
//    listSize--;
//    delete pitr;
//    return postErase;
//}
//
////equivalent operator
//template <typename T>
//bool dlist<T>::operator==(const dlist & other) const{
//    //if not same size, definitely not equal
//    if (listSize != other.listSize) {
//        return false;
//    }
//    auto otherItr = other.begin();
//    //loop through each node and compare their data value
//    for (auto thisItr = this->begin(); thisItr != this->end(); ++thisItr) {
//        if (*thisItr != *otherItr) {
//            return false;
//        }
//        ++otherItr;
//    }
//    return true;
//}
//
////not equal
//template <typename T>
//bool dlist<T>::operator!=(const dlist & other) const{
//    return !(*this == other);
//}
//
////less than
//template <typename T>
//bool dlist<T>::operator<(const dlist& other) const{
//    //smaller size will be considered less than
//    if (this->listSize < other.listSize) {
//        return true;
//    } else if (this->listSize == other.listSize) {
//        auto thisItr = this->begin();
//        auto otherItr = other.begin();
//        //iterating through both list to compare the data in each nodes
//        while (thisItr != this->end() && otherItr != other.end()) {
//            if (*thisItr < *otherItr) {
//                return true;
//            } else if (*otherItr < *thisItr) {
//                return false;
//            }
//            ++thisItr;
//            ++otherItr;
//        }
//    }
//    else {
//        return false;
//    }
//    return false;
//}
//
////less and equal
//template <typename T>
//bool dlist<T>::operator<=(const dlist& other) const{
//    return (*this < other) || (*this == other);
//}
//
////greater
//template <typename T>
//bool dlist<T>::operator>(const dlist& other) const{
//    return !(*this <= other);
//}
//
////great and equal
//template <typename T>
//bool dlist<T>::operator>=(const dlist& other) const{
//    return !(*this < other);
//}
//
////iterator of the first data containing node
//template <typename T>
//typename dlist<T>::iterator dlist<T>::begin() {
//    return iterator(head->next);
//}
//
////constant begin.
//template <typename T>
//const typename dlist<T>::iterator dlist<T>::begin() const{
//    return iterator(head->next);
//}
//
////iterator of the tail node
//template <typename T>
//typename dlist<T>::iterator dlist<T>::end() {
//    return iterator(tail);
//}
//
////constant end.
//template <typename T>
//const typename dlist<T>::iterator dlist<T>::end() const{
//    return iterator(tail);
//}
//
////these are class iterator's implementation
////default constructor
//template <typename T>
//dlist<T>::iterator::iterator() : current(0){
//}
//
////iterator at the given nodes
//template <typename T>
//dlist<T>::iterator::iterator(typename dlist<T>::node* ptr) : current(ptr) {
//}
//
////equivalent ioerator
//template <typename T>
//bool dlist<T>::iterator::operator==(const iterator &other) const{
//    return current == other.current;
//}
//
////not equal
//template <typename T>
//bool dlist<T>::iterator::operator!=(const iterator &other) const{
//    return !(current == other.current);
//}
//
////pointer dereference, return the data of the iterated node
//template <typename T>
//T & dlist<T>::iterator::operator*() {
//    return current->data;
//}
//
////constant pointer dereference.
//template <typename T>
//const T & dlist<T>::iterator::operator*() const{
//    return current->data;
//}
//
////return the pointer to the data
//template <typename T>
//T * dlist<T>::iterator::operator->() {
//    return &(current->data);
//}
//
////constant return pointer
//template <typename T>
//const T * dlist<T>::iterator::operator->() const{
//    return &(current->data);
//}
//
////pre increment, iterator goes to the next node
//template <typename T>
//typename dlist<T>::iterator& dlist<T>::iterator::operator++() {
//    current = current->next;
//    return *this;
//}
//
////post increment, returns the copy of original iterator
//template <typename T>
//const typename dlist<T>::iterator dlist<T>::iterator::operator++(int) {
//    iterator temp = *this;
//    current = current->next;
//    return temp;
//}
//
////pre decrement, iterator goes to the previous node
//template <typename T>
//typename dlist<T>::iterator& dlist<T>::iterator::operator--() {
//    current = current->prev;
//    return *this;
//}
//
////post decrement
//template <typename T>
//const typename dlist<T>::iterator dlist<T>::iterator::operator--(int) {
//    iterator temp = *this;
//    current = current->prev;
//    return temp;
//}
