//
// Created by Hyperbook on 12.11.2023.
//

#include "Node.h"
Node::Node(std::string& value) {
    this->value = &value;
    this->left = NULL;
    this->right = NULL;
    this->ammountOfVars = 0;
}

Node::Node() {
    this->value = NULL;
    this->left = NULL;
    this->right = NULL;
    this->ammountOfVars = 0;
}

Node* Node::getLeft() {
    return left;
}

Node* Node::getRight() {
    return right;
}

void Node::setLeft(Node &node) {
    left = &node;
}

void Node::setRight(Node &node) {
    right = &node;
}

void Node::setValue(std::string &s) {
    value = &s;
}

void Node::incVars() {
    ammountOfVars++;
}