//
// Created by Hyperbook on 18.12.2023.
//

#ifndef ZAD3_V2_MYSMARTPOINTER_H
#define ZAD3_V2_MYSMARTPOINTER_H

#include <cstddef>

template <class T>
class MySmartPointer {
public:
    MySmartPointer(T* objPointer){
        pointer = objPointer;
    }
    //for a smart pointer to work we need a counter which will keep track of pointers connected to one obj
    MySmartPointer(const MySmartPointer<T>& other){
        counter = other.counter;
        pointer = other.pointer;
        counter.inc();
    }
    MySmartPointer(MySmartPointer<T>&& other){
        pointer = other.pointer;
        counter = other.counter;
        other.counter = NULL;
        other.pointer = NULL;
    }
    ~MySmartPointer(){
        removeThisPointer();
    }
    MySmartPointer<T>& operator=(const MySmartPointer<T>& other){
        removeThisPointer();
        this = MySmartPointer<T>(other);
        return *this;
    }
    T& operator*(){return *pointer;};
    T* operator->(){return pointer;};

    bool removeThisPointer(){
        if(counter.dec() == 0){
            delete counter;
            delete pointer;
            return true;
        }else
            return false;

    }

private:
    //this is the implementation of counter class mentioned above
    class Counter{
    public:
        Counter(){
            count = 1;
        }
        int inc(){
            return count++;
        }
        int dec(){
            return count--;
        }
        int get(){
            return count;
        }
    private:
        int count;
    };
    Counter counter;
    T* pointer;
};
#endif //ZAD3_V2_MYSMARTPOINTER_H