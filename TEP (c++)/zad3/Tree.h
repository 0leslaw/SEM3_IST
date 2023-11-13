//
// Created by Hyperbook on 07.11.2023.
//

#ifndef ZAD3_TREE_H
#define ZAD3_TREE_H
#include <iostream>
#include <wsman.h>
#include "Node.h"

using namespace std;
class Tree {

private:

    Node* root;

public:
    Tree();
    bool setupTree(std::string& value);
    bool setupTreeHelper(int* currentIndex, std::string& value, Node& root);
    void preorderPrint();
    void preorderPrintHelper(Node *root);
    void fintNextIndAfterFail(Node &root,int* currentIndex);
};


#endif //ZAD3_TREE_H
