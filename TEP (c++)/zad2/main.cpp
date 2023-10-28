#include <iostream>
#include "CNumber.h"
#include <cstdlib>
bool testCNumber(){
    int num1,num2;


    bool isCorrect = true;
    for (int i = 0; i < 100; i++) {
        num1 = rand() % 2000000;
        num2 = rand() % 2000000;
        CNumber CNum1 = num1;
        CNumber CNum2 = num2;

        if(num1-num2 != CNumber::changeToNumberIfFitsInt(CNum1-CNum2)) {
            isCorrect = false;
            std::cout << "zanotowano blad moj panie! <->" << std::endl;
        }

        if(num1+num2 != CNumber::changeToNumberIfFitsInt(CNum1+CNum2)) {
            isCorrect = false;
            std::cout << "zanotowano blad moj panie! <+>" << std::endl;
        }

        if(num1*num2 != CNumber::changeToNumberIfFitsInt(CNum1*CNum2)) {
            isCorrect = false;
            std::cout << "zanotowano blad moj panie! <*>" << num1 << " * " << num2 << " = " << (CNum1*CNum2).toString() << std::endl;
        }

        if(num1/num2 != CNumber::changeToNumberIfFitsInt(CNum1/CNum2)) {
            isCorrect = false;
            std::cout << "zanotowano blad moj panie! </>" << std::endl;
        }
    }

    return isCorrect;
}

int main() {
    CNumber number1, number2;
    number1 = 1478;
    std::cout << number1.toString();
    number2 = 1358;
    number1 = number1 * number2;
    std::cout << number1.toString() << testCNumber()<<std::endl;

    return 0;
}
