//
// Created by Hyperbook on 13.11.2023.
//

#include "Tree.h"
#include "Node.h"

// Tree stuff
Tree::Tree() : root(NULL), varList(new ArrayList<string>()){}

bool Tree::setupTree(std::string& value) {
    int* currentIndex = new int(0);

    return setupTreeHelper(currentIndex,value, *root);
}
//TODO czy sprawdzac wyjscie za zakres na kazdym currentIndex++
bool Tree::setupTreeHelper(int *currentIndex, std::string &value, Node& root) {
    if (*currentIndex >= value.length())
        root.setValue(*new string("1"));
    //current is either a constant
    if(value[*currentIndex] > 47 && value[*currentIndex] < 58){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        *currentIndex++;
        //FIND END OF VARIABLE CHECK IF IS A SPACE OR END, IF IS
        while (value[*currentIndex] > 47 && value[*currentIndex] < 58 && *currentIndex < value.length()-1)
            *currentIndex++;

        value[*currentIndex++] == 32?
        root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex)))
                                    :
        fintNextIndAfterFail(root,currentIndex);

        string *s = new string (value.substr(firstIndex,*currentIndex-firstIndex));
        //SET VALUE
        root.setValue(*s);
        //ADD NEW VAR TO LIST
        varList->add(*s);
    }
        //or its a variable
    else if(value[*currentIndex] > 96 && value[*currentIndex] < 123){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        *currentIndex++;
        while (value[*currentIndex] > 96 && value[*currentIndex] < 123 && *currentIndex < value.length()-1)
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

        *currentIndex >= value.length()-1 || value[*currentIndex++] == 32
        ?
        root.setValue(*new string (value.substr(*currentIndex,1)))
        :
        fintNextIndAfterFail(root,currentIndex);

        Node* newLeft = new Node();
        Node* newRight = new Node();

        root.getArgList()->add(*newLeft);
        setupTreeHelper(currentIndex,value,*newLeft);
        root.getArgList()->add(*newRight);
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

    cout << root->getValue();
    for (int i = 0; i < root->getArgList()->getElemCount(); i++)
        preorderPrintHelper(root->getArgList()->get(i));

}


