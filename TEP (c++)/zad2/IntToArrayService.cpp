//
// Created by LEGION on 21.10.2023.
//

#include <iostream>
#include <complex>
#include "IntToArrayService.h"

    int IntToArrayService::findIntLength(int value) {

        value = std::abs(value);

        int length = 1;
        int magnitude = 10;

        while (magnitude < value){
            magnitude*=10;
            length++;
        }
        return length;
    }


    int *IntToArrayService::makeArrayFromNumber(int value, int length) {

        value = std::abs(value);
        if(length == 0)
            return 0;

        int *arrPointer = new int[length];

        int magnitude = 10;
        int last = value % magnitude;
        arrPointer[0] = last;

        for (int i = 1; i<length; i++) {
            arrPointer[i] = ((value % (magnitude*10)) - last) / magnitude;
            magnitude*=10;
            last = value % magnitude;
        }
        return arrPointer;
    }

    int *IntToArrayService::cutArrayStartingAtLastIndex(int *&toBeCut, int desiredLength) {
        int* cut = new int[desiredLength];
        for (int i = 0; i < desiredLength; i++) {
            cut[i] = toBeCut[i];
        }
        delete[] toBeCut;
        toBeCut = cut;
        return toBeCut;
    }
