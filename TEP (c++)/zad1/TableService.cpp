//
// Created by Hyperbook on 11.10.2023.
//

#include <iostream>
#include "TableService.h"
void TableService::vAllocTableFill34(int iSize) {
    if (iSize < 0) return;

    int *array = new int[iSize];
    for (int i = 0; i < iSize; ++i)
        array[i] = 34;

    for (int i = 0; i < iSize; ++i)
        std::cout << array[i] << ", ";

    std::cout << std::endl;
    delete[] array;
}

bool TableService::bAllocTable2Dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 0 || iSizeY < 0)
        return false;

    *piTable = new int *[iSizeX];
    for (int i = 0; i < iSizeX; ++i) {
        (*piTable)[i] = new int[iSizeY];
    }
    return true;
}

bool TableService::bDeallocTable2Dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 0 || iSizeY < 0)
        return false;

    for (int i = 0; i < iSizeX; ++i) {
        delete[] (*piTable)[i];
    }
    delete[] *piTable;
    return true;
}

void TableService::vModTab(CTable *pcTab, int iNewSize) {
    (*pcTab).setNewSize(iNewSize);
}

void TableService::vModTab(CTable cTab, int iNewSize) {
    cTab.setNewSize(iNewSize);
}
