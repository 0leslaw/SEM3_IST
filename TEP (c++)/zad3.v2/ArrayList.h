//
// Created by Hyperbook on 13.11.2023.
//

//BASIC ARRAYLIST IMPLEMENTATION
#ifndef ZAD3_V2_ARRAYLIST_H
#define ZAD3_V2_ARRAYLIST_H
#include <iostream>
template <class T>
class ArrayList {
private:
    T** array;
    int arrayLength;
    int elemCount;
    void clear() {
        for (int i = 0; i < elemCount; i++) {
            delete array[i];
            array[i] = NULL;
        }
        arrayLength = 0;
    }
public:
    ArrayList(){
        arrayLength = 0;
        array = NULL;
        elemCount = 0;
    }
    ArrayList(const ArrayList<T> &other){
        elemCount = other.getElemCount();
        if (arrayLength == 0){
            array = NULL;
        }
        else {
            arrayLength = other.getArrayLength();
            array = new T *[arrayLength];
            for (int i = 0; i < elemCount; i++)
                array[i] = new T(*other.getArray()[i]);
        }
    }
    ~ArrayList(){
        if(arrayLength != 0) {
            clear();
            delete[] array;
        }
    }
    void add(T& element){
        elemCount++;
        if (elemCount > arrayLength) {
            arrayLength++;
            arrayLength *= 2;
            T **tempArray = new T*[arrayLength];
            if (array != NULL) {
                for (int i = 0; i < elemCount-1; i++)
                    tempArray[i] = array[i];
                delete[] array;
            }
            array = tempArray;
        }
        array[elemCount-1] = &element;
    }
    void setAt(int index, T& element){
        delete array[index];
        array[index] = &element;
    }
    bool contains(T& element){
        for (int i = 0; i < elemCount; i++)
            if (*array[i] == element)
                return true;
        return false;
    }
    int findFirstIndexOf(T& element){
        for (int i = 0; i < elemCount; i++)
            if (*array[i] == &elemCount)
                return i;
        return -1;
    }
    T* get(int index) const{
        if (index < 0 || index >= elemCount) {
            std::cout << "POZA ZAKRESEM";
            std::string* exception = new std::string(" ");
            exception[INT_MAX];
        }
        return array[index];
    }
    int getElemCount() const{
        return elemCount;
    }

    T **getArray() const {
        return array;
    }

    int getArrayLength() const {
        return arrayLength;
    }

};



#endif //ZAD3_V2_ARRAYLIST_H
