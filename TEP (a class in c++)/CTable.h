//
// Created by LEGION on 08.10.2023.
//

#ifndef TEP__A_CLASS_IN_C____CTABLE_H
#define TEP__A_CLASS_IN_C____CTABLE_H

#include <string>
#include <iostream>

class CTable {

    private:
        std::string t_name;
        int* t_pointer;
        int t_len;
    public:
        CTable(){
            this->t_name = "name";
            this->t_len = 10;
            t_pointer = new int[t_len];
            std::cout<<"bezp: "<<t_name;
        }
        CTable(std::string t_name, int t_len){
            this->t_name = t_name;
            this->t_len = t_len;
            t_pointer = new int[t_len];
            std::cout<<"parametr: "<<t_name;
        }
        CTable(CTable const &to_be_cloned){
            this->t_name = to_be_cloned.t_name+".copy";
            this->t_len = to_be_cloned.t_len;
            t_pointer = new int[t_len];
            for (int i = 0; i < t_len; ++i)
                t_pointer[i] = to_be_cloned.t_pointer[i];
        }
        ~CTable(){
            delete[] t_pointer;
            std::cout << "usuwanko";
        }
        void setNewSize(int new_size){
            int* temp_table = new int[new_size];
            for (int i = 0; i < t_len; ++i)
                temp_table[i] = t_pointer[i];

            delete[] t_pointer;
            t_pointer = temp_table;
        }
        CTable* CTClone(){
            return new CTable(*this);
        }
};


#endif //TEP__A_CLASS_IN_C____CTABLE_H
