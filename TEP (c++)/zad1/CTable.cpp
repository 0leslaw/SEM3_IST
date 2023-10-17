//
// Created by Hyperbook on 11.10.2023.
//
#include <iostream>
#include "CTable.h"
CTable::CTable() {
    this->tName = "name";
    this->tLen = 10;
    tPointer = new int[tLen];
    std::cout << "wywolanie bezpiecznego konstruktora: " << tName << endl;
}

CTable::CTable(std::string tName, int tLen) {
    this->tName = tName;
    this->tLen = tLen;
    tPointer = new int[tLen];
    std::cout << "wywolanie konstruktora z parametrem: " << tName << endl;
}

CTable::CTable(const CTable &toBeCloned) {
    this->tName = toBeCloned.tName + ".copy";
    this->tLen = toBeCloned.tLen;
    tPointer = new int[tLen];
    for (int i = 0; i < tLen; ++i)
        tPointer[i] = toBeCloned.tPointer[i];

    std::cout << "skopiowano CTable o nazwie: " + tName << endl;
}

CTable::~CTable() {
    delete[] tPointer;
    std::cout << "usunieto CTable o nazwie: " + tName << endl;
}

void CTable::setNewSize(int newSize) {
    if (newSize < 0)
        return;

    int *tempTable = new int[newSize];
    int min = newSize;
    if (newSize > tLen)
        min = tLen;
    for (int i = 0;i < min; ++i)
        tempTable[i] = tPointer[i];

    delete[] tPointer;
    tPointer = tempTable;
    tLen = newSize;
}

CTable *CTable::CTClone() {
    return new CTable(*this);
}

const string &CTable::getTName() const {
    return tName;
}

void CTable::setTName(const string &tName) {
    this->tName = tName;
}

int *CTable::getTPointer() const {
    return tPointer;
}

void CTable::setTPointer(int *tPointer) {
    this->tPointer = tPointer;
}

int CTable::getTLen() const {
    return tLen;
}

void CTable::setTLen(int tLen) {
    this->tLen = tLen;
}

