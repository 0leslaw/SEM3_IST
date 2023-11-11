//
// Created by Hyperbook on 07.11.2023.
//

#ifndef ZAD3_TREE_H
#define ZAD3_TREE_H
#import <iostream>
#include <wsman.h>
using namespace std;
class Tree {
private:
    class Node{
    private:
        std::string* value;
        Node* left;
        Node* right;
        int ammountOfVars;
    public:
        Node(std::string& value);
        Node();
        Node* getLeft();
        Node* getRight();
        string* getValue();
        void incVars();
        void setLeft(Node& node);
        void setRight(Node& node);
        void setValue(string& s);

    };
    Node* root;

public:
    Tree();
    bool setupTree(std::string& value);
    bool setupTreeHelper(int* currentIndex, std::string& value, Node& root);
    void preorderPrint();
    void preorderPrintHelper(Tree::Node *root);
    void fintNextIndAfterFail(Tree::Node &root,int* currentIndex)
};


#endif //ZAD3_TREE_H
