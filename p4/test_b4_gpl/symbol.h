#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>
#include "gpl_type.h"
using namespace std;

/* We need the symbol class to store
   string name,
   Gpl_type type,
   void* value.
*/
class Symbol
{
  public:
    string m_name;
    Gpl_type m_type;
    void* m_value;
    int m_size;
    string get_name(); 
    string get_type(); 
    // Make this constructor first and test it. 
    Symbol(string name, Gpl_type type, int value);
    Symbol(string name, Gpl_type type, double value);
    Symbol(string name, Gpl_type type, string value);
    Symbol(string name, Gpl_type type, int value, int size);
    void print();
};

#endif
