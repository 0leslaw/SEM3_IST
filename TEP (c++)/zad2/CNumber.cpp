//
// Created by LEGION on 21.10.2023.
//

#include "CNumber.h"
#include "IntToArrayService.h"
#include <cstdio>

CNumber::CNumber() {
        arrayLength = 0;
        digitsArray = 0;
    }

    CNumber::CNumber(int value) {
        arrayLength = IntToArrayService::findIntLength(value);
        digitsArray = IntToArrayService::makeArrayFromNumber(value,arrayLength);
    }

    CNumber::CNumber(int *&digitsArray, int arrayLength, bool isPositive) : digitsArray(digitsArray),
                                                                        arrayLength(arrayLength),
                                                                        isPositive(isPositive) {}

    CNumber::~CNumber() {
//        delete[] digitsArray;
    }

    void CNumber::operator=(const int value) {
        delete[] digitsArray;
        arrayLength = IntToArrayService::findIntLength(value);
        digitsArray = IntToArrayService::makeArrayFromNumber(value,arrayLength);
    }

    void CNumber::operator=(const CNumber &other) {
        delete[] digitsArray;
        arrayLength = other.getArrayLength();
        digitsArray = other.getDigitsArray();
    }

    int *CNumber::getDigitsArray() const {
        return digitsArray;
    }

    int CNumber::getArrayLength() const {
        return arrayLength;
    }

void CNumber::setDigitsArray(int *digitsArray) {
    CNumber::digitsArray = digitsArray;
}

void CNumber::setArrayLength(int arrayLength) {
    CNumber::arrayLength = arrayLength;
}

    bool CNumber::getIsPositive() const {
        return isPositive;
    }

    void CNumber::setIsPositive(bool isPositive) {
        CNumber::isPositive = isPositive;
    }

std::string CNumber::toString() {
            std::string array = "";
            char buffer[20];
            for (int i = 0; i < arrayLength; ++i) {
                std::sprintf(buffer, "%d", digitsArray[arrayLength-1-i]);
                std::string digit = buffer;
                array += digit + " ";
            }

            std::sprintf(buffer, "%d", arrayLength);
            std::string arrayLengthToString = buffer;

            return "THE NUMBER IS: " + array + "\n AND ITS LENGTH IS: " + arrayLengthToString + "\n";
    }

    CNumber CNumber::operator+(const CNumber &other) {

        int newLength = std::max(other.getArrayLength(), this->arrayLength)+1;
        int* tempSumTable = new int[newLength];

        int carry = 0;

        for (int i = 0; i < newLength; i++) {
            if (this->arrayLength - 1 >= i && other.getArrayLength() -1 >= i){// if max index of this array and max index of other array is bigger/equal than current then:
                int val = (this->digitsArray[i] + other.getDigitsArray()[i] + carry) % 10;
                tempSumTable[i] = val;
                if (this->digitsArray[i] + other.getDigitsArray()[i] + carry > 9)
                    carry = 1;
                else
                    carry = 0;

            }
            else if(this->arrayLength - 1 >= (i)) {// else if max index of this array is bigger/equal than current then:
                tempSumTable[i] = (this->digitsArray[i] + carry) % 10;
                if (this->digitsArray[i] + carry > 9)
                    carry = 1;
                else
                    carry = 0;

            }
            else if(other.getArrayLength() - 1 >= i) {
                int val = (other.getDigitsArray()[i] + carry) % 10;
                tempSumTable[i] = val;
                if (other.getDigitsArray()[i] + carry > 9)
                    carry = 1;
                else
                    carry = 0;
            }
            //last index
            else{
                if (carry == 1)
                    tempSumTable[i] = carry;
                else{
                    IntToArrayService::cutArrayStartingAtLastIndex(tempSumTable,--newLength);
                }
            }
        }


        return CNumber(tempSumTable, newLength, true);;
    }

//    CNumber &CNumber::operator-(const CNumber &other) {
//        return <#initializer#>;
//    }
//
//    CNumber &CNumber::operator*(const CNumber &other) {
//        return <#initializer#>;
//    }
//
//    CNumber &CNumber::operator/(const CNumber &other) {
//        return &other;
//    }





