//
// Created by LEGION on 21.10.2023.
//

#include "CNumber.h"
#include "IntToArrayService.h"
#include <cstdio>

CNumber::CNumber() {
    arrayLength = 0;
    digitsArray = 0;
    isPositive = false;
}

CNumber::CNumber(int value) {
    arrayLength = IntToArrayService::findIntLength(value);
    digitsArray = IntToArrayService::makeArrayFromNumber(value,arrayLength);
    value > 0 ?
    isPositive = true : isPositive = false;
}

CNumber::CNumber(int *&digitsArray, int arrayLength, bool isPositive) : digitsArray(digitsArray),
arrayLength(arrayLength),
isPositive(isPositive) {}

CNumber::~CNumber() {
//       delete[] digitsArray;
}

void CNumber::operator=(const int value) {
    delete[] digitsArray;
    arrayLength = IntToArrayService::findIntLength(value);
    digitsArray = IntToArrayService::makeArrayFromNumber(value,arrayLength);
    value > 0 ? isPositive = true : isPositive = false;
}

void CNumber::operator=(const CNumber &other) {
    delete[] digitsArray;
    arrayLength = other.getArrayLength();
    digitsArray = other.getDigitsArray();
    isPositive = other.getIsPositive();
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
    if (!isPositive)
        array += "- ";
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

CNumber CNumber::operator+(CNumber other) {
    //determine is positive
    bool isThisBigger = this->isBiggerThan(other);
    if(this->isPositive && other.isPositive)
        return this->addHelper(other,true);
    else if(this->isPositive && !other.isPositive){
        if(isThisBigger)
            return this->subtractHelper(other, true);
        else
            return other.subtractHelper(*this, false);
    }
        
    else if(!this->isPositive && other.isPositive) {
        if(isThisBigger)
            return this->subtractHelper(other, false);
        else
            return other.subtractHelper(*this, true);
    }
    else
        return this->addHelper(other, false);
}

CNumber CNumber::operator-(CNumber other) {
    //determine is positive
    bool isThisBigger = this->isBiggerThan(other);
    if(this->isPositive && other.isPositive){
        if(isThisBigger)
            return this->subtractHelper(other, true);
        else
            return other.subtractHelper(*this, false);
    }
    else if(this->isPositive && !other.isPositive)
        return this->addHelper(other,true);

    else if(!this->isPositive && other.isPositive)
        return this->addHelper(other, false);

    else{
        if(isThisBigger)
            return this->subtractHelper(other, false);
        else
            return other.subtractHelper(*this, true);
    }
}

bool CNumber::isBiggerThan(const CNumber &other) {
    if(this->arrayLength > other.getArrayLength() ||
    (this->arrayLength = other.getArrayLength() &&
            this->digitsArray[this->arrayLength-1]>other.getDigitsArray()[other.getArrayLength()-1]))
        return true;

    else
        return false;
}

CNumber CNumber::addHelper(const CNumber &other, bool isPositive) {
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
    return CNumber(tempSumTable, newLength, isPositive);
}

CNumber CNumber::subtractHelper(const CNumber &other, bool isPositive) {
    int newLength = std::max(other.getArrayLength(), this->arrayLength);
    int* tempDifferenceTable = new int[newLength];

    int carry = 0;
    for (int i = 0; i < newLength; i++) {
        if (this->arrayLength - 1 >= i && other.getArrayLength() -1 >= i){// if max index of this array and max index of other array is bigger/equal than current then:
            tempDifferenceTable[i] = this->digitsArray[i] - other.getDigitsArray()[i] - carry;
            if (this->digitsArray[i] - other.getDigitsArray()[i] - carry < 0){
                carry = 1;
                this->arrayLength - 1 == i ?
                        tempDifferenceTable[i]+=10 : tempDifferenceTable[i]+=9;
            }
                
            else
                carry = 0;
        }
        else if(this->arrayLength - 1 >= (i)) {// else if max index of this array is bigger/equal than current then:
            tempDifferenceTable[i] = this->digitsArray[i] - carry;
            if (this->digitsArray[i] - carry < 0) {
                carry = 1;
                this->arrayLength - 1 == i ?
                        tempDifferenceTable[i] += 10 : tempDifferenceTable[i] += 9;
            }else
                carry = 0;
        }
        else if(other.getArrayLength() - 1 >= i) {
            tempDifferenceTable[i] = other.getDigitsArray()[i] - carry;
            if (other.getDigitsArray()[i] - carry < 0) {
                carry = 1;
                other.getDigitsArray()[i] - 1 == i ?
                tempDifferenceTable[i] += 10 : tempDifferenceTable[i] += 9;
            }else
                carry = 0;
        }
        //adjusting array
        else{
            if (carry == 1)
                tempDifferenceTable[i] = carry;
            else{
                newLength = newLength - findIndexOfLastZero(tempDifferenceTable, newLength) - 1;
                IntToArrayService::cutArrayStartingAtLastIndex(tempDifferenceTable, newLength);
            }
        }
    }
    return CNumber(tempDifferenceTable, newLength, isPositive);
}

int CNumber::findIndexOfLastZero(const int *array, int length) {
    int index = -1;
    for (int i = length-1; i >= 0; i++) {
        if (array[i] != 0)
            return index;
        index++;
    }
    return index;
}
//
//    CNumber &CNumber::operator*(const CNumber &other) {
//        return <#initializer#>;
//    }
//
//    CNumber &CNumber::operator/(const CNumber &other) {
//        return &other;
//    }





