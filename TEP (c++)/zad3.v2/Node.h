//
// Created by Hyperbook on 13.11.2023.
//

#ifndef ZAD3_V2_NODE_H
#define ZAD3_V2_NODE_H
#include <iostream>
#include "ArrayList.h"

using namespace std;


class Node {
private:
    std::string* value;
    ArrayList<Node>* argList;
public:

    Node(std::string& value);
    Node();
    Node(const Node& other);
    ~Node();
    string* getValue() const;
    void setValue(string& s);

    ArrayList<Node> *getArgList() const;
    void addArg(Node node);
    bool isArgListNULL();
};


#endif //ZAD3_V2_NODE_H
