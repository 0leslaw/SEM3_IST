//
// Created by Hyperbook on 13.11.2023.
//

#ifndef ZAD3_V2_TREE_H
#define ZAD3_V2_TREE_H

#include <string>
#include "ArrayList.h"

using namespace std;
class Tree;

class Node {
private:
    std::string value;
    ArrayList<Node>* argList;
public:
    Node(std::string& value) {
        this->value = value;
        argList = NULL;
    }
// in case of new arraylist it will loop endlessly, //TODO zapytac
    Node() {
        argList = NULL;
    }
    Node(const Node &other) {
        value = other.getValue();
        argList = NULL;
        if(other.getArgList() != NULL)
            for (int i = 0; i < other.argCount(); i++)
                this->addArg(*new Node(*other.getArgList()->get(i)));
    }

    void setValue(std::string &s) {
        value = s;
    }

    string getValue() const{
        return value;
    }

    ArrayList<Node> *getArgList() const{
        return argList;
    }
    Node* getArgAt(int index) {
        return argList->get(index);
    }
    void addArg(Node& node) {
        if(argList == NULL)
            argList = new ArrayList<Node>();
        argList->add(node);
    }
    int argCount() const{
        return argList->getElemCount();
    }
    bool isArgListNULLorEmpty() {
        return argList == NULL || argCount() == 0;
    }
//TODO zapytaj co tu powinno sie robic
    ~Node() {
        cout<< "Usunieto node: "+value+" Moj panie!"<<endl;
        if(argList != NULL)
            delete argList;
    }

    friend class Tree;
};
class Tree {

private:
    Node* treeRoot;
    ArrayList<string>* varList;

    void setupTreeHelper(int* currentIndex, std::string& value, Node& root);
    void preorderPrintHelper(Node &root);
    void fintNextIndAfterFail(Node &root,string& value, int* currentIndex);
    void skipSpaces(string& value,int *currentIndex);
    void addVariable(string& value);
    static bool isNextTrygon(const int *currentIndex, std::string &value);
    static bool isNextOperator(const int *currentIndex, std::string &value);
    static bool isNextNumber(const int *currentIndex, std::string &value);
    static bool isNextVar(const int *currentIndex, std::string &value);
public:
    Tree();
    Tree(string& value);
    Tree operator+(const Tree& other);
    Tree& operator=(const Tree& other);
    Tree(const Tree& other);
    ~Tree();
    void setupTree(std::string& value);
    void preorderPrint();
    double computeForSetParameters(const ArrayList<int>& parameterSet);
    double computeHelper(const ArrayList<int>& parameterSet, Node& root);
    void joinTreeWithThis(string &value);
    ArrayList<string>* getVarList();
    ArrayList<string>& getVarListConst()const;
    bool isVarListNULLorEmpty() const;
    void printVars();
    Node *getRoot() const;
    void setRoot(Node *newRoot);
};


#endif //ZAD3_V2_TREE_H
