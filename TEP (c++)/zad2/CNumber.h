//
// Created by LEGION on 21.10.2023.
//

#ifndef ZAD2_CNUMBER_H
#define ZAD2_CNUMBER_H
#include <iostream>

class CNumber {
    private:
        int* digitsArray;

        int arrayLength;

        bool isPositive;


        static int* cutArrayStartingAtLastIndex(int*& toBeCut, int desiredLength);

        static int findIntLength(int value);

        static int* makeArrayFromNumber(int value, int length);

        CNumber addHelper(const CNumber& other, bool isPositive);

        CNumber subtractHelper(const CNumber& other, bool isPositive);

        int findIndexOfLastZero(const int* array, int length);

        static int changeToNumber(const CNumber& other);
    public:
        CNumber();

        CNumber(int value);

        CNumber(int *&digitsArray, int arrayLength, bool isPositive);

        ~CNumber();

        CNumber& operator=(const int value);

        CNumber& operator=(const CNumber& other);

        CNumber operator+(CNumber other);

        CNumber operator-(CNumber other);

        CNumber operator*(const CNumber& other);

        CNumber operator/(const CNumber& other);

        bool isBiggerThan(const CNumber& other);



        std::string toString();

        int *getDigitsArray() const;

        int getArrayLength() const;

        void setDigitsArray(int *digitsArray);

        void setArrayLength(int arrayLength);

        bool getIsPositive() const;

        void setIsPositive(bool isPositive);

};


#endif //ZAD2_CNUMBER_H
