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
    Tree& operator+(const Tree& other);
    Tree& operator=(const Tree& other);
    Tree(const Tree& other);
    void setupTree(std::string& value);
    void preorderPrint();
    void computeForSetParameters(ArrayList<int>& parameterSet);
    void joinTreeWithThis(string &value);
    ArrayList<string>& getVarList();
    ArrayList<string>& getVarListConst()const;


    Node *getRoot() const;

    void setRoot(Node *root);
};


#endif //ZAD3_V2_TREE_H
