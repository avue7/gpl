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
    string get_base_type();
    bool is_array(); 

    Symbol(string name, Gpl_type type, int value);
    Symbol(string name, Gpl_type type, double value);
    Symbol(string name, Gpl_type type, string value);
    void print();

    /* If you want to use the below constructor instead
       then you must make the values point to a void. 
       From gpl.y grammer rules, you can dynamically allocate
       memory for each value type. */
    // Symbol(string name, Gpl_type type, void *value);
};

#endif
