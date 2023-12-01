//  dlist.h
//  2023/8/19.
//
//header file that contain class dlist which creates doubly-linked list, allow-
//ing traversing and access of each node, supports basic operations.
//class iterator is implemented to as doubly-linked list iterator support the
//node's iterating and traversing.

#ifndef DLIST_H
#define DLIST_H

#include <cstddef>
#include <iterator>
#include <list>

namespace Project2 {

template <typename T>
class dlist {
    
private:
    //nodes that connects to the previous and next nodes
    struct node {
        T data;
        node *prev;
        node *next;
        node(const T& da = T(), node *pre = 0, node *nex = 0)
        :data(da), prev(pre), next(nex) {}
    };
    //size of the list, head and tail nodes.
    size_t listSize;
    node *head;
    node *tail;
    

public:
    // Types
    class iterator;
    
    // Implementaiton of the iterator class
    class iterator
    : public std::iterator<std::bidirectional_iterator_tag, T> {
        friend class dlist<T>;
    public:
        typedef const T const_reference;
        
        //default constructor
        iterator() : current(0) {
        }
        
        //constructor taking a pointer to a node for current node iteration
        explicit iterator(typename dlist<T>::node *ptr) : current(ptr) {
        }
        
        //equality
        bool operator==(const iterator &other) const{
            return current == other.current;
        }
        
        //not equal
        bool operator!=(const iterator &other) const{
            return !(current == other.current);
        }
        
        //return the data in the iterated node
        T &operator*() {
            return current->data;
        }
        
        //const pointer dereferencing
        const T &operator*() const{
            return current->data;
        }
        
        //return the pointer to the current node's data
        T *operator->() {
            return &(current->data);
        }
        
        //const return pointer
        const T *operator->() const{
            return &(current->data);
        }

        //pre increment, iterator goes to the next node
        iterator &operator++() {
            current = current->next;
            return *this;
        }

        //post increment, returns the copy of original iterator
        const iterator operator++(int) {
            iterator temp = *this;
            current = current->next;
            return temp;
        }

        //pre decrement, iterator goes to the previous node
        iterator &operator--() {
            current = current->prev;
            return *this;
        }

        //post decrement
        const iterator operator--(int) {
            iterator temp = *this;
            current = current->prev;
            return temp;
        }
    private:
        node *current;
    };
    
    
    typedef size_t size_type;
    typedef T value_type;
    typedef const T const_reference;
    // Default constructor
    dlist() : head(new node), tail(new node), listSize(0) {
    //defualt construct list only has head and tail nodes
    //head and tail are sentinel nodes that don't hold data
    head->next = tail;
    tail->prev = head;
    }
        // Copy constructor
    dlist(const dlist &other)
        : head(new node), tail(new node), listSize(0) {
        //initialized the list with just head and tail
        head->next = tail;
        tail->prev = head;
        //call push back to insert new node at the end before tail node.
        for (auto itr = other.begin(); itr != other.end(); ++itr) {
            push_back(*itr);
        }
    }
        // Iterator range constructor
    template <typename InputIterator> dlist(InputIterator first,
                                            InputIterator last)
            : head(new node), tail(new node), listSize(0) {
            //similar to copy construction but with input iterators
        head->next = tail;
        tail->prev = head;
        for (InputIterator itr = first; itr != last; ++itr) {
            push_back(*itr);
        }
    }
        // Destructor
    ~dlist() {
        //remove nodes one by one starting at the end
        while (!empty()) {
            pop_back();
        }
        delete head;
        delete tail;
    }
        // Copy assginment operator
    dlist &operator=(const dlist &other) {
        //check for self assign
        if (this != &other) {
            //remove old nodes
            while (!empty()) {
                pop_back();
            }
            //push on copied new nodes
            for (auto itr = other.begin(); itr != other.end(); ++itr) {
                push_back(*itr);
            }
        }
        return *this;
    }
    // empty() & size()
    bool empty() const{
        return size() == 0;
    }
    
    //return size of the list
    size_type size() const{
        return listSize;
    }
    
    // front() & back()
    //return the data of the first node
    T &front() {
        return *begin();
    }
    
    //constant version of front()
    const T &front() const{
        return *begin();
    }
    
    //return the last node's data
    T &back() {
        return *(--end());
    }
    
    //constant version of end()
    const T &back() const {
        //since end() returns tail node, decrement is needed
        return *(--end());
    }
    
    // Modifiers
    //use insert function to push node with new data to the front
    void push_front(const T &val) {
        insert(begin(), val);
    }
    
    //use erase() to remove the first node
    void pop_front() {
        if (!empty()) {
            erase(begin());
        }
    }
    
    //use insert function to push node with new data to the back
    void push_back(const T &val) {
        insert(end(), val);
    }
    
    //use erase() to remove the last node
    void pop_back() {
        if (!empty()) {
            erase(--end());
        }
    }
    
    //insert new node with new data
    iterator insert(iterator itr, const T &val) {
        //creat a pointer to current node and increase list size
        node *pitr = itr.current;
        listSize++;
        //create new node used to insert
        node *newNode = new node(val, pitr->prev, pitr);
        //assignment of adjacent nodes' prev, next pointer to connect the inserted
        //node
        pitr->prev->next = newNode;
        pitr->prev = newNode;
        //return iterator at inserted place
        return iterator(newNode);
    }
    
    iterator erase(iterator itr) {
        //creat a pointer to current node.
        node *pitr = itr.current;
        iterator postErase(pitr->next);
        //reassign the adjacent nodes connection to each other.
        pitr->prev->next = pitr->next;
        pitr->next->prev = pitr->prev;
        //decrease list size, delete node, return iterator at post erased place.
        listSize--;
        delete pitr;
        return postErase;
    }
    
    // Comparision
    bool operator==(const dlist &other) const{
        //if not same size, definitely not equal
        //if not same size, definitely not equal
        if (listSize != other.listSize) {
            return false;
        }
        auto otherItr = other.begin();
        //loop through each node and compare their data value
        for (auto thisItr = this->begin(); thisItr != this->end(); ++thisItr) {
            if (*thisItr != *otherItr) {
                return false;
            }
            ++otherItr;
        }
        return true;
    }
      
    //not equal
    bool operator!=(const dlist &other) const{
        return !(*this == other);
    }
      
    //return if this list is smaller
    bool operator<(const dlist &other) const{
        //smaller size will be considered less than
        if (this->listSize < other.listSize) {
            return true;
        } else if (this->listSize == other.listSize) {
            auto thisItr = this->begin();
            auto otherItr = other.begin();
            //iterating through both list to compare the data in each nodes
            while (thisItr != this->end() && otherItr != other.end()) {
                if (*thisItr < *otherItr) {
                    return true;
                } else if (*otherItr < *thisItr) {
                    return false;
                }
                ++thisItr;
                ++otherItr;
            }
        }
        else {
            return false;
        }
        return false;
    }
     
    //lesser and equal to
    bool operator<=(const dlist &other) const{
        return (*this < other) || (*this == other);
    }
      
    //greater to
    bool operator>(const dlist &other) const{
        return !(*this <= other);
    }
      
    //greater and equal to
    bool operator>=(const dlist &other) const{
        return !(*this < other);
    }
        
    // Iterators
    //return iterator at the first node after head node
    iterator begin() {
        return iterator(head->next);
    }
        
    //constant first node iterator
    const iterator begin() const{
        return iterator(head->next);
    }
      
    //return iterator at tail node
    iterator end() {
        return iterator(tail);
    }
    
    //constant tail iterator
    const iterator end() const{
        return iterator(tail);
    }
};

}

#endif /* dlist_h */
