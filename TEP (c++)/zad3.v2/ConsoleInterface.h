//
// Created by Hyperbook on 26.11.2023.
//

#ifndef ZAD3_V2_CONSOLEINTERFACE_H
#define ZAD3_V2_CONSOLEINTERFACE_H
#include <iostream>
#include <cstdlib>
#include "ConsoleInterface.h"
#include "Tree.h"

using namespace std;

template <class T>
class ConsoleInterface {
public:
    ConsoleInterface();
    void run();
};
template <class T>
ConsoleInterface<T>::ConsoleInterface() {

}

template <class T>
void ConsoleInterface<T>::run() {
    string acc;
    Tree<T>* currentTree = NULL;
    while(true){
        cout<<"Podaj komende\n";
        std::getline(std::cin, acc);
        if(acc.find("enter") != std::string::npos) {
            string s = acc.substr(5,acc.length()-5);
            currentTree = new Tree<T>(s);
        }else if (currentTree == NULL) {
            cout << "nie ma zaladowanego drzewa\n";
        }
        else if(acc.find("print") != std::string::npos){
            currentTree->preorderPrint();
        }else if(acc.find("vars") != std::string::npos){
            currentTree->printVars();
        }else if(acc.find("comp") != std::string::npos){
            int* currentIndex = new int(4);
            ArrayList<string> parameterSet;
            if(currentTree->getType() == 1) {
                while (*currentIndex < acc.length()) {
                    while (*currentIndex < acc.length() - 1 &&
                           acc[*currentIndex] < 47 || acc[*currentIndex] > 58)
                        (*currentIndex)++;
                    int startIndex = *currentIndex;
                    while (*currentIndex < acc.length() - 1 &&
                           acc[*currentIndex + 1] > 47 && acc[*currentIndex + 1] < 58)
                        (*currentIndex)++;
                    parameterSet.add(*new string(acc.substr(startIndex, *currentIndex - startIndex + 1)));
                    (*currentIndex)++;
                }
            }else if(currentTree->getType() == 2) {

                while (*currentIndex < acc.length()) {
                    int pointFlag = -1;
                    while (*currentIndex < acc.length() - 1 &&
                           acc[*currentIndex] < 47 || acc[*currentIndex] > 58){
                        (*currentIndex)++;
                    }
                    int startIndex = *currentIndex;
                    while (*currentIndex < acc.length() - 1 &&
                           acc[*currentIndex] > 47 && acc[*currentIndex] < 58) {
                        (*currentIndex)++;
                        if (acc[*currentIndex]=='.' && pointFlag == -1)
                            pointFlag = (*currentIndex)++;
                    }
                    if(acc[*currentIndex]!='.')
                        parameterSet.add(*new string(acc.substr(startIndex, *currentIndex - startIndex)));
                    (*currentIndex)++;
                }
            }else if(currentTree->getType() == 3) {

                while (*currentIndex < acc.length()) {
                    while (*currentIndex < acc.length() - 1 &&
                            acc[*currentIndex] != '\''){
                        (*currentIndex)++;
                    }
                    int startIndex = (*currentIndex)++;
                    while (*currentIndex < acc.length() &&
                            acc[*currentIndex] != '\'') {
                        (*currentIndex)++;
                    }
                    if(acc[*currentIndex]=='\'')
                        parameterSet.add(*new string(acc.substr(startIndex, *currentIndex - startIndex)));
                    (*currentIndex)++;
                }
            }
            delete currentIndex;
            string value = currentTree->computeForSetParameters(parameterSet);
            cout<<"Wyliczono: "<<value<<" moj panie!\n";
        }else if(acc.find("join") != std::string::npos){
            string s = acc.substr(4,acc.length()-4);
            currentTree->joinTreeWithThis(s);
            cout << "Polaczone drzewo:\n";
            currentTree->preorderPrint();
            currentTree->printVars();
        }
        else if(acc.find("exit") != std::string::npos)
            break;

    }
}


#endif //ZAD3_V2_CONSOLEINTERFACE_H
