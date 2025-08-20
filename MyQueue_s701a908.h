#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include <iostream>
#include <algorithm>

#include "MyVector_s701a908.h"

template <typename DataType>
class MyQueue : private MyVector<DataType>
{  
  private:
    size_t dataStart, dataEnd;

    // changes the size of the array to newSize
    void resize(size_t newSize)     //
    {
        // code begins
        MyVector<DataType>::resize(newSize);
        // code ends
    }

    // requests for newCapacity amount of space
    void reserve(size_t newCapacity)    //
    {
        // code begins
        if(newCapacity < this->theCapacity){
            return;
        }

        DataType* tmp = new DataType[newCapacity];
        for(size_t i = 0; i < this->theSize; ++i){
            tmp[i] = std::move(this->data[(i + dataStart) % this->theCapacity]);

        }

        std::swap(this->data, tmp);
        this->theCapacity = newCapacity;
        delete[] tmp;
        
        dataStart = 0;
        dataEnd = this->theSize - 1;
        // code ends
    }

  public:

    // default constructor
    explicit MyQueue(size_t initSize = 0) :     //
        MyVector<DataType>(initSize),
        dataStart(0),
        dataEnd(initSize)


    {
        // code begins
    
        // code ends
    }

    // copy constructor
    MyQueue(const MyQueue & rhs) :      //
        MyVector<DataType>(rhs),
        dataStart(rhs.dataStart),
        dataEnd(rhs.dataEnd)
    {
        // code begins

        // code ends
    }

    // move constructor
    MyQueue(MyQueue && rhs) :       //
        MyVector<DataType>(std::move(rhs)),
        dataStart(rhs.dataStart),
        dataEnd(rhs.dataEnd)
    {
        // code begins
        rhs.dataStart = 0;
        rhs.dataEnd = 0;

        // code ends
    }

    // destructor
    ~MyQueue()      //
    {
        // code begins
        ;
        // code ends
    }

    // copy assignment
    MyQueue & operator= (const MyQueue & rhs)   //
    {
        // code begins
        if(this != &rhs){
            MyVector<DataType>::operator=(rhs);
            dataStart = rhs.dataStart;
            dataEnd = rhs.dataEnd;
        }

        return *this;
        // code ends
    }

    // move assignment
    MyQueue & operator= (MyQueue && rhs)    // 
    {
        // code begins
        if(this != &rhs){
            MyVector<DataType>::operator=(std::move(rhs));
            
            dataStart = rhs.dataStart;
            dataEnd = rhs.dataEnd;

            rhs.dataStart = 0;
            rhs.dataEnd = 0;
        }

        return *this;
        // code ends
    }

    // insert x into the queue
    void enqueue(const DataType & x)    //  
    {
        // code begins
        if(this->theSize + 1 == this->theCapacity){
            reserve(this->theCapacity * 2);
        }

        this->data[dataEnd] = x;
        ++dataEnd;
        dataEnd = dataEnd % this->theCapacity;
        
        ++this->theSize;

        // code ends
    }

    // insert x into the queue
    void enqueue(DataType && x)     //
    {
        // code begins
        if(this->theSize + 1 == this->theCapacity){
            reserve(this->theCapacity * 2);
        }

        this->data[dataEnd] = std::move(x);
        ++dataEnd;
        dataEnd = dataEnd % this->theCapacity;
        
        ++this->theSize;

        // code ends
    }

    // remove the first element from the queue
    void dequeue(void)      //    
    {
        // code begins
        ++dataStart;
        dataStart = dataStart % this->theCapacity;

        --this->theSize;
        // code ends
    }

    // access the first element of the queue
    const DataType & front(void) const      //
    {
        // code begins
        return this->data[dataStart];
        // code ends
    }

    // check if the queue is empty; return TRUE if empty; FALSE otherwise
    bool empty(void) const      //
    {
        // code begins
        return size() == 0;
        // code ends
    }

    // access the size of the queue
    size_t size() const     //
    {
        // code begins
        return (dataEnd - dataStart + this->theCapacity) % this->theCapacity;
        // code ends
    }

    // access the capacity of the queue
    size_t capacity(void) const     //
    {
        // code begins
        return this->theCapacity;
        // code ends
    }

};


#endif // __MYQUEUE_H__