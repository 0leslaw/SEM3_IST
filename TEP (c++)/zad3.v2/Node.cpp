//
// Created by Hyperbook on 13.11.2023.
//

#include "Node.h"
Node::Node(std::string& value) {
    this->value = &value;

}

Node::Node() {
    this->value = NULL;
    argList = new ArrayList<Node>();
}


void Node::setValue(std::string &s) {
    value = &s;
}


string *Node::getValue() {
    return value;
}

ArrayList<Node> *Node::getArgList() {
    return argList;
}



