//
// Created by Hyperbook on 13.11.2023.
//

#include "Node.h"
Node::Node(std::string& value) {
    this->value = &value;
    argList = NULL;
}
// in case of new arraylist it will loop endlessly, //TODO zapytac
Node::Node() {
    this->value = NULL;
    argList = NULL;
}


void Node::setValue(std::string &s) {
    value = &s;
}


string *Node::getValue() const{
    return value;
}

ArrayList<Node> *Node::getArgList() const{
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
//TODO zapytaj co tu powinno sie robic
Node::~Node() {
//    delete argList;
}

Node::Node(const Node &other) {
    value = new string(*other.getValue());
    if(other.getArgList() != NULL)
    for (int i = 0; i < other.getArgList()->getElemCount(); i++)
        argList->add(*new Node(*other.getArgList()->get(i)));

}





