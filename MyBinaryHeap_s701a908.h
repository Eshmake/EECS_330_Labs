#ifndef __MYBINARYHEAP_H__
#define __MYBINARYHEAP_H__

#include <iostream>
#include <cstdlib>

#include "MyVector_s701a908.h"

// ComparableType should be comparable (<, >, ==, >=, <= operators implemented)
// ComparableType should also have +, +=, -, -= operators implemented to support priority adjustment

template <typename ComparableType>
class MyBinaryHeap 
{
  private:
	MyVector<ComparableType> data;  // the array that holds the data elements

    // moves the data element at the pth position of the array up
    void percolateUp(const size_t p)    //
    {
        // code begins
        if(p > data.size()-1) throw std::out_of_range("percolateUp");
        
        data[0] = std::move(data[p]);
        
        size_t hole = p;

        for(; data[0] > data[hole/2]; hole /= 2){
            data[hole] = std::move(data[hole/2]);
        }

        data[hole] = std::move(data[0]);

        // code ends
    }

    // moves the data element at the pth position of the array down
    void percolateDown(const size_t p)  //
    {
        // code begins
        if(p > data.size()-1) throw std::out_of_range("percolateDown");

        size_t hole = p, child;
        data[0] = std::move(data[p]);

        for(; hole * 2 <= data.size()-1; hole = child){
            child = hole * 2;
            
            if(child < data.size()-1 && data[child+1] > data[child]) ++child;

            if(data[0] < data[child]) data[hole] = std::move(data[child]);
            else break;

        }

        data[hole] = std::move(data[0]);


        // code ends
    }

    // reorders the data elements in the array to ensure heap property
    void buildHeap()    //
    {
        // code begins
        for(size_t i = (data.size()-1) / 2; i > 0; --i){
            percolateDown(i);
        }

        // code ends
    }	

  public: 

    // default constructor
    explicit MyBinaryHeap() :       //
        data(1)     // reserve data[0]
    {
        // code begins


        // code ends
    }

    // constructor from a set of data elements
    MyBinaryHeap(const MyVector<ComparableType>& items) :   //
        data(1)     // reserve data[0]
    {
        // code begins
        for(size_t i = 0; i < items.size(); i++){
            data.push_back(items[i]);
        }

        buildHeap();

        // code ends
    }

    // copy constructor
    MyBinaryHeap(const MyBinaryHeap<ComparableType>& rhs) :     //
        data(rhs.data)
    {
        // code begins


        // code ends
    }

    // move constructor
    MyBinaryHeap(MyBinaryHeap<ComparableType> && rhs) :     //
        data(std::move(rhs.data))
    {
        // code begins

        // code ends
    }

    // copy assignment
    MyBinaryHeap& operator=(const MyBinaryHeap<ComparableType>& rhs)    // 
    {
        // code begins

        if(this != &rhs){
            data = rhs.data;
        }

        return *this;

        // code ends
    }

    // move assignment
    MyBinaryHeap& operator=(MyBinaryHeap<ComparableType> && rhs)       //
    {
        // code begins

        if(this != &rhs){
            data = std::move(rhs.data);
        }

        return *this;

        // code ends
    }

    // inserts x into the priority queue (copy)
	void enqueue(const ComparableType& x)   //
    {
        // code begins
        data.push_back(x);
        percolateUp(data.size()-1);

        // code ends
    } 

    // inserts x into the priority queue (move)
    void enqueue(ComparableType && x)   //
    {
        // code begins
        data.push_back(std::move(x));
        percolateUp(data.size()-1);

        // code ends
    }

    // accesses the data element with the highest priority
	const ComparableType& front()   //
    {
        // code begins
        return data[1];

        // code ends
    } 

    // deletes the data element with the highest priority from the queue
    void dequeue()  //
    {
        // code begins
        if(empty()) throw std::out_of_range("dequeue");

        data[1] = data[data.size()-1];
        data.pop_back();

        if(!empty()) percolateDown(1);

        // code ends
    }

    // verifies whether the array satisfies the heap property
    bool verifyHeapProperty(void)       //
    {
        // code begins

        for(size_t i = 1; i <= (data.size()-1)/2; i++){
            size_t lc = i * 2;
            size_t rc = i * 2 + 1;

            if(lc < data.size() && data[i] < data[lc]) return false;
            if(rc < data.size() && data[i] < data[rc]) return false;
        }

        return true;

        // code ends
    }

    // disrupts heap property by random shuffling
    void disruptHeapProperty(void)
    {
        if(data.size() <= 3)
            return;
        for(size_t i = 0; i < 1000; ++ i)
        {
            size_t p = 1 + ((int) rand()) % (data.size() - 1);
            size_t q = 1 + ((int) rand()) % (data.size() - 1);
            std::swap(data[p], data[q]);
        }
        return;
    }

    // merges two heaps; the second heap can be destructed after the merge
    MyBinaryHeap& merge(MyBinaryHeap<ComparableType> && rhs)    //
    {
        // code begins

        for(size_t i = 1; i < rhs.data.size(); i++){
            data.push_back(std::move(rhs.data[i]));
        }

        buildHeap();

        rhs.clear();

        return *this;

        

        // code ends
    }

    // increases the priority measure of an element at a specific position and reorder the heap
	void increaseKey(const size_t p, const unsigned int d)  //
    {    
        // code begins
        if(p > data.size()-1) throw std::out_of_range("increaseKey");

        data[p] += d;

        percolateUp(p);

        // code ends
    }

    // decreases the priority measure of an element at a specific position and reorder the heap
    // if the current priority is smaller than the requested decrement, assign priority 0
	void decreaseKey(const size_t p, const unsigned int d)  //
    {
        // code begins
        if(p > data.size()-1) throw std::out_of_range("decreaseKey");

        if(data[p] > d) data[p] -= d;
        else data[p] = 0;

        percolateDown(p);

        // code ends   
    }

    // checks whether the heap is empty
    bool empty()    //
    {
        // code begins

        return data.size() <= 1;

        // code ends
    }

    // removes all data elements from the heap
    void clear()    //
    {
        // code begins
        data.resize(1);

        // code ends
    }

    // returns the size of the heap
    size_t size()   //
    {
        // code begins

        return data.size() > 0 ? data.size()-1 : 0;

        // code ends
    }

    // prints the data in the array
    void print() 
    {
        const char delim = '\t';
        for (size_t i = 1; i < data.size(); ++ i) {
            std::cout << data[i] << delim;
        }
        std::cout << std::endl;
        return;
    }

};

#endif // __MYBINARYHEAP_H__