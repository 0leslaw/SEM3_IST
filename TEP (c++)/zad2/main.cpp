#include <iostream>
#include "CNumber.h"


int main() {
    CNumber number1, number2;
    number1 = 368;
    std::cout << number1.toString();
    number2 = 1567;
    number1 = number1 + number2;
    std::cout << number1.toString() << std::endl;

    return 0;
}
