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

Variable::Variable(string symbol_name, string param, Expression* p_expr)
{
  m_symbol = Symbol_table::instance()->lookup(symbol_name);
  m_var_type = "GAME_OBJECT_ARRAY";
  m_expr = p_expr;
  m_param = param;
  m_type = p_expr->m_type;
}

int Variable::get_int_value()
{
  cerr << " VARIABLE.CPP : m_var_TYPE : " << m_var_type << endl;
  if (m_var_type == "DUMMY")
  {
    int value = 0;
    return value;
  }
  if (m_var_type == "CONSTANT")
  {
    cerr << "THIS RAN IN CONSANT 65 var.cpp" << endl;
    return *(int*) m_symbol->m_value;
  } 
  else if (m_var_type == "EXPRESSION")
  {
    cerr << "M_type in variable is " << m_type << endl;
    if (m_type == INT_ARRAY)
    { 
      int value;
      value = ((int*)m_symbol->m_value)[m_expr->eval_int()];
      return value;
    }
    else if (m_type == CIRCLE_ARRAY)
    {
       cerr << "INDEED IT IS A CIRCLE_ARRAY" << endl;
    }
    else
    {
      cerr << "Error: cannot find array_type: var.cpp:line 109." << endl;
    }
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
    cerr << "this printed in var.cpp get_int_value" << endl;
    int ret_value;
    Game_object* temp_obj;
    if (m_symbol->m_type == TRIANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Triangle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == RECTANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Rectangle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == PIXMAP_ARRAY)
    {
      temp_obj = (Game_object*)((Pixmap**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == TEXTBOX_ARRAY)
    {
      temp_obj = (Game_object*)((Textbox**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == CIRCLE_ARRAY)
    {
      temp_obj = (Game_object*)((Circle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else
    {
      cerr << "Trouble in Var::get_int_value for object_array!" << endl;
    }
  }
}

double Variable::get_double_value()
{
  if (m_var_type == "EXPRESSION")
  {
    double value;
    value = ((double*)m_symbol->m_value)[m_expr->eval_int()];
    return value;
  }
  else if (m_var_type == "GAME_OBJECT")
  {
    double ret_value;
    Game_object* temp_obj;
    temp_obj = (Game_object*)(m_symbol->m_value);
    temp_obj->get_member_variable(this->m_param, ret_value);
    return ret_value;
  }
  else if (m_var_type == "CONSTANT")
  {
    void *temp;
    double value;
    temp = m_symbol->m_value;
    value = *(double*)temp;
    return value;
  }
  else
  {
    cerr << "ERROR::VAR.CPP(line:207): cannot find m_var_type";
    cerr << " for get_double_value!" << endl;
  }
}

string Variable::get_string_value()
{

  cerr << " THIS RAN IN GET STRING VAL OF VAR>CPP " << endl;
  void *temp;
  stringstream ss;
  string s_value;
  if (m_var_type == "EXPRESSION")
  {
    if (m_expr->m_type == INT && m_type == INT)
    {
      cerr << "------I AM AN INT ! var.cpp(222) " << endl;
      int int_value;
      stringstream ss;
      string s_value;
      int_value = m_expr->eval_int();
      ss << int_value;
      ss >> s_value;
      return s_value;
    }
    else if (m_type == INT_ARRAY)
    {
      int int_value;
      stringstream ss;
      string s_value;
      int_value = ((int*)m_symbol->m_value)[m_expr->eval_int()];
      ss << int_value;
      ss >> s_value;
      return s_value;
    }
    else if (m_type == DOUBLE_ARRAY)
    {
      double d_value;
      stringstream ss;
      string s_value;
      d_value = ((double*)m_symbol->m_value)[m_expr->eval_int()];
      ss << d_value;
      ss >> s_value;
      return s_value;
    }
    else if (m_type == STRING_ARRAY)
    {
      return ((string*)m_symbol->m_value)[m_expr->eval_int()];
    }
    else 
    {
      cerr << "ERROR::Var.cpp(line:218): I cant find type!" << endl;
      cerr << "----EXPR Type should be: " << m_expr->m_type << endl;
      cerr << "----Var type should be: " << this->m_type << endl;
    }
  }
  else if (m_var_type == "GAME_OBJECT")
  {
    string ret_value;
    Game_object* temp_obj;
    temp_obj = (Game_object*)(m_symbol->m_value);
    temp_obj->get_member_variable(this->m_param, ret_value);
    return ret_value;
  }
  else if (m_var_type == "GAME_OBJECT_ARRAY")
  {
    cerr << "  THIS RAN IN GAME_OBJECT _ARRAY" << endl;
    string ret_value;
    Game_object* temp_obj;
    if (m_symbol->m_type == TRIANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Triangle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == RECTANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Rectangle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      cerr << "---247: m_expr->eval_int is : " << m_expr->eval_int() << endl;
      Status status;
      status = temp_obj->get_member_variable(this->m_param, ret_value);
      cerr << " ---- status " << status_to_string(status) << endl;
      return ret_value;
    }
    else if (m_symbol->m_type == PIXMAP_ARRAY)
    {
      temp_obj = (Game_object*)((Pixmap**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == TEXTBOX_ARRAY)
    {
      temp_obj = (Game_object*)((Textbox**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == CIRCLE_ARRAY)
    {
      cerr << "     VAR:296 YES I AM A CIRCLE ARRAY " << endl;
      temp_obj = (Game_object*)((Circle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      temp_obj->get_member_variable(this->m_param, ret_value);
      cerr << " THE VALUE FOR CIRCLE ARRAY IS : " << ret_value << endl;
      return ret_value;
    }
    else
    {
      cerr << "Trouble in Var::get_int_value for object_array!" << endl;
    }
  }
  else if (m_var_type == "CONSTANT")
  {
    cerr << "THIS PRINT INSIDE OF STRING IN VAR.CPP" << endl;
    string value;
    temp = m_symbol->m_value;
    value = *(string*)temp;
    return value;
  }
  else 
  {
    cerr << "ERROR::VAR.CPP(line:260): cannot find m_var_type!" << endl;
  }
}
 
Animation_block *Variable::get_animation_block()
{
  if (m_type == ANIMATION_BLOCK)
  {
    return m_symbol->get_animation_block();
  }
  else 
  {
    cerr << "ERROR:VAR(256): M_TYPE == ANIMATION_BLOCK?" << endl;
  }
}

// Added in p7
void Variable::set_new_value(void* new_value)
{
  if (m_var_type == "CONSTANT")
  { 
    cerr << "VAR.CPP:274: set value in set_new Value ks " << *(int*) new_value << endl;    
    m_symbol->m_value = new_value;
  }
  else if (m_var_type == "EXPRESSION")
  {
     // Arrays
     if (m_symbol->m_type == INT_ARRAY)
     {
       ((int*)m_symbol->m_value)[m_expr->eval_int()] = *(int*) new_value;
     }
     else if (m_symbol->m_type == DOUBLE_ARRAY)
     {
       ((double*)m_symbol->m_value)[m_expr->eval_int()] = *(double*) new_value;
     }
     else if (m_symbol->m_type == STRING_ARRAY)
     {
       ((string*)m_symbol->m_value)[m_expr->eval_int()] = *(string*) new_value;
     }
     else
     {
        cerr << "ERROR: VAR(281): CANNOT FIND TYPE!" << endl;
     }
  }
  else if (m_var_type == "GAME_OBJECT_ARRAY")
  {
    Game_object* temp_obj;
    if (m_symbol->m_type == TRIANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Triangle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
    }
    else if (m_symbol->m_type == RECTANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Rectangle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
    }
    else if (m_symbol->m_type == PIXMAP_ARRAY)
    {
      temp_obj = (Game_object*)((Pixmap**)
                  (m_symbol->m_value))[m_expr->eval_int()];
    }
    else if (m_symbol->m_type == TEXTBOX_ARRAY)
    {
      temp_obj = (Game_object*)((Textbox**)
                  (m_symbol->m_value))[m_expr->eval_int()];
    }
    else if (m_symbol->m_type == CIRCLE_ARRAY)
    {
      temp_obj = (Game_object*)((Circle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
    }
    else
    {
      cerr << "Trouble in Var::set_new_value for object_array!" << endl;
    }
    temp_obj->set_member_variable(this->m_param, *(int*) new_value); 
  }
  else 
  {
     cerr << "Error: cannot find m_var_type in var::set_new_value!" << endl;
  }
}

