//
// Created by Hyperbook on 13.11.2023.
//

#ifndef ZAD3_V2_TREE_H
#define ZAD3_V2_TREE_H

#include <string>
#include "Node.h"
#include "ArrayList.h"

using namespace std;

class Tree {

private:
    Node* root;
    ArrayList<string>* varList;

    void setupTreeHelper(int* currentIndex, std::string& value, Node& root);
    void preorderPrintHelper(Node *root);
    void fintNextIndAfterFail(Node &root,string& value, int* currentIndex);
    void skipSpaces(string& value,int *currentIndex);
public:
    Tree();
    void setupTree(std::string& value);
    void preorderPrint();

};


#endif //ZAD3_V2_TREE_H
