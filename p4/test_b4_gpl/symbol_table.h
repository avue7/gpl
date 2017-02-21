#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include "gpl_type.h"
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Symbol_table
{
  public:
    static Symbol_table *instance();
    Symbol *lookup(string name);
    void add_symbol(Symbol *symbol); // Making this function to add symbols
    void print(ostream &os);
    bool compare_symbols(Symbol *a, Symbol *b);
    unordered_map<string, Symbol*> m_map;   
 
  private:
    static Symbol_table *m_instance;
    int m_id;
    Symbol_table() {};
    Symbol_table(const Symbol_table &);
    const Symbol_table &operator=(const Symbol_table &);

};

#endif
