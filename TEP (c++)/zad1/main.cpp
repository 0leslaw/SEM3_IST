#include <iostream>
#include "CTable.h"
#include "TableService.h"


int main() {
    // testowanie utworzenia tablicy z wart 34
    TableService::vAllocTableFill34(10);

    // Testowanie alokacji tablicy
    int** piTable;

    TableService::bAllocTable2Dim(&piTable, 3, 3);
    piTable[0][0]=23;

        cout << piTable[0][0] << endl;

    // dealokacja
    TableService::bDeallocTable2Dim(&piTable, 3, 3);

    CTable tabStatic;

        cout << "nazwa statycznej tabeli przed zmiana: " + tabStatic.getTName() << endl;

    tabStatic.setTName("stack_static");
    CTable tabStaticCopy(tabStatic);

        cout << "nazwa kopii statycznej tabeli po zmianie: " + tabStaticCopy.getTName() << endl;

    /*
    * spróbujemy zmienić wielkość statycznej tablicy
    * nie uda nam się to ponieważ na wejściu do funkcji zostanie wygenerowana
    * tymczasowa kopia w zakresie fukncji (zobaczymy to w konsoli gdy wydrukuje się "skopiowano..."
    *
    * natomiast inaczej będzie gdy przekażemy wskaźnik na tablicę, wtedy treść wskaźnika zostanie skopiowana
    * jednak to nie będzie dla nas problemem, gdyż treść kopii będzie nadal posiadała adres pierwszego
    * elementu tablicy, co za tym idzie zmodyfikujemy pożądaną lokalizację w pamięci
    * */
    CTable* dynamicTable = new CTable("dynamic_table", 10);

        cout << "wywolujemy funkcje dla statycznej tablicy\nstany tablic: " << endl;

    TableService::vModTab(tabStatic, 6);

        cout << tabStatic.getTName() << " " << tabStatic.getTLen() << endl <<
        (*dynamicTable).getTName() << " " << (*dynamicTable).getTLen() << endl;

        cout << "wywolujemy funkcje dla dynamicznej tablicy\nstany tablic: " << endl;

    TableService::vModTab(dynamicTable, 6);

        cout << tabStatic.getTName() << " " << tabStatic.getTLen() << endl <<
        (*dynamicTable).getTName() << " " << (*dynamicTable).getTLen() << endl;

    /*
    * co ciekawe moglibyśmy stworzyć wskaźnik na tablicę statyczną i wtedy nasza funkcja zadziała
    * zobaczmy w praktyce
    */

    CTable* pointerToStaticTable = &tabStatic;
    TableService::vModTab(pointerToStaticTable,6);

        cout << "wywolujemy funkcje dla pointera na statyczną tablicę\nstany tablic: " << endl;

    TableService::vModTab(dynamicTable, 6); // To zmodyfikuje oryginalny obiekt

        cout << tabStatic.getTName() << " " << tabStatic.getTLen() << endl <<
        (*dynamicTable).getTName() << " " << (*dynamicTable).getTLen() << endl;

    delete dynamicTable; // Usunięcie obiektu dynamicznego
    return 0;

}