//
// Created by Hyperbook on 13.11.2023.
//

#include "Tree.h"
#include "Node.h"

// Tree stuff
Tree::Tree() : root(NULL), varList(new ArrayList<string>()){}

bool Tree::setupTree(std::string& value) {
    int* currentIndex = new int(0);
    root = new Node();
    return setupTreeHelper(currentIndex,value,*root);
}
//TODO czy sprawdzac wyjscie za zakres na kazdym currentIndex++
bool Tree::setupTreeHelper(int *currentIndex, std::string &value, Node& root) {
    if (*currentIndex >= value.length())
        root.setValue(*new string("1"));
    //current is either a constant
    if(value[*currentIndex] > 47 && value[*currentIndex] < 58){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        (*currentIndex)++;
        //FIND END OF VARIABLE CHECK IF IS A SPACE OR END, IF IS
        while (value[*currentIndex] > 47 && value[*currentIndex] < 58 && *currentIndex < value.length()-1)
            (*currentIndex)++;

        if(*currentIndex+1>=value.length() || value[(*currentIndex)++] == 32) {
            root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex - 1)));

        }
        else
        fintNextIndAfterFail(root,value,currentIndex);


    }
        //or its a variable
    else if(value[*currentIndex] > 96 && value[*currentIndex] < 123){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        (*currentIndex)++;
        while (value[*currentIndex] > 96 && value[*currentIndex] < 123 && *currentIndex < value.length()-1)
            (*currentIndex)++;

        if(*currentIndex+1>=value.length() || value[(*currentIndex)++] == 32) {
            root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex - 1)));
            string *s = new string (value.substr(firstIndex,*currentIndex-firstIndex));
            //SET VALUE
            root.setValue(*s);
            //ADD NEW VAR TO LIST
            varList->add(*s);
        }
        else
            fintNextIndAfterFail(root,value,currentIndex);
    }
        //OR its an operator with two variables
    else if(value[*currentIndex] == 42
            || value[*currentIndex] == 43
            || value[*currentIndex] == 45
            || value[*currentIndex] == 47
            ){
        //we just have to find where the number ends to continue
        int startIndex = (*currentIndex)++;

        if(*currentIndex >= value.length()-1 || value[(*currentIndex)++] == 32){
            root.setValue(*new string (value.substr(startIndex,1)));
            Node* newLeft = new Node();
            Node* newRight = new Node();

            root.addArg(*newLeft);
            setupTreeHelper(currentIndex,value,*newLeft);
            root.addArg(*newRight);
            setupTreeHelper(currentIndex,value,*newRight);
        }
        else
        fintNextIndAfterFail(root,value,currentIndex);
    }else
        fintNextIndAfterFail(root,value,currentIndex);
    return false;
}

void Tree::preorderPrint() {
    preorderPrintHelper(root);
    cout << endl;
}

void Tree::fintNextIndAfterFail(Node &root,string& value, int* currentIndex) {
    // while we have a char suggesting a missclick
    root.setValue(*new std::string("1"));


    while (*currentIndex < value.length()
            && value[*currentIndex] != 42
           && value[*currentIndex] != 43
           && value[*currentIndex] != 45
           && value[*currentIndex] != 47
           && !(value[*currentIndex] > 96 && value[*currentIndex] < 123)
           && !(value[*currentIndex] > 47 && value[*currentIndex] < 58)
            ){
        // we have to remove the letter (move startIndex)
        (*currentIndex)++;
    }
}

void Tree::preorderPrintHelper(Node *root) {

    cout << *root->getValue();
    if (!root->isArgListNULL())
    for (int i = 0; i < root->getArgList()->getElemCount(); i++)
        preorderPrintHelper(root->getArgList()->get(i));

}


