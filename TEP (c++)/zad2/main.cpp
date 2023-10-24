#include <iostream>
#include "CNumber.h"


int main() {
    CNumber number1, number2;
    number1 = 56;
    std::cout << number1.toString();
    number2 = 21;
    number1 = number1 / number2;
    std::cout << number1.toString() << std::endl;

    return 0;
}
