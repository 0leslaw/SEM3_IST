//
// Created by Hyperbook on 12.11.2023.
//

#ifndef ZAD3_NODE_H
#define ZAD3_NODE_H

#include <string>

using namespace std;

class Node {
    public:
        std::string* value;
        Node* left;
        Node* right;
        int ammountOfVars;
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


#endif //ZAD3_NODE_H
