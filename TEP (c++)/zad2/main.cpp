#include <iostream>
#include "CNumber.h"


int main() {
    CNumber number1, number2;
    number1 = 256;
    std::cout << number1.toString();
    number2 = 4;
    number1 = number1 / number2;
    std::cout << number1.toString() << std::endl;

    return 0;
}
