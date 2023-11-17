//
// Created by Hyperbook on 13.11.2023.
//

#include "Node.h"
Node::Node(std::string& value) {
    this->value = value;
    argList = NULL;
}
// in case of new arraylist it will loop endlessly, //TODO zapytac
Node::Node() {
    argList = NULL;
}


void Node::setValue(std::string &s) {
    value = s;
}


string Node::getValue() const{
    return value;
}

ArrayList<Node> *Node::getArgList() const{
    return argList;
}

void Node::addArg(const Node& node) {
    if(argList == NULL)
        argList = new ArrayList<Node>();
    argList->add(node);
}

bool Node::isArgListNULL() {
    return argList == NULL;
}
//TODO zapytaj co tu powinno sie robic
Node::~Node() {
    if(!isArgListNULL())
        delete argList;
}

Node::Node(const Node &other) {
    //TODO czy spowoduje mem leak gdy value jest static
    value = *new string(other.getValue());
    if(other.getArgList() != NULL)
    for (int i = 0; i < other.getArgList()->getElemCount(); i++)
        this->addArg(*new Node(*other.getArgList()->get(i)));
    else argList = NULL;
}





