//
// Created by Hyperbook on 13.11.2023.
//

#ifndef ZAD3_V2_ARRAYLIST_H
#define ZAD3_V2_ARRAYLIST_H

template <class T>
class ArrayList {
private:
    T** array;
    int arrayLength;
    int elemCount;
    void clear() {
        for (int i = 0; i < arrayLength; i++)
            delete array[i];

        arrayLength = 0;
    }
public:
    ArrayList(){
        arrayLength = 2;
        array = new T*[arrayLength];
        elemCount = 0;
    }
    ArrayList(ArrayList<T> &other){
        arrayLength = other.getArrayLength();
        array = new T*[arrayLength];
        elemCount = other.getElemCount();
        for (int i = 0; i < elemCount; i++)
            array[i] = new T(*other.getArray().get(i));
    }
    ~ArrayList(){
        clear();
        delete[] array;
    }
    void add(T& element){
        elemCount++;
        if (elemCount > arrayLength) {
            arrayLength *= 2;
            T **tempArray = new T*[arrayLength];
            for (int i = 0; i < elemCount; i++)
                tempArray[i] = array[i];

            clear();
            delete[] array;
            array = tempArray;
        }
        array[elemCount-1] = &element;
    }

    T* get(int index){
        if (index < 0 || index >= elemCount) {
            std::cout << "POZA ZAKRESEM";
            std::string* exception = new std::string(" ");
            exception[INT_MAX];
        }
        return array[index];
    }
    int getElemCount(){
        return elemCount;
    }
    void printStrings(){
        for (int i = 0; i < elemCount; i++) {
            std::cout<<*array[i]+" ";
        }
        std::cout << std::endl;
    }

    T **getArray() const {
        return array;
    }

    int getArrayLength() const {
        return arrayLength;
    }
};



#endif //ZAD3_V2_ARRAYLIST_H
