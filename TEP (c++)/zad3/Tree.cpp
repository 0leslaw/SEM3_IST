//
// Created by Hyperbook on 07.11.2023.
//

#include "Tree.h"
//Node stuff



// Tree stuff
bool Tree::setupTree(std::string& value) {
    int* currentIndex = new int(0);

    return setupTreeHelper(currentIndex,value, *root);
}
//TODO czy sprawdzac wyjscie za zakres na kazdym currentIndex++
bool Tree::setupTreeHelper(int *currentIndex, std::string &value, Node& root) {
    //current is either a constant
    if(value[*currentIndex] > 47 && value[*currentIndex] < 58){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        *currentIndex++;
        while (value[*currentIndex] > 47 && value[*currentIndex] < 58)
            *currentIndex++;

        value[*currentIndex++] == 32?
        root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex)))
        :
        fintNextIndAfterFail(root,currentIndex);

        root.setValue(*new string (value.substr(firstIndex,*currentIndex-firstIndex)));
    }
    //or its a variable
    else if(value[*currentIndex] > 96 && value[*currentIndex] < 123){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        *currentIndex++;
        while (value[*currentIndex] > 96 && value[*currentIndex] < 123)
            *currentIndex++;

        value[*currentIndex++] == 32
        ?
            root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex)))
        :
            fintNextIndAfterFail(root,currentIndex);


    }
    //OR its an operator with two variables
    else if(value[*currentIndex] == 42
    || value[*currentIndex] == 43
    || value[*currentIndex] == 45
    || value[*currentIndex] == 47
    ){
        //we just have to find where the number ends to continue
        *currentIndex++;

        value[*currentIndex++] == 32
        ?
        root.setValue(*new string (value.substr(*currentIndex,1)))
        :
        fintNextIndAfterFail(root,currentIndex);

        Node* newLeft = new Node();
        Node* newRight = new Node();

        root.setLeft(*newLeft);
        root.setRight(*newRight);

        setupTreeHelper(currentIndex,value,*newLeft);
        setupTreeHelper(currentIndex,value,*newRight);
    }else
        fintNextIndAfterFail(root,currentIndex);
    return false;
}

void Tree::preorderPrint() {
    preorderPrintHelper(root);
    cout << endl;
}

void Tree::fintNextIndAfterFail(Node &root,int* currentIndex) {
    // while we have a char suggesting a missclick

    string value = *root.getValue();
    if (*currentIndex >= value.length()){
        root.setValue(*new std::string("0"));
        return;
    }

    while (value[*currentIndex] != 42
           && value[*currentIndex] != 43
           && value[*currentIndex] != 45
           && value[*currentIndex] != 47
           && !(value[*currentIndex] > 96 && value[*currentIndex] < 123)
           && !(value[*currentIndex] > 47 && value[*currentIndex] < 58)
            ){
        // we have to remove the letter (move startIndex)
        *currentIndex++;
    }
    root.setValue(*new std::string("0"));
}

void Tree::preorderPrintHelper(Node *root) {
    if(root == NULL)
        return;
    cout << root->getValue();
    preorderPrintHelper(root->getLeft());
    preorderPrintHelper(root->getRight());
}
