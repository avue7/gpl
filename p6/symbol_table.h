#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include "gpl_type.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "game_object.h"
#include "error.h"
using namespace std;

class Symbol_table
{
  public:
    static Symbol_table *instance();
    Symbol *lookup(string name);
    void insert_symbol(Symbol *symbol); // Making this function to add symbols
    void print(ostream &os);
    static bool compare_symbols(Symbol *a, Symbol *b);
    unordered_map<string, Symbol*> m_map;   
 
  private:
    static Symbol_table *m_instance;
    Symbol_table() {};
    Symbol_table(const Symbol_table &);
    const Symbol_table &operator=(const Symbol_table &);

};

#endif
