//
// Created by Hyperbook on 11.10.2023.
//

#ifndef ZAD1_1_1_TABLESERVICE_H
#define ZAD1_1_1_TABLESERVICE_H


#include "CTable.h"

class TableService {
public:
    static void vAllocTableFill34(int iSize);
    static bool bAllocTable2Dim(int ***piTable, int iSizeX, int iSizeY);
    static bool bDeallocTable2Dim(int ***piTable, int iSizeX, int iSizeY);
    static void vModTab(CTable *pcTab, int iNewSize);
    static void vModTab(CTable cTab, int iNewSize);
};


#endif //ZAD1_1_1_TABLESERVICE_H
