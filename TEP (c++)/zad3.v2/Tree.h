//
// Created by Hyperbook on 13.11.2023.
//

#ifndef ZAD3_V2_Tree_H
#define ZAD3_V2_Tree_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cmath>
#include "ArrayList.h"

using namespace std;
template<class T>
class Tree;


template<class T>
class Node {
private:
    std::string value;
    ArrayList<Node<T> >* argList;
public:
    // ALL ARE AUTODESCRIPTIVE
    Node<T>(std::string& value) {
        this->value = value;
        argList = NULL;
    }
    Node<T>() {
        argList = NULL;
    }
    Node<T>(const Node<T> &other) {
        value = other.getValue();
        argList = NULL;
        if(other.getArgList() != NULL)
            for (int i = 0; i < other.argCount(); i++)
                this->addArg(*new Node<T>(*other.getArgList()->get(i)));
    }

    void setValue(std::string &s) {
        value = s;
    }

    string getValue() const{
        return value;
    }

    ArrayList<Node<T> > *getArgList() const{
        return argList;
    }
    Node<T>* getArgAt(int index) {
        return argList->get(index);
    }
    void addArg(Node<T>& node) {
        if(argList == NULL)
            argList = new ArrayList<Node<T> >();
        argList->add(node);
    }
    int argCount() const{
        return argList->getElemCount();
    }
    bool isArgListNULLorEmpty() {
        return argList == NULL || argCount() == 0;
    }
    ~Node() {
//        cout<< "Usunieto node: "+value+" Moj panie!"<<endl;
        if(argList != NULL)
            delete argList;
    }

    friend class Tree<T>;
};
template<class T>
class Tree {

private:
    Node<T>* treeRoot;
    ArrayList<string>* varList;

    void setupTreeHelperInt(int* currentIndex, std::string& value, Node<T>& root);
    void setupTreeHelperDouble(int* currentIndex, std::string& value, Node<T>& root);
    void setupTreeHelperString(int* currentIndex, std::string& value, Node<T>& root);
    void preorderPrintHelper(Node<T> &root);
    void findNextIndAfterFail(Node<T> &root, string& value, int* currentIndex);
    void skipSpaces(string& value,int *currentIndex);
    void addVariable(string& value);
    static bool isNextTrygon(const int *currentIndex, std::string &value);
    static bool isNextOperator(const int *currentIndex, std::string &value);
    static bool isNextNumber(const int *currentIndex, std::string &value);
    static bool isNextVar(const int *currentIndex, std::string &value);
public:
    Tree();
    Tree(string& value);
    Tree<T> operator+(const Tree<T>& other);
    Tree<T>& operator=(const Tree<T>& other);
    Tree(const Tree<T>& other);
    ~Tree();
    void setupTree(std::string& value);
    void preorderPrint();
    string computeForSetParameters(const ArrayList<string>& parameterSet);
    double computeHelper(const ArrayList<string>& parameterSet, Node<T>& root);
    string computeHelperString(const ArrayList<string>& parameterSet, Node<T>& root);

    void joinTreeWithThis(string &value);
    ArrayList<string>* getVarList();
    ArrayList<string>& getVarListConst()const;
    bool isVarListNULLorEmpty() const;
    void printVars();
    Node<T> *getRoot() const;
    void setRoot(Node<T> *newRoot);
    int getType();
};




template<>
inline int Tree<int>::getType() {
    return 1;
}
template<>
inline int Tree<double>::getType() {
    return 2;
}
template<>
inline int Tree<string>::getType() {
    return 3;
}
template<class T>
inline int Tree<T>::getType() {
    return -1;
}
// Tree<T> stuff

