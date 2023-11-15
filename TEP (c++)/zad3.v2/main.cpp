#include <iostream>
#include "Tree.h"

int main() {
    Tree* tree = new Tree();
    tree->setupTree(*new string("* 2 2"));
    tree->preorderPrint();
    return 0;
}
