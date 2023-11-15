//
// Created by Hyperbook on 13.11.2023.
//

#include "Node.h"
Node::Node(std::string& value) {
    this->value = &value;

}
// in case of new arraylist it will loop endlessly, //TODO zapytac
Node::Node() {
    this->value = NULL;
    argList = NULL;
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

void Node::addArg(Node node) {
    if(argList == NULL)
        argList = new ArrayList<Node>();
    argList->add(node);
}

bool Node::isArgListNULL() {
    return argList == NULL;
}





