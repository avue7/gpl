#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>
#include "gpl_type.h"
using namespace std;

class Symbol; // Class forwarding
class Expression; // Class forwarding

class Variable
{
  public:
    // Member variables 
    Gpl_type m_type;
    Expression *m_expr; // Pointer to class
    Symbol *m_symbol;   // Pointer to class
    string m_var_type;    

    // Member functions
    string get_type();
    int get_int_value();
    double get_double_value();
    string get_string_value();
    
    // Constructors 
    Variable(string symbol_name);
    Variable(string symbol_name, Expression *expr);
};

#endif
