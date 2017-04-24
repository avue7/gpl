#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>
#include "gpl_type.h"
#include "game_object.h"
#include "expression.h"
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
    bool is_array();
    bool is_game_object(); 

    Symbol(string name, Gpl_type type, int value);
    Symbol(string name, Gpl_type type, double value);
    Symbol(string name, Gpl_type type, string value);
    Symbol(string name, Game_object* value);
    void print();
   
    /* Get and set functions */
    int get_int_value();
    string get_name(); 
    Gpl_type get_type();
    string get_base_type();
    double get_double_value();
    string get_string_value();
    Game_object *get_game_object_value();
    void set(int value);
   
    /* If you want to use the below constructor instead
       then you must make the values point to a void. 
       From gpl.y grammer rules, you can dynamically allocate
       memory for each value type. */
    // Symbol(string name, Gpl_type type, void *value);
};

#endif
