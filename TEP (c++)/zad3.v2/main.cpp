#include <iostream>
#include "Tree.h"

int main() {
    Tree* tree = new Tree();
    string *s = new string("sin * 10230");
    tree->setupTree(*s);
    Tree tree1 = *new Tree(*tree);
    tree1.preorderPrint();
    tree->joinTreeWithThis(*s);
    tree->preorderPrint();
//    tree->preorderPrint();
//    std::string userInput;
//
//    while (true) {
//        // Prompt the user for input
//        std::cout << "Enter something (type 'exit' to stop): ";
//
//        // Read input from the user
//        std::cin >> userInput;
//
//        // Check if the user wants to exit
//        if (userInput == "exit") {
//            break;  // Exit the loop
//        }
//
//        // Process the input (you can do something with it)
//        std::cout << "You entered: " << userInput << std::endl;
//    }
    return 0;
}