template <typename T>
Tree<T>::Tree() : treeRoot(NULL), varList(new ArrayList<string>()){}
//AUTODESCRIPTIVE
template <typename T>
void Tree<T>::setupTree(std::string& value) {
    int* currentIndex = new int(0);
    treeRoot = new Node<T>();
    switch (getType()) {
        case 1:
            setupTreeHelperInt(currentIndex, value, *treeRoot);
            break;
        case 2:
            setupTreeHelperDouble(currentIndex, value, *treeRoot);
            break;
        case 3:
            setupTreeHelperString(currentIndex, value, *treeRoot);
            break;
        default:
            break;
    }
    if (*currentIndex<value.length())
        cout<<"UCIETO WYRAZENIE - ZA DUZO ARGUMENTOW"<<endl;

    delete currentIndex;
}
//TAKES IN INT POINTER WHICH IT TREATS AS STRING ITERATOR AND RECURSIVELY A ROOT FOR
//WHICH IT TRIES TO ASSIGN ITS FIELDS BASED ON THE INPUT STRING
template <typename T>
void Tree<T>::setupTreeHelperInt(int *currentIndex, std::string &value, Node<T>& root) {
    skipSpaces(value,currentIndex);
    if (*currentIndex >= value.length()) {
        root.setValue(*new string("1"));
        cout<<"UTWORZONO SZTUCZNIE WARTOSC"<<endl;
    }
    else if(isNextTrygon(currentIndex,value)){
        *currentIndex += 3;
        if(*currentIndex >= value.length() || value[*currentIndex] == 32){
            root.setValue(*new string (value.substr(*currentIndex-3,3)));
            Node<T>* oneArg = new Node<T>();
            (*currentIndex)++;
            setupTreeHelperInt(currentIndex, value, *oneArg);

            root.addArg(*oneArg);
        }
        else
            findNextIndAfterFail(root, value, currentIndex);
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
            findNextIndAfterFail(root, value, currentIndex);


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
            findNextIndAfterFail(root, value, currentIndex);
    }
        //OR its an operator with two variables
    else if(isNextOperator(currentIndex,value)){
        //we just have to find where it ends to continue
        int startIndex = (*currentIndex)++;

        if(*currentIndex >= value.length()-1 || value[(*currentIndex)++] == 32){
            root.setValue(*new string (value.substr(startIndex,1)));
            Node<T>* newLeft = new Node<T>();
            Node<T>* newRight = new Node<T>();

            root.addArg(*newLeft);
            root.addArg(*newRight);

            setupTreeHelperInt(currentIndex, value, *newLeft);
            setupTreeHelperInt(currentIndex, value, *newRight);

        }
        else
            findNextIndAfterFail(root, value, currentIndex);
    }else
        findNextIndAfterFail(root, value, currentIndex);
}
template<class T>
void Tree<T>::setupTreeHelperString(int *currentIndex, string &value, Node<T> &root) {
    skipSpaces(value,currentIndex);
    if (*currentIndex >= value.length()) {
        root.setValue(*new string("'ala'"));
        cout<<"UTWORZONO SZTUCZNIE WARTOSC"<<endl;
    }
    //current is either a string
    else if(value[*currentIndex] == '\''){
        //we just have to find where the str ends to continue
        int firstIndex = *currentIndex;
        (*currentIndex)++;
        //FIND END OF STR CHECK IF IS A SPACE OR END, IF IS
        while (value[(*currentIndex)] != '\'')
            (*currentIndex)++;

        if(*currentIndex < value.length() && value[(*currentIndex)++] == '\'' && (*currentIndex >= value.length() || value[*currentIndex] == 32)){
            root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex)));
            (*currentIndex)++;
        }
        else
            findNextIndAfterFail(root, value, currentIndex);


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
            findNextIndAfterFail(root, value, currentIndex);
    }
        //OR its an operator with two variables
    else if(isNextOperator(currentIndex,value)){
        //we just have to find where it ends to continue
        int startIndex = (*currentIndex)++;

        if(*currentIndex >= value.length()-1 || value[(*currentIndex)++] == 32){
            root.setValue(*new string (value.substr(startIndex,1)));
            Node<T>* newLeft = new Node<T>();
            Node<T>* newRight = new Node<T>();

            root.addArg(*newLeft);
            root.addArg(*newRight);

            setupTreeHelperString(currentIndex, value, *newLeft);
            setupTreeHelperString(currentIndex, value, *newRight);

        }
        else
            findNextIndAfterFail(root, value, currentIndex);
    }else{
        findNextIndAfterFail(root, value, currentIndex);
        root.setValue(*new std::string("'ala'"));
    }
}

