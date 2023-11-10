//
// Created by Hyperbook on 07.11.2023.
//

#ifndef ZAD3_TREE_H
#define ZAD3_TREE_H
#import <iostream>
#include <wsman.h>

class Tree {
private:
    class Node{
    private:
        std::string value;
        Node left;
        Node right;
    public:
        Node(std::string value);
    };
    Node root;

public:
    Tree();
    bool setupTree(std::string);
    
};


#endif //ZAD3_TREE_H
