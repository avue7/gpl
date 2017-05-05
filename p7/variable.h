#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>
#include "gpl_type.h"
#include "error.h"
#include "animation_block.h"
#include "symbol.h"

using namespace std;

//class Symbol; // Class forwarding
class Expression; // Class forwarding

class Variable
{
  public:
    // Member variables 
    Gpl_type m_type;
    Expression *m_expr; // Pointer to class
    Symbol *m_symbol;   // Pointer to class
    string m_var_type;
    string m_param;    

    // Member functions
    string get_type();
    int get_int_value();
    double get_double_value();
    string get_string_value();
    Animation_block * get_animation_block();

    //Added in p7.. Must create for assignment->execute() in 
    // assignment class to work. 
    void set_new_value(void* new_value);
    void set_game_object_value(void* value);
    
    // Constructors 
    Variable(string symbol_name);
    Variable(string symbol_name, Expression *expr);
    Variable(string symbol_name, string param);
    Variable(string symbol_name, string param, Expression *p_expr);
};

#endif