template<class T>
void Tree<T>::setupTreeHelperDouble(int *currentIndex, string &value, Node<T> &root) {
    skipSpaces(value,currentIndex);
    if (*currentIndex >= value.length()) {
        root.setValue(*new string("1.0"));
        cout<<"UTWORZONO SZTUCZNIE WARTOSC"<<endl;
    }
    else if(isNextTrygon(currentIndex,value)){
        *currentIndex += 3;
        if(*currentIndex >= value.length() || value[*currentIndex] == 32){
            root.setValue(*new string (value.substr(*currentIndex-3,3)));
            Node<T>* oneArg = new Node<T>();
            (*currentIndex)++;
            setupTreeHelperDouble(currentIndex, value, *oneArg);

            root.addArg(*oneArg);
        }
        else
            findNextIndAfterFail(root, value, currentIndex);
    }
        //current is either a constant
    else if(isNextNumber(currentIndex,value)){
        //we just have to find where the number ends to continue
        int firstIndex = *currentIndex;
        //flag of point so the point cant be doubled
        int pointFlag=-1;
        //FIND END OF NUMBER CHECK IF IS A SPACE OR END, IF IS
        while (*currentIndex < value.length() && value[*currentIndex] > 47 && value[*currentIndex] < 58){
            (*currentIndex)++;
            if (value[*currentIndex] == '.' && pointFlag == -1)
                pointFlag = (*currentIndex)++;
        }
        if(value[*currentIndex]!='.' && (*currentIndex >= value.length() || value[*currentIndex] == 32)) {
            root.setValue(*new string(value.substr(firstIndex, *currentIndex - firstIndex)));
            (*currentIndex)++;
        }
        else
            findNextIndAfterFail(root, value, currentIndex);


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
            findNextIndAfterFail(root, value, currentIndex);
    }
        //OR its an operator with two variables
    else if(isNextOperator(currentIndex,value)){
        //we just have to find where it ends to continue
        int startIndex = (*currentIndex)++;

        if(*currentIndex >= value.length()-1 || value[(*currentIndex)++] == 32){
            root.setValue(*new string (value.substr(startIndex,1)));
            Node<T>* newLeft = new Node<T>();
            Node<T>* newRight = new Node<T>();

            root.addArg(*newLeft);
            root.addArg(*newRight);

            setupTreeHelperDouble(currentIndex, value, *newLeft);
            setupTreeHelperDouble(currentIndex, value, *newRight);

        }
        else
            findNextIndAfterFail(root, value, currentIndex);
    }else {
        findNextIndAfterFail(root, value, currentIndex);
    }
}
//THIS TAKES THE POINTER TO INT VAL AND TREATS IT AS ITERATOR OF THE STRING
//ARRAY, RETURNS REQUIRED INDEX
template <typename T>
void Tree<T>::findNextIndAfterFail(Node<T> &root, string& value, int* currentIndex) {
    // while we have a char suggesting a missclick
    switch (getType()) {
        case 1:
            root.setValue(*new string("1"));
            break;
        case 2:
            root.setValue(*new string("1.0"));
            break;
        case 3:
            root.setValue(*new string("'ala'"));
            break;
        default:
            break;
    }
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
template <typename T>
void Tree<T>::skipSpaces(string &value,int *currentIndex) {
    while (value[*currentIndex] == 32)
        (*currentIndex)++;
}
template <typename T>
void Tree<T>::preorderPrint() {
    preorderPrintHelper(*treeRoot);
    cout << endl;
}
//RECURSIVELY PRINTS Node<T> VALUES
template <typename T>
void Tree<T>::preorderPrintHelper(Node<T> &root) {
    cout << (root.getValue())+"; ";
    if (!root.isArgListNULLorEmpty())
        for (int i = 0; i < root.argCount(); i++)
            preorderPrintHelper(*(root.getArgAt(i)));
}
//CALCULATES Tree<T> EQUATION
template <typename T>
string Tree<T>::computeForSetParameters(const ArrayList<string> &parameterSet) {
    if (parameterSet.getElemCount() != varList->getElemCount()) {
        cout << "ZLA ILOSC PARARMETROW";
        return "ajc";
    }
    else if (getType() == 3){
      return computeHelperString(parameterSet,*treeRoot);
    }
    else {
        std::ostringstream oss;
        oss << computeHelper(parameterSet, *treeRoot);
        std::string myString = oss.str();
        return myString;
    }
}
template<class T>
string Tree<T>::computeHelperString(const ArrayList<string> &parameterSet, Node<T> &root) {
//operators
    // *
    if(root.value[0] == 42) {
        string s = computeHelperString(parameterSet, *root.getArgAt(0));
        string inserted = computeHelperString(parameterSet, *root.getArgAt(1));
        for (int i = 0; i < s.length(); i++) {
            if(s[i] == inserted[0]){
                s = s.insert(i+1,inserted.substr(1,inserted.length()));
                i+=inserted.length()-1;
            }
        }
        return s;
    }     ;
    // +String
    if(root.value[0] == 43)
        return computeHelperString(parameterSet,*root.getArgAt(0)) +
               computeHelperString(parameterSet,*root.getArgAt(1));
    // -String
    if(root.value[0] == 45) {
        string s = computeHelperString(parameterSet, *root.getArgAt(0));
        string pattern = computeHelperString(parameterSet, *root.getArgAt(1));
        size_t pos = s.rfind(pattern);  // rfind searches from the end

        if (pos != std::string::npos && pos == s.length() - pattern.length()) {
            // Erase the pattern only if it is at the end
            s.erase(pos, pattern.length());
        }
        return s;
    }
    // /String
    if(root.value[0] == 47) {
        string s = computeHelperString(parameterSet, *root.getArgAt(0));
        string pattern = computeHelperString(parameterSet, *root.getArgAt(1));
        size_t found = s.find(pattern);

        while (found != std::string::npos) {
            // Erase the found pattern
            s.erase(found+1, pattern.length()-1);

            // Search for the next occurrence, starting from the current position
            found = s.find(pattern, found);
        }
        return s;
    }
    //string
    if(root.value[0] == '\'')
        return root.value.substr(1,root.value.length()-2);
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
        return (*parameterSet.get(ii)).substr(1,root.value.length()-2);
    }
    else return false;
}
//TAKES IN PARAMETERSET FOR WHICH IT CALCULATES EQUATION RECURSIVELY WHICH CONVENIANTLY
//WILL CALCULATE THE LEAFS FIRST AND THEN PROPAGATE UP THE Tree<T>
template <typename T>
double Tree<T>::computeHelper(const ArrayList<string> &parameterSet, Node<T> &root) {
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
        return std::atof(root.value.c_str());
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
        string s = *parameterSet.get(ii);
        return std::atof(s.c_str());
    }
    else if (root.value == "sin"){
        return sin(computeHelper(parameterSet,*root.getArgAt(0)));
    }
    else if (root.value == "cos"){
        return cos(computeHelper(parameterSet,*root.getArgAt(0)));
    }
    else return false;
}

