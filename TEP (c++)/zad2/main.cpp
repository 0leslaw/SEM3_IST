#include <iostream>
#include "CNumber.h"
#include <cstdlib>
bool testCNumber(){
    int num1,num2;

    bool isCorrect = true;
    for (int i = 0; i < 100000; i++) {
        num1 = -(rand() % 200000000);
        num2 = (rand() % 200000000+1);
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
            std::cout << "zanotowano blad moj panie! </>" << num1 << " / " << num2 << " = " <<
            num1/num2 << "\na jest" << (CNum1/CNum2).toString() << std::endl;
        }
    }

    return isCorrect;
}

int main() {
    CNumber number1, number2;
    number1 = 20376;
    std::cout << number1.toString();
    number2 = 3;
    number1 = number1 / number2;
    std::cout << number1.toString() << std::endl;
    std::cout << testCNumber()<<std::endl;

    return 0;
}
