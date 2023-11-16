#include <iostream>
#include "Tree.h"

int main() {
    Tree* tree = new Tree();
    tree->setupTree(*new string("sin 144554 23"));
    Tree tree1 = *new Tree(*tree);
    tree1.preorderPrint();
    return 0;
}