//TAKES FURTHEST LEFT LEAF AND CHANGES IT TO THE ROOT OF Tree<T> CREATED FROM  "value"
template <typename T>
void Tree<T>::joinTreeWithThis(string &value) {
    *this =*this + Tree<T>(value);
}
//AUTODESCRIPTIVE
template <typename T>
ArrayList<string> *Tree<T>::getVarList() {
    return varList;
}
//AUTODESCRIPTIVE
template <typename T>
Node<T> *Tree<T>::getRoot() const{
    return treeRoot;
}
//AUTODESCRIPTIVE
template <typename T>
void Tree<T>::setRoot(Node<T> *newRoot) {
    treeRoot = newRoot;
}
//AUTODESCRIPTIVE
template <typename T>
Tree<T> Tree<T>::operator+(const Tree<T> &other) {
    //find any leaf
    Tree<T> tempThis(*this);
    Tree<T>* tempOther = new Tree<T>(other);
    if (treeRoot == NULL || treeRoot->isArgListNULLorEmpty()){
        delete tempThis.getRoot();
        tempThis.setRoot(tempOther->getRoot());
    }
    else {
        Node<T>* currentRoot = tempThis.getRoot();
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
template <typename T>
Tree<T>::Tree(const Tree<T> &other) {
    varList = new ArrayList<string>();
    if (other.getRoot() == NULL){
        treeRoot = NULL;
        return;
    }
    treeRoot = new Node<T>(*other.getRoot());
    if (!other.isVarListNULLorEmpty())
        for (int i = 0; i < other.getVarListConst().getElemCount(); i++) {
            varList->add(*new string(*other.getVarListConst().get(i)));

        }
    preorderPrint();
}
//AUTODESCRIPTIVE
template <typename T>
ArrayList<string> &Tree<T>::getVarListConst() const {
    return *varList;
}
//AUTODESCRIPTIVE
template <typename T>
void Tree<T>::addVariable(string &value) {
    if (varList == NULL)
        varList = new ArrayList<string>();
    varList->add(value);
}
//AUTODESCRIPTIVE
template <typename T>
bool Tree<T>::isNextTrygon(const int *currentIndex, string &value) {
    return *currentIndex+3 < value.length() &&  (value.substr(*currentIndex,3) == "sin" ||
                                                 value.substr(*currentIndex,3) == "cos");
}
//AUTODESCRIPTIVE
template <typename T>
bool Tree<T>::isNextOperator(const int *currentIndex, string &value) {
    return value[*currentIndex] == 42
           || value[*currentIndex] == 43
           || value[*currentIndex] == 45
           || value[*currentIndex] == 47;
}
//AUTODESCRIPTIVE
template <typename T>
bool Tree<T>::isNextNumber(const int *currentIndex, string &value) {
    return value[*currentIndex] > 47 && value[*currentIndex] < 58;
}
//AUTODESCRIPTIVE
template <typename T>
bool Tree<T>::isNextVar(const int *currentIndex, string &value) {
    return value[*currentIndex] > 96 && value[*currentIndex] < 123;
}
//AUTODESCRIPTIVE
template <typename T>
void Tree<T>::printVars(){
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
template <typename T>
bool Tree<T>::isVarListNULLorEmpty() const{
    return varList == NULL || varList->getElemCount() == 0;
}
//AUTODESCRIPTIVE
template <typename T>
Tree<T>::~Tree() {
//    cout<< "Usunięto drzewo: "+treeRoot->getValue()+"MÓJ PANIE!"<<endl;
    delete treeRoot;
    delete varList;
}
//AUTODESCRIPTIVE
template <typename T>
Tree<T>::Tree(string &value) {
    treeRoot = NULL;
    varList = new ArrayList<string>();
    setupTree(value);
}
//AUTODESCRIPTIVE
template <typename T>
Tree<T> &Tree<T>::operator=(const Tree<T> &other) {
    if (this != &other){
        delete varList;
        delete treeRoot;
        varList = NULL;
        treeRoot = NULL;

        varList = new ArrayList<string>(other.getVarListConst());
        if (other.getRoot() != NULL)
            treeRoot = new Node<T>(*other.getRoot());
    }else
        return *this;
}


#endif //ZAD3_V2_Tree_H
