//
// Created by Hyperbook on 13.11.2023.
//

#include "Tree.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
// Tree stuff
Tree::Tree() : treeRoot(NULL), varList(new ArrayList<string>()){}
//AUTODESCRIPTIVE
void Tree::setupTree(std::string& value) {
    int* currentIndex = new int(0);
    treeRoot = new Node();
    setupTreeHelper(currentIndex,value,*treeRoot);
    if (*currentIndex<value.length())
        cout<<"UCIETO WYRAZENIE - ZA DUZO ARGUMENTOW"<<endl;

    delete currentIndex;
}
//TAKES IN INT POINTER WHICH IT TREATS AS STRING ITERATOR AND RECURSIVELY A ROOT FOR
//WHICH IT TRIES TO ASSIGN ITS FIELDS BASED ON THE INPUT STRING
void Tree::setupTreeHelper(int *currentIndex, std::string &value, Node& root) {
    skipSpaces(value,currentIndex);
    if (*currentIndex >= value.length()) {
        root.setValue(*new string("1"));
        cout<<"UTWORZONO SZTUCZNIE WARTOSC"<<endl;
    }
    else if(isNextTrygon(currentIndex,value)){
        *currentIndex += 3;
        if(*currentIndex >= value.length() || value[*currentIndex] == 32){
            root.setValue(*new string (value.substr(*currentIndex-3,3)));
            Node* oneArg = new Node();
            (*currentIndex)++;
            setupTreeHelper(currentIndex,value,*oneArg);

            root.addArg(*oneArg);
        }
        else
            fintNextIndAfterFail(root,value,currentIndex);
    }
    //current is either a constant
    else if(isNextNumber(currentIndex,value)){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        (*currentIndex)++;
        //FIND END OF NUMBER CHECK IF IS A SPACE OR END, IF IS
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
    else if(isNextVar(currentIndex,value)){
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
            if (!varList->contains(*s))
                addVariable(*s);
        }
        else
            fintNextIndAfterFail(root,value,currentIndex);
    }
        //OR its an operator with two variables
    else if(isNextOperator(currentIndex,value)){
        //we just have to find where it ends to continue
        int startIndex = (*currentIndex)++;

        if(*currentIndex >= value.length()-1 || value[(*currentIndex)++] == 32){
            root.setValue(*new string (value.substr(startIndex,1)));
            Node* newLeft = new Node();
            Node* newRight = new Node();

            root.addArg(*newLeft);
            root.addArg(*newRight);

            setupTreeHelper(currentIndex,value,*newLeft);
            setupTreeHelper(currentIndex,value,*newRight);

        }
        else
        fintNextIndAfterFail(root,value,currentIndex);
    }else
        fintNextIndAfterFail(root,value,currentIndex);
}
//THIS TAKES THE POINTER TO INT VAL AND TREATS IT AS ITERATOR OF THE STRING
//ARRAY, RETURNS REQUIRED INDEX
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
//AUTODESCRIPTIVE
void Tree::skipSpaces(string &value,int *currentIndex) {
    while (value[*currentIndex] == 32)
        (*currentIndex)++;
}

void Tree::preorderPrint() {
    preorderPrintHelper(*treeRoot);
    cout << endl;
}
//RECURSIVELY PRINTS NODE VALUES
void Tree::preorderPrintHelper(Node &root) {
    cout << (root.getValue())+"; ";
    if (!root.isArgListNULLorEmpty())
        for (int i = 0; i < root.argCount(); i++)
            preorderPrintHelper(*(root.getArgAt(i)));
}
//CALCULATES TREE EQUATION
double Tree::computeForSetParameters(const ArrayList<int> &parameterSet) {
    if (parameterSet.getElemCount() != varList->getElemCount()) {
        cout << "ZLA ILOSC PARARMETROW";
        return -1;
    }
    else{
        return computeHelper(parameterSet,*treeRoot);
    }
}
//TAKES IN PARAMETERSET FOR WHICH IT CALCULATES EQUATION RECURSIVELY WHICH CONVENIANTLY
//WILL CALCULATE THE LEAFS FIRST AND THEN PROPAGATE UP THE TREE
double Tree::computeHelper(const ArrayList<int> &parameterSet, Node &root) {
    //operators
    // *
    if(root.value[0] == 42)
        return computeHelper(parameterSet,*root.getArgAt(0)) *
        computeHelper(parameterSet,*root.getArgAt(1));
    // +
    if(root.value[0] == 43)
        return computeHelper(parameterSet,*root.getArgAt(0)) +
               computeHelper(parameterSet,*root.getArgAt(1));
    // -
    if(root.value[0] == 45)
        return computeHelper(parameterSet,*root.getArgAt(0)) -
               computeHelper(parameterSet,*root.getArgAt(1));
    // /
    if(root.value[0] == 47)
        return computeHelper(parameterSet,*root.getArgAt(0)) /
               computeHelper(parameterSet,*root.getArgAt(1));
    //num
    if(root.value[0] > 47 && root.value[0] < 58)
        return std::atoi(root.value.c_str());
    //var
    if(root.value[0] > 92 && root.value[0] < 123){
        int* i = new int(0);
        while(*i < varList->getElemCount()) {
            if (*varList->get(*i) == root.value)
                break;
            (*i)++;
        }
        int ii = *i;
        delete i;
        return *parameterSet.get(ii);
    }
    else if (root.value == "sin"){
        return sin(computeHelper(parameterSet,*root.getArgAt(0)));
    }
    else if (root.value == "cos"){
        return cos(computeHelper(parameterSet,*root.getArgAt(0)));
    }
    else return false;
}

