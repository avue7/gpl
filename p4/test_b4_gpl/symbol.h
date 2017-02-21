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
    
    // Make this constructor first and test it. 
    Symbol(string name, Gpl_type type, void* value);
    void print();
};

#endif