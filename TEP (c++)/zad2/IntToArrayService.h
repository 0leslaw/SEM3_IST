//
// Created by LEGION on 21.10.2023.
//

#ifndef ZAD2_INTTOARRAYSERVICE_H
#define ZAD2_INTTOARRAYSERVICE_H


#include "CNumber.h"

class IntToArrayService {
public:
    static int findIntLength(int value);
    static int* makeArrayFromNumber(int value, int length);
    static int* cutArrayStartingAtLastIndex(int*& toBeCut, int desiredLength);
//    static bool determinePositive(CNumber& number1, CNumber& number2);
};


#endif //ZAD2_INTTOARRAYSERVICE_H
