#include <iostream>
#include <cstdlib>
#include "ConsoleInterface.h"
template <typename T>
void runConsoleInterface() {
    ConsoleInterface<T> consoleInterface;
    consoleInterface.run();
}

int main() {

    string driver;
    cout<< "Wybierz\n1 - int,\n2 - double lub\n3 - string,\n cokolwiek innego - wyjscie: ";
    std::getline(std::cin, driver);
    if(driver == "1")
            runConsoleInterface<int>();
    if(driver == "2")
            runConsoleInterface<double>();
    if(driver == "3")
            runConsoleInterface<string>();


    return 0;
}
