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
    value >= 0 ?
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

CNumber CNumber::operator+(CNumber other) {
    //determine is positive
    bool isThisBigger = isAbsoluteBiggerEqualThan(other);
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
    bool isThisBigger = isAbsoluteBiggerEqualThan(other);
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

bool CNumber::isAbsoluteBiggerEqualThan(const CNumber &other) {
    if(this->arrayLength > other.getArrayLength() ||
    (this->arrayLength == other.getArrayLength() &&
            this->digitsArray[this->arrayLength-1]>=other.getDigitsArray()[other.getArrayLength()-1]))
        return true;

    else
        return false;
}

bool CNumber::isBiggerEqualThanArray(int *thisT, int firstIndex, int lastIndex, int *other, int oLength) {
    if(lastIndex+1-firstIndex > oLength ||
       (lastIndex+1-firstIndex == oLength &&
        thisT[lastIndex]>=other[oLength-1]))
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
    zeroOut(tempDifferenceTable,newLength);

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
    newLength = std::max(findFirstNonZeroIndex(tempDifferenceTable,newLength) + 1,1);
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
    if (other.getArrayLength() == 1 && other.getDigitsArray()[0] == 0) {
        std::cout << "division by zero is not allowed!!" << std::endl;
        return CNumber(-1);
    }
    if(other.getArrayLength() > arrayLength)
        return CNumber(0);

    int newLength = arrayLength - other.getArrayLength() + 1;
    int* division = new int[newLength];
    zeroOut(division,newLength);
    int* tempDivision = new int[newLength];
    zeroOut(tempDivision,newLength);
    int* lastCounted = new int;
    *lastCounted = arrayLength - 1;
    int subDivisionDigit = 0;


    for (int i = arrayLength-1; i >= 0; i--) {
        tempDivision[i] = digitsArray[i];

        while (isBiggerEqualThanArray(tempDivision,
                                      i, *lastCounted,
                                      other.getDigitsArray(), other.getArrayLength())) {
            DIVISION_subTables(tempDivision, i, lastCounted,
                               other.getDigitsArray(), other.getArrayLength());
            subDivisionDigit++;

        }
        division[i] = subDivisionDigit;
        subDivisionDigit = 0;
    }
    newLength = std::max(findFirstNonZeroIndex(division,newLength) + 1,1);
    cutArrayStartingAtLastIndex(division, newLength);
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


    while (value/10 > 0){
        value/=10;
        length++;
    }
    return length;
}

int *CNumber::makeArrayFromNumber(int value, int length) {

    value = std::abs(value);
    if(length == 0)
        return 0;

    int *arrPointer = new int[length];
    for (int i = 0; i<length; i++) {
        arrPointer[i] = value % 10;
        value/=10;
    }
    return arrPointer;
}

void CNumber::cutArrayStartingAtLastIndex(int *&toBeCut, int desiredLength) {
    int* cut = new int[desiredLength];
    for (int i = 0; i < desiredLength; i++) {
        cut[i] = toBeCut[i];
    }
    delete[] toBeCut;
    toBeCut = cut;
}
int CNumber::findFirstNonZeroIndex(int *&toBeCut, int length) {
    int i = length-1;
    while (toBeCut[i] == 0)
        i--;
    return i;
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

void CNumber::DIVISION_subTables(int*& thisT, int firstIndex, int* lastIndex , int* other, int oLength){
    int thisTLength = *lastIndex - firstIndex + 1;

    int carry = 0;
    for (int i = 0; i < thisTLength; i++) {
        if (thisTLength - 1 >= i && oLength -1 >= i){// if max index of this array and max index of other array is bigger/equal than current then:
            thisT[i+firstIndex] = thisT[i+firstIndex] - other[i] - carry;
            if (thisT[i+firstIndex] < 0){
                carry = 1;
                thisT[i+firstIndex]+=10;
            }

            else
                carry = 0;
        }
        else if(thisTLength - 1 >= (i)) {// else if max index of this array is bigger/equal than current then:
            thisT[i+firstIndex] = thisT[i+firstIndex] - carry;
            if (thisT[i+firstIndex] < 0) {
                carry = 1;
                thisT[i+firstIndex] += 10;
            }else
                carry = 0;
        }
        else if(oLength - 1 >= i) {
            thisT[i+firstIndex] = other[i] - carry;
            if (other[i] - carry < 0) {
                carry = 1;
                thisT[i+firstIndex] += 10;
            }else
                carry = 0;
        }
    }
    while (thisT[*lastIndex] == 0)
        *lastIndex = *lastIndex - 1;
}

void CNumber::zeroOut(int *&array, int length) {
    for (int i = 0; i < length; i++) {
        array[i] = 0;
    }
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





