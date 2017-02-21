#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>
#include "gpl_type.h"

/* We need the symbol class to store
   string name,
   Gpl_type type,
   void* value.
*/
class Symbol
{
  public:
    std::string name;
    Gpl_type type;
    void* value;
    
    // Make this constructor first and test it. 
    Symbol(std::string m_name, Gpl_type m_type, void* m_value);
};

#endif
