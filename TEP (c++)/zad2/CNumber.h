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


        //constructor helpers
        static int findIntLength(int value);

        static int* makeArrayFromNumber(int value, int length);
        //operator helpers
        static int findFirstNonZeroIndex(int*& toBeCut, int length);

        static void cutArrayStartingAtLastIndex(int*& toBeCut, int desiredLength);

        CNumber addHelper(const CNumber& other, bool isPositive);

        CNumber subtractHelper(const CNumber& other, bool isPositive);

        static void zeroOut(int*& array, int length);

        static void MULTIPLICATION_sumTables(int* thisT, int tLength, int* other, int oLength);

        static bool isBiggerEqualThanArray(int *thisT, int firstIndex, int lastIndex, int *other, int oLength);

        static void DIVISION_subTables(int *&thisT, int firstIndex, int* lastIndex, int *other, int oLength);

    public:

        CNumber();

        CNumber(int value);

        CNumber(int *&digitsArray, int arrayLength, bool isPositive);

        CNumber(const CNumber& other);

        ~CNumber();

        CNumber& operator=(const int value);

        CNumber& operator=(const CNumber& other);

        CNumber operator+(CNumber other);

        CNumber operator-(CNumber other);

        CNumber operator*(const CNumber& other);

        CNumber operator/(const CNumber& other);

        bool isAbsoluteBiggerEqualThan(const CNumber& other);

        bool isAbsoluteEqual(const CNumber& other);

        static int changeToNumberIfFitsInt(CNumber other);


        std::string toString();

        int *getDigitsArray() const;

        int getArrayLength() const;

        void setDigitsArray(int *digitsArray);

        void setArrayLength(int arrayLength);

        bool getIsPositive() const;

        void setIsPositive(bool isPositive);


};


#endif //ZAD2_CNUMBER_H
