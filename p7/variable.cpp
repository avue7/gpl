#include "variable.h"
#include "expression.h"
#include "symbol.h"
#include "symbol_table.h"

Variable::Variable(string symbol_name)
{
  // DUMMY
  if (symbol_name == "DUMMY")
  {
    m_symbol = new Symbol("DUMMY", INT, 0);
    Symbol_table::instance()->insert_symbol(m_symbol);
    Symbol_table::instance()->lookup("DUMMY");
    m_type = INT;
    m_expr = NULL;
    m_var_type = "DUMMY";
  }
  else
  {
    // Look for the symbol in the symbol table
    // store it in m_symbol
    m_symbol = Symbol_table::instance()->lookup(symbol_name);
    m_type = m_symbol->m_type;
    m_expr = NULL;
    m_var_type = "CONSTANT";
  }
}

Variable::Variable(string symbol_name, Expression *expression)
{
  m_symbol = Symbol_table::instance()->lookup(symbol_name);
  m_type = m_symbol->m_type;
  m_expr = expression;
  m_var_type = "EXPRESSION";
}

Variable::Variable(string symbol_name, string param)
{
  m_symbol = Symbol_table::instance()->lookup(symbol_name);
  ((Game_object*)(m_symbol->m_value))->get_member_variable_type(param, m_type);
  m_expr = NULL;
  m_var_type = "GAME_OBJECT";
  m_param = param;
}

Variable::Variable(string symbol_name, string param, int array_index)
{
  m_symbol = Symbol_table::instance()->lookup(symbol_name);
  m_expr = NULL;
  m_var_type = "GAME_OBJECT_ARRAY";
  if (m_symbol->m_type == TRIANGLE_ARRAY)
  {
    ((Game_object*)((Triangle**)(m_symbol->m_value))
      [array_index])->get_member_variable_type(param, m_type);
     m_param = param;
     m_array_index = array_index; 
  }
  else if (m_symbol->m_type == RECTANGLE_ARRAY)
  {
    ((Game_object*)((Rectangle**)(m_symbol->m_value))
      [array_index])->get_member_variable_type(param, m_type);
     m_param = param;
     m_array_index = array_index; 
  }
  else if (m_symbol->m_type == CIRCLE_ARRAY)
  {
    ((Game_object*)((Circle**)(m_symbol->m_value))
      [array_index])->get_member_variable_type(param, m_type);
     m_param = param;
     m_array_index = array_index; 
  }
  else if (m_symbol->m_type == TEXTBOX_ARRAY)
  {
    ((Game_object*)((Textbox**)(m_symbol->m_value))
      [array_index])->get_member_variable_type(param, m_type);
     m_param = param;
     m_array_index = array_index; 
  }
  else if (m_symbol->m_type == PIXMAP_ARRAY)
  {
    ((Game_object*)((Pixmap**)(m_symbol->m_value))
      [array_index])->get_member_variable_type(param, m_type);
     m_param = param;
     m_array_index = array_index; 
  }
  else
  {
    cerr << "Trouble in Variable.cpp constr for game_object_array!" << endl;
  }
}

int Variable::get_int_value()
{
  if (m_var_type == "DUMMY")
  {
    int value = 0;
    return value;
  }
  if (m_var_type == "EXPRESSION")
  {
    int value;
    value = ((int*)m_symbol->m_value)[m_expr->eval_int()];
    return value;
  }
  else if (m_var_type == "GAME_OBJECT")
  {
    int ret_value;
    Game_object* temp_obj;
    temp_obj = (Game_object*)(m_symbol->m_value);
    temp_obj->get_member_variable(this->m_param, ret_value);
    return ret_value;
  }
  else if (m_var_type == "GAME_OBJECT_ARRAY")
  {
    int ret_value;
    Game_object* temp_obj;
    if (m_symbol->m_type == TRIANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Triangle**)
                  (m_symbol->m_value))[m_array_index];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == RECTANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Rectangle**)
                  (m_symbol->m_value))[m_array_index];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == PIXMAP_ARRAY)
    {
      temp_obj = (Game_object*)((Pixmap**)
                  (m_symbol->m_value))[m_array_index];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == TEXTBOX_ARRAY)
    {
      temp_obj = (Game_object*)((Textbox**)
                  (m_symbol->m_value))[m_array_index];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == CIRCLE_ARRAY)
    {
      temp_obj = (Game_object*)((Circle**)
                  (m_symbol->m_value))[m_array_index];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else
    {
      cerr << "Trouble in Var::get_int_value for object_array!" << endl;
    }
  }
  void *temp;
  int value;
  temp = m_symbol->m_value;
  value = *(int*)temp;
  return value;
}

double Variable::get_double_value()
{
  if (m_type == INT_ARRAY)
  {    
    int value;
    double d_value;
    value = get_int_value();
    d_value = (double)value;
    return d_value;
  }
  if (m_type == DOUBLE_ARRAY)
  {
    int value;
    double d_value;
    value = get_int_value();
    d_value = (double)value;
    return d_value;
  }
  if (m_var_type == "GAME_OBJECT")
  {
    double ret_value;
    Game_object* temp_obj;
    temp_obj = (Game_object*)(m_symbol->m_value);
    temp_obj->get_member_variable(this->m_param, ret_value);
    return ret_value;
  }
  void *temp;
  double value;
  temp = m_symbol->m_value;
  value = *(double*)temp;
  return value;
/*  else
  {
    cerr << "I should never print unless something went wrong. ";
    cerr << "I am printing from get_double_value() in Variable.cpp." << endl;
    return 1.0;
  }*/
}

string Variable::get_string_value()
{
  void *temp;
  stringstream ss;
  string s_value;
  if (m_type == INT_ARRAY)
  {
    int value = get_int_value();
    ss << value;
    ss >> s_value;
    return s_value;
  }
  if (m_type == DOUBLE_ARRAY)
  {
    double value = get_double_value();
    ss << value;
    ss >> s_value;
    return s_value;
  }
  if (m_var_type == "GAME_OBJECT")
  {
    string ret_value;
    Game_object* temp_obj;
    temp_obj = (Game_object*)(m_symbol->m_value);
    temp_obj->get_member_variable(this->m_param, ret_value);
    return ret_value;
  }
//  cerr << "THIS PRINT INSIDE OF STRING IN VAR.CPP" << endl;
  string value;
  temp = m_symbol->m_value;
  value = *(string*)temp;
  return value;
}
 
Animation_block *Variable::get_animation_block()
{
  if (m_type == ANIMATION_BLOCK)
  {
    return m_symbol->get_animation_block();
  }
}

// Added in p7
void Variable::set_new_value(int new_value)
{
  if (m_var_type == "CONSTANT")
  {
    m_symbol->m_value = (void*) new int(new_value);
  }
}
