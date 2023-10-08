#include <iostream>

void v_alloc_table_fill_34(int iSize){
    if (iSize < 0)  return;

    int *array = new int[iSize];
    for (int i = 0; i < iSize; ++i)
        array[i] = 34;

    for (int i = 0; i < iSize; ++i)
        std::cout << array[i] << ", ";

    std::cout << std::endl;
    delete[] array;
}
bool b_alloc_table_2_dim(int **piTable, int iSizeX, int iSizeY){
    piTable = new int*[iSizeX];
    for (int i = 0; i < iSizeX; ++i) {
        piTable[i] = new int[iSizeY];
    }
    return false;
}














void vSet5(int iVal) {iVal = 5;}
void vSet5(int *piVal) {*piVal = 5;}

int main() {
    v_alloc_table_fill_34(3);
    std::cout << "Hello, World!" << std::endl;
    int number = 2;
    int *pointer,**pointer_to_pointer;
    pointer = &number;
    pointer_to_pointer = &pointer;

    std::cout << **pointer_to_pointer << std::endl;

    //making a 2D table
    int t_size = 4;
    int **table = new int*[t_size];
    for (int i = 0; i < t_size; ++i) {
        *(table+i) = new int[3];
        for (int j = 0; j < 3; ++j)
            table[i][j] = 1;
    }
    for (int i = 0; i < t_size; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << table[i][j];
        }
        std:: cout << " "<< std::endl;
    }
    for (int i = 0; i < t_size; ++i) {
        delete[] table[i];
    }
    delete[] table;
    //static alocated adress
    int num;
    *(&num) = 5;

    int i_want_to_be_5;
    int i_will_be_5;
    vSet5(i_want_to_be_5);
    vSet5(&i_will_be_5);
    std::cout << i_want_to_be_5 << " "<< i_will_be_5<< std::endl;
    return 0;

}
