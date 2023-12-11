//
// Created by Hyperbook on 26.11.2023.
//

#include <iostream>
#include <cstdlib>
#include "ConsoleInterface.h"
#include "Tree.h"

using namespace std;
ConsoleInterface::ConsoleInterface() {

}

void ConsoleInterface::run() {
    string acc;
    Tree* currentTree = NULL;
    while(true){
        cout<<"Podaj komende\n";
        std::getline(std::cin, acc);
        if(acc.find("enter") != std::string::npos) {
            string s = acc.substr(5,acc.length()-5);
            currentTree = new Tree(s);
        }else if (currentTree == NULL) {
            cout << "nie ma zaladowanego drzewa\n";
        }
        else if(acc.find("print") != std::string::npos){
            currentTree->preorderPrint();
        }else if(acc.find("vars") != std::string::npos){
            currentTree->printVars();
        }else if(acc.find("comp") != std::string::npos){
            int* currentIndex = new int(4);
            ArrayList<int> parameterSet;
            while (*currentIndex < acc.length()){
                while (*currentIndex < acc.length()-1 &&
                acc[*currentIndex] < 47 || acc[*currentIndex] > 58)
                    (*currentIndex)++;
                int startIndex = *currentIndex;
                while (*currentIndex < acc.length()-1 &&
                acc[*currentIndex+1] > 47 && acc[*currentIndex+1] < 58)
                    (*currentIndex)++;
                parameterSet.add(*new int(std::atoi((acc.substr(startIndex,*currentIndex - startIndex + 1)).c_str())));
                (*currentIndex)++;
            }
            delete currentIndex;
            double value = currentTree->computeForSetParameters(parameterSet);
            cout<<"Wyliczono: "<<value<<" moj panie!\n";
        }else if(acc.find("join") != std::string::npos){
            string s = acc.substr(4,acc.length()-4);
            currentTree->joinTreeWithThis(s);
            cout << "Polaczone drzewo:\n";
            currentTree->preorderPrint();
            currentTree->printVars();
        }

    }
}
