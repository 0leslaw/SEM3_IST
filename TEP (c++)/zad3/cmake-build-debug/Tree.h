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
    public:
        Node(std::string& value);
        Node* getLeft();
        Node* getRight();
        string* getValue();
        void setLeft(Node& node);
        void setRight(Node& node);
        void setValue(string s);

    };
    Node* root;

public:
    Tree();
    bool setupTree(std::string& value);
    bool setupTreeHelper(int* currentIndex, std::string& value, Node* root);
};


#endif //ZAD3_TREE_H
