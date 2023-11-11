//
// Created by Hyperbook on 07.11.2023.
//

#include "Tree.h"

Tree::Node::Node(std::string& value) {
    this->value = &value;
    this->left = NULL;
    this->right = NULL;
}

Tree::Node* Tree::Node::getLeft() {
    return left;
}

Tree::Node* Tree::Node::getRight() {
    return right;
}

bool Tree::setupTree(std::string& value) {
    int* currentIndex = new int(0);

    return setupTreeHelper(currentIndex,value, root);
}

bool Tree::setupTreeHelper(int *currentIndex, std::string &value, Node* root) {
    //current is either a constant
    if(value[*currentIndex] > 47 && value[*currentIndex] < 58){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        *currentIndex++;
        while (value[*currentIndex] > 47 && value[*currentIndex] < 58)
            *currentIndex++;

        root->setValue(value.substr(firstIndex,*currentIndex));
    }
    //or its a variable
    if(value[*currentIndex] > 96 && value[*currentIndex] < 123){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        *currentIndex++;
        while (value[*currentIndex] > 47 && value[*currentIndex] < 58)
            *currentIndex++;

        root->setValue(value.substr(firstIndex,*currentIndex));
    }
    //OR its an operator with two variables
    if(value[*currentIndex] == 42
    || value[*currentIndex] == 43
    || value[*currentIndex] == 45
    || value[*currentIndex] == 47
    ){
        //we just have to find where the number ends to continue
        root->setValue(value.substr(*currentIndex,*currentIndex));
        *currentIndex++;

    }
}
