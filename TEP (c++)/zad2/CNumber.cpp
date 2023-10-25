//
// Created by LEGION on 21.10.2023.
//

#include "CNumber.h"
#include <cstdio>
#include <valarray>
#include <iostream>
#include <complex>

CNumber::CNumber() {
    arrayLength = 0;
    digitsArray = 0;
    isPositive = false;
}

CNumber::CNumber(int value) {
    arrayLength = findIntLength(value);
    digitsArray = makeArrayFromNumber(value,arrayLength);
    value > 0 ?
    isPositive = true : isPositive = false;
}

CNumber::CNumber(int *&digitsArray, int arrayLength, bool isPositive) : digitsArray(digitsArray),
arrayLength(arrayLength),
isPositive(isPositive) {}

CNumber::~CNumber() {
//       delete[] digitsArray;
}

CNumber& CNumber::operator=(const int value) {

    delete[] digitsArray;
    arrayLength = findIntLength(value);
    digitsArray = makeArrayFromNumber(value,arrayLength);
    value > 0 ? isPositive = true : isPositive = false;
    return *this;
}

CNumber& CNumber::operator=(const CNumber &other) {
    if (this == &other)
        return *this;

    delete[] digitsArray;
    arrayLength = other.getArrayLength();
    digitsArray = other.getDigitsArray();
    isPositive = other.getIsPositive();
    return *this;
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
    bool isThisBigger = isBiggerThan(other);
    if(isPositive && other.getIsPositive())
        return addHelper(other,true);
    else if(isPositive && !other.getIsPositive()){
        if(isThisBigger)
            return subtractHelper(other, true);
        else
            return other.subtractHelper(*this, false);
    }
        
    else if(!isPositive && other.getIsPositive()) {
        if(isThisBigger)
            return subtractHelper(other, false);
        else
            return other.subtractHelper(*this, true);
    }
    else
        return addHelper(other, false);
}

CNumber CNumber::operator-(CNumber other) {
    //determine is positive
    bool isThisBigger = isBiggerThan(other);
    if(isPositive && other.getIsPositive()){
        if(isThisBigger)
            return subtractHelper(other, true);
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
    (this->arrayLength == other.getArrayLength() &&
            this->digitsArray[this->arrayLength-1]>other.getDigitsArray()[other.getArrayLength()-1]))
        return true;

    else
        return false;
}

bool CNumber::isBiggerThanArray(int *thisT,int firstIndex, int lastIndex, int *other, int oLength) {
    if(lastIndex+1-firstIndex > oLength ||
       (lastIndex+1-firstIndex == oLength &&
        thisT[firstIndex]>other[oLength-1]))
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
                cutArrayStartingAtLastIndex(tempSumTable,--newLength);
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
                tempDifferenceTable[i]+=10;
            }
                
            else
                carry = 0;
        }
        else if(this->arrayLength - 1 >= (i)) {// else if max index of this array is bigger/equal than current then:
            tempDifferenceTable[i] = this->digitsArray[i] - carry;
            if (this->digitsArray[i] - carry < 0) {
                carry = 1;
                tempDifferenceTable[i]+=10;
            }else
                carry = 0;
        }
        else if(other.getArrayLength() - 1 >= i) {
            tempDifferenceTable[i] = other.getDigitsArray()[i] - carry;
            if (other.getDigitsArray()[i] - carry < 0) {
                carry = 1;
                tempDifferenceTable[i] += 10;
            }else
                carry = 0;
        }

    }
    //adjusting array
    newLength = newLength - findIndexOfLastZero(tempDifferenceTable, newLength) - 1;
    cutArrayStartingAtLastIndex(tempDifferenceTable, newLength);
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

CNumber CNumber::operator*(const CNumber &other) {
    int newLength = other.getArrayLength()+ arrayLength;
    int* MultTable = new int[newLength];
    int tempMultLength = arrayLength+1;
    int* tempMult = new int[tempMultLength];
    zeroOut(MultTable, tempMultLength);

    int carry = 0;

    for (int i = 0; i < other.getArrayLength(); i++) {
        for (int j = 0; j < arrayLength; ++j) {
            tempMult[j+i] = (other.getDigitsArray()[i] * digitsArray[j] + carry) % 10;
            carry = (other.getDigitsArray()[i] * digitsArray[j]) / 10;
        }
        tempMult[i+arrayLength] = carry;
        MultTable = sumTables(MultTable,newLength,tempMult,tempMultLength);
        delete[] tempMult;
        tempMult = new int[tempMultLength++];
    }
    if (isPositive && !other.getIsPositive() || !isPositive && other.getIsPositive())
        return CNumber(MultTable, newLength, false);
    else
        return CNumber(MultTable, newLength, true);
}

CNumber CNumber::operator/(const CNumber &other) {
    if(other.getArrayLength() > arrayLength)
        return CNumber(0);

    int newLength = arrayLength - other.getArrayLength() + 1;
    int* division = new int[newLength];
    zeroOut(division,newLength);
    int* tempDivision = new int[newLength];
    zeroOut(tempDivision,newLength);
    int lastCounted = 0;
    int subDivisionDigit = 0;

    for (int i = 0; i < 0; i++) {
        if (isBiggerThanArray(other.getDigitsArray(),
                              lastCounted, i ,
                              tempDivision, newLength)){
            tempDivision[i] = digitsArray[i];
            division[i] = 0;
        }else{

            while (isBiggerThanArray(other.getDigitsArray(),
                                     lastCounted, i ,
                                     tempDivision, newLength)){
                tempDivision = subTables(tempDivision,lastCounted,i,
                                         other.getDigitsArray(),other.getArrayLength());
                subDivisionDigit++;
            }
            if (tempDivision[i] == 0)
                lastCounted = i+1;
            else{
                lastCounted = i;        //make sure the next subdivision is starting at correct index
                while (tempDivision[lastCounted] != 0)
                    lastCounted--;
            }
            division[i] = subDivisionDigit;
            subDivisionDigit = 0;
        }
    }
    if (isPositive && !other.getIsPositive() || !isPositive && other.getIsPositive())
        return CNumber(division, newLength, false);
    else
        return CNumber(division, newLength, true);
}

int CNumber::changeToNumber(const CNumber &other) {
    int number = 0;
    int magnitude = 1;
    for (int i = 0; i < other.getArrayLength(); i++) {
        number += other.getDigitsArray()[i]*magnitude;
        magnitude *= 10;
    }
    return number;
}


int CNumber::findIntLength(int value) {

    value = std::abs(value);

    int length = 1;
    int magnitude = 10;

    while (magnitude < value){
        magnitude*=10;
        length++;
    }
    return length;
}

int *CNumber::makeArrayFromNumber(int value, int length) {

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

int *CNumber::cutArrayStartingAtLastIndex(int *&toBeCut, int desiredLength) {
    int* cut = new int[desiredLength];
    for (int i = 0; i < desiredLength; i++) {
        cut[i] = toBeCut[i];
    }
    delete[] toBeCut;
    toBeCut = cut;
    return toBeCut;
}

// getters & setters
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

int* CNumber::sumTables(int* thisT,int tLength, int* other,int oLength) {
    int newLength = std::max(oLength, tLength)+1;
    int* tempSumTable = new int[newLength];
    int carry = 0;
    for (int i = 0; i < newLength; i++) {
        if (tLength - 1 >= i && oLength-1 >= i){// if max index of this array and max index of other array is bigger/equal than current then:
            int val = (thisT[i] + other[i] + carry) % 10;
            tempSumTable[i] = val;
            if (thisT[i] + other[i] + carry > 9)
                carry = 1;
            else
                carry = 0;
        }
        else if(tLength - 1 >= (i)) {// else if max index of this array is bigger/equal than current then:
            tempSumTable[i] = (thisT[i] + carry) % 10;
            if (thisT[i] + carry > 9)
                carry = 1;
            else
                carry = 0;
        }
        else if(oLength - 1 >= i) {
            int val = (other[i] + carry) % 10;
            tempSumTable[i] = val;
            if (other[i] + carry > 9)
                carry = 1;
            else
                carry = 0;
        }
            //last index
        else{
            if (carry == 1)
                tempSumTable[i] = carry;
            else{
                cutArrayStartingAtLastIndex(tempSumTable,--newLength);
            }
        }
    }
    return tempSumTable;
}

int* CNumber::subTables(int* thisT,int firstIndex,int lastIndex ,int* other,int oLength){
    int thisTLength = lastIndex - firstIndex + 1;
    int newLength = std::max(oLength, thisTLength);
    int* tempDifferenceTable = new int[newLength];


    int carry = 0;
    for (int i = 0; i < newLength; i++) {
        if (thisTLength - 1 >= i && oLength -1 >= i){// if max index of this array and max index of other array is bigger/equal than current then:
            tempDifferenceTable[i] = thisT[i] - other[i] - carry;
            if (thisT[i] - other[i] - carry < 0){
                carry = 1;
                tempDifferenceTable[i]+=10;
            }

            else
                carry = 0;
        }
        else if(thisTLength - 1 >= (i)) {// else if max index of this array is bigger/equal than current then:
            tempDifferenceTable[i] = thisT[i] - carry;
            if (thisT[i] - carry < 0) {
                carry = 1;
                tempDifferenceTable[i] += 10;
            }else
                carry = 0;
        }
        else if(oLength - 1 >= i) {
            tempDifferenceTable[i] = other[i] - carry;
            if (other[i] - carry < 0) {
                carry = 1;
                tempDifferenceTable[i] += 10;
            }else
                carry = 0;
        }

    }

    return tempDifferenceTable;
}

void CNumber::zeroOut(int *&array, int length) {
    for (int i = 0; i < length; i++) {
        array[i] = 0;
    }
}