//TAKES FURTHEST LEFT LEAF AND CHANGES IT TO THE ROOT OF TREE CREATED FROM  "value"
void Tree::joinTreeWithThis(string &value) {
    *this =*this + Tree(value);
}
//AUTODESCRIPTIVE
ArrayList<string> *Tree::getVarList() {
    return varList;
}
//AUTODESCRIPTIVE
Node *Tree::getRoot() const{
    return treeRoot;
}
//AUTODESCRIPTIVE
void Tree::setRoot(Node *newRoot) {
    treeRoot = newRoot;
}
//AUTODESCRIPTIVE
Tree Tree::operator+(const Tree &other) {
    //find any leaf
    Tree tempThis(*this);
    Tree* tempOther = new Tree(other);
    if (treeRoot == NULL || treeRoot->isArgListNULLorEmpty()){
        delete tempThis.getRoot();
        tempThis.setRoot(tempOther->getRoot());
    }
    else {
        Node* currentRoot = tempThis.getRoot();
        while (!currentRoot->getArgAt(0)->isArgListNULLorEmpty())
            currentRoot = currentRoot->getArgAt(0);
        currentRoot->getArgList()->setAt(0,*tempOther->getRoot());
    }
    if (!tempOther->isVarListNULLorEmpty()){
        for (int i = 0; i < tempOther->getVarListConst().getElemCount(); i++)
            tempThis.getVarList()->add(*new string(*tempOther->getVarListConst().get(i)));
    }
    return tempThis;
}
//AUTODESCRIPTIVE
Tree::Tree(const Tree &other) {
    varList = new ArrayList<string>();
    if (other.getRoot() == NULL){
        treeRoot = NULL;
        return;
    }
    treeRoot = new Node(*other.getRoot());
    if (!other.isVarListNULLorEmpty())
        for (int i = 0; i < other.getVarListConst().getElemCount(); i++) {
            varList->add(*new string(*other.getVarListConst().get(i)));

    }
    preorderPrint();
}
//AUTODESCRIPTIVE
ArrayList<string> &Tree::getVarListConst() const {
    return *varList;
}
//AUTODESCRIPTIVE
void Tree::addVariable(string &value) {
    if (varList == NULL)
        varList = new ArrayList<string>();
    varList->add(value);
}
//AUTODESCRIPTIVE
bool Tree::isNextTrygon(const int *currentIndex, string &value) {
    return *currentIndex+3 < value.length() &&  (value.substr(*currentIndex,3) == "sin" ||
                                                value.substr(*currentIndex,3) == "cos");
}
//AUTODESCRIPTIVE
bool Tree::isNextOperator(const int *currentIndex, string &value) {
    return value[*currentIndex] == 42
           || value[*currentIndex] == 43
           || value[*currentIndex] == 45
           || value[*currentIndex] == 47;
}
//AUTODESCRIPTIVE
bool Tree::isNextNumber(const int *currentIndex, string &value) {
    return value[*currentIndex] > 47 && value[*currentIndex] < 58;
}
//AUTODESCRIPTIVE
bool Tree::isNextVar(const int *currentIndex, string &value) {
    return value[*currentIndex] > 96 && value[*currentIndex] < 123;
}
//AUTODESCRIPTIVE
void Tree::printVars(){
    if (!isVarListNULLorEmpty()) {
        std::cout << "lista zmiennych:\n";
        for (int i = 0; i < varList->getElemCount(); i++) {
            std::cout << *varList->get(i) + " ";
        }
        std::cout << std::endl;
    }else
        std::cout << "BRAK ZMIENNYCH" << std::endl;
}
//AUTODESCRIPTIVE
bool Tree::isVarListNULLorEmpty() const{
    return varList == NULL || varList->getElemCount() == 0;
}
//AUTODESCRIPTIVE
Tree::~Tree() {
//    cout<< "Usunięto drzewo: "+treeRoot->getValue()+"MÓJ PANIE!"<<endl;
    delete treeRoot;
    delete varList;
}
//AUTODESCRIPTIVE
Tree::Tree(string &value) {
    treeRoot = NULL;
    varList = new ArrayList<string>();
    setupTree(value);
}
//AUTODESCRIPTIVE
Tree &Tree::operator=(const Tree &other) {
    if (this != &other){
        delete varList;
        delete treeRoot;
        varList = NULL;
        treeRoot = NULL;

        varList = new ArrayList<string>(other.getVarListConst());
        if (other.getRoot() != NULL)
            treeRoot = new Node(*other.getRoot());
    }else
        return *this;
}



