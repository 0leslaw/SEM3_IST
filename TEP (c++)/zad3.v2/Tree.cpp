//
// Created by Hyperbook on 13.11.2023.
//

#include "Tree.h"
#include "Node.h"

// Tree stuff
Tree::Tree() : root(NULL), varList(new ArrayList<string>()){}

void Tree::setupTree(std::string& value) {
    int* currentIndex = new int(0);
    root = new Node();
    setupTreeHelper(currentIndex,value,*root);
    if (*currentIndex<value.length())
        cout<<"UCIETO WYRAZENIE - ZA DUZO ARGUMENTOW"<<endl;
    preorderPrint();
    varList->printStrings();
}
//TODO czy sprawdzac wyjscie za zakres na kazdym currentIndex++
void Tree::setupTreeHelper(int *currentIndex, std::string &value, Node& root) {
    skipSpaces(value,currentIndex);
    if (*currentIndex >= value.length()) {
        root.setValue(*new string("1"));
        cout<<"UTWORZONO SZTUCZNIE WARTOSC"<<endl;
    }
    else if(*currentIndex+3 < value.length() && (value.substr(*currentIndex,3) == "sin" ||
            value.substr(*currentIndex,3) == "cos")
    ){
        *currentIndex += 3;
        if(*currentIndex >= value.length() || value[*currentIndex] == 32){
            root.setValue(*new string (value.substr(*currentIndex-3,3)));
            Node* oneArg = new Node();
            (*currentIndex)++;
            setupTreeHelper(currentIndex,value,*oneArg);

            root.addArg(*oneArg);

            delete oneArg;
        }
        else
            fintNextIndAfterFail(root,value,currentIndex);
    }
    //current is either a constant
    else if(value[*currentIndex] > 47 && value[*currentIndex] < 58){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        (*currentIndex)++;
        //FIND END OF VARIABLE CHECK IF IS A SPACE OR END, IF IS
        while (*currentIndex < value.length() && value[*currentIndex] > 47 && value[*currentIndex] < 58)
            (*currentIndex)++;

        if(*currentIndex >= value.length() || value[*currentIndex] == 32) {
            root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex)));
            (*currentIndex)++;
        }
        else
        fintNextIndAfterFail(root,value,currentIndex);


    }
        //or its a variable
    else if(value[*currentIndex] > 96 && value[*currentIndex] < 123){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        (*currentIndex)++;
        while (*currentIndex < value.length() && value[*currentIndex] > 96 && value[*currentIndex] < 123)
            (*currentIndex)++;

        if(*currentIndex>=value.length() || value[*currentIndex] == 32) {
            root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex)));
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

            setupTreeHelper(currentIndex,value,*newLeft);
            setupTreeHelper(currentIndex,value,*newRight);

            root.addArg(*newLeft);
            root.addArg(*newRight);

            delete newLeft;
            delete newRight;
        }
        else
        fintNextIndAfterFail(root,value,currentIndex);
    }else
        fintNextIndAfterFail(root,value,currentIndex);
}

void Tree::preorderPrint() {
    preorderPrintHelper(root);
    cout << endl;
}

void Tree::fintNextIndAfterFail(Node &root,string& value, int* currentIndex) {
    // while we have a char suggesting a missclick
    root.setValue(*new std::string("1"));
    cout << "ZNALEZIONO BLAD WE WPROWADZONYM WYRAZENIU"<<endl;

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
    string temp = *(root->getValue());
    cout << *(root->getValue())+" ";
    if (!root->isArgListNULL())
    for (int i = 0; i < root->getArgList()->getElemCount(); i++)
        preorderPrintHelper(root->getArgList()->get(i));
}

void Tree::skipSpaces(string &value,int *currentIndex) {
    while (value[*currentIndex] == 32)
        (*currentIndex)++;
}

void Tree::computeForSetParameters(ArrayList<int> &parameterSet) {

}

void Tree::joinTreeWithThis(string &value) {
    //find any leaf
    Node* currentRoot = this->root;
    while (!currentRoot->isArgListNULL())
        currentRoot = currentRoot->getArgList()->get(0);

    Tree temp = *new Tree();
    temp.setupTree(value);
    for (int i = 0; i < temp.getVarList().getElemCount(); i++) {
        varList->add(*temp.getVarList().get(i));
    }
    currentRoot->addArg(*temp.getRoot());
}

ArrayList<string> &Tree::getVarList() {
    return *varList;
}

Node *Tree::getRoot() const{
    return root;
}

void Tree::setRoot(Node *root) {
    Tree::root = root;
}

Tree &Tree::operator+(const Tree &other) {
    Tree temp = *new Tree();
    //find any leaf
    Node* currentRoot = this->root;
    while (!currentRoot->isArgListNULL())
        currentRoot = currentRoot->getArgList()->get(0);

    for (int i = 0; i < temp.getVarList().getElemCount(); i++) {
        varList->add(*temp.getVarList().get(i));
    }
    currentRoot->addArg(*temp.getRoot());
    return temp;
}

Tree &Tree::operator=(const Tree &other) {
    return *this;
}

Tree::Tree(const Tree &other) {
    root = new Node(*other.getRoot());
}

ArrayList<string> &Tree::getVarListConst() const {
    return *varList;
}


