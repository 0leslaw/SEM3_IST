//
// Created by Hyperbook on 13.11.2023.
//

#ifndef ZAD3_V2_ARRAYLIST_H
#define ZAD3_V2_ARRAYLIST_H

template <class T>
class ArrayList {
private:
    T* array;
    int arrayLength;
    int elemCount;
public:
    ArrayList(){
        arrayLength = 10;
        array = new T[arrayLength];
        elemCount = 0;
    }
    ~ArrayList();
    void add(T& element){
        elemCount++;
        if (elemCount > arrayLength) {
            arrayLength *= 2;
            T *tempArray = new T[arrayLength];
            for (int i = 0; i < elemCount; i++)
                tempArray[i] = array[i];
            delete[] array;
            array = tempArray;
        }
        array[elemCount-1] = &element;
    }
    T* get(int index){
        if (index < 0 || index >= elemCount)
            std::cout << "POZA ZAKRESEM";

        return array[index];
    }
    int getElemCount(){
        return elemCount;

    }

};



#endif //ZAD3_V2_ARRAYLIST_H
