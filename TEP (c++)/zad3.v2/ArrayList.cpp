//
// Created by Hyperbook on 13.11.2023.
//

#include <iostream>
#include "ArrayList.h"



template<class T>
ArrayList<T>::~ArrayList() {
    delete[] array;
}



template<class T>
T* ArrayList<T>::get(int index) {
    if (index < 0 || index >= elemCount)
       std::cout << "POZA ZAKRESEM";

    return array[index];
}

template<class T>
int ArrayList<T>::getElemCount() {
    return elemCount;
}
