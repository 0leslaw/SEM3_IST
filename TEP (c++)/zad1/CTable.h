//
// Created by Hyperbook on 11.10.2023.
//

#ifndef ZAD1_1_1_CTABLE_H
#define ZAD1_1_1_CTABLE_H
using namespace std;

class CTable {
    private:
        std::string tName;
        int* tPointer;
        int tLen;
    public:
        CTable();

        CTable(std::string tName, int tLen);

        CTable(CTable const &toBeCloned);

        ~CTable();

        void setNewSize(int newSize);

        CTable* CTClone();

        const string &getTName() const;

        void setTName(const string &tName);

        int *getTPointer() const;

        void setTPointer(int *tPointer);

        int getTLen() const;

        void setTLen(int tLen);

};


#endif //ZAD1_1_1_CTABLE_H
