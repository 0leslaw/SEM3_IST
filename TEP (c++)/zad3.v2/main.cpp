#include <iostream>
#include "Tree.h"

int main() {
    Tree* tree = new Tree();
    string *s = new string("sin 144554 23");
    tree->setupTree(*s);
    Tree tree1 = *new Tree(*tree);
    tree1.preorderPrint();
//    tree->joinTreeWithThis(*s);
//    tree->preorderPrint();
    return 0;
}
