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
    m_symbol = Symbol_table::instance()->lookup(symbol_name);
    m_type = m_symbol->m_type;
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
  Status status;
  Game_object* temp_obj = NULL;
  if (m_symbol->m_size < m_expr->eval_int())
  {
    if (m_symbol->m_type == TRIANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Triangle**)(m_symbol->m_value))[0];
    }
    else if (m_symbol->m_type == RECTANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Rectangle**)(m_symbol->m_value))[0];
    }
    else if (m_symbol->m_type == PIXMAP_ARRAY)
    {
      temp_obj = (Game_object*)((Pixmap**)(m_symbol->m_value))[0];
    }
    else if (m_symbol->m_type == TEXTBOX_ARRAY)
    {
      temp_obj = (Game_object*)((Textbox**)(m_symbol->m_value))[0];
    }
    else if (m_symbol->m_type == CIRCLE_ARRAY)
    {
      temp_obj = (Game_object*)((Circle**)(m_symbol->m_value))[0];
    }
    else
    {
      cerr << "Trouble in Var::getting member type in constructor!" << endl;
    }
    status = temp_obj->get_member_variable_type(m_param, this->m_type);
  }
  else   // Array not out of index for assignment
  {
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
      cerr << "Trouble in Var:: cannot find member type for constructor!" << endl;
    }
    status = temp_obj->get_member_variable_type(m_param, this->m_type);
    //cerr << "VAR:11: STATUS IS :" << status_to_string(status) << endl;
  }
  if (status != OK)
  {
    cerr << "ERROR::VAR.CPP(114): cannot get member variable type!" << endl;
    cerr << "---Error returned: " << status_to_string(status) << endl;
  }
}

/*################################################################*/
/*                     GETTER FUNCTIONS BEGINS                    */
/*################################################################*/
int Variable::get_int_value()
{
  //cerr << " VARIABLE.CPP : m_var_TYPE : " << m_var_type << endl;
  Status status;
  if (m_var_type == "DUMMY")
  {
    int value = 0;
    return value;
  }
  if (m_var_type == "CONSTANT")
  {
    return *(int*) m_symbol->m_value;
  } 
  else if (m_var_type == "EXPRESSION")
  {
    if (m_type == INT_ARRAY)
    { 
      int value;
      value = ((int*)m_symbol->m_value)[m_expr->eval_int()];
      return value;
    }
    else
    {
      cerr << "Error: cannot find array_type: var.cpp:line 109." << endl;
      return -1;
    }
  }
  else if (m_var_type == "GAME_OBJECT")
  {
    int ret_value;
    Game_object* temp_obj;
    temp_obj = (Game_object*)(m_symbol->m_value);
    status = temp_obj->get_member_variable(this->m_param, ret_value);
    if (status != OK)
    {
      cerr << "ERROR::VAR.CPP(158): while getting member";
      cerr << " variable in get_int_value()!" << endl;
      cerr << "---STATUS RETURNED: " << status_to_string(status) << endl;
      return -1;
    }
    return ret_value;
  }
  else if (m_var_type == "GAME_OBJECT_ARRAY")
  {
    //cerr << "this printed in var.cpp get_int_value" << endl;
    int ret_value;
    Game_object* temp_obj = NULL;
    if (m_symbol->m_type == TRIANGLE_ARRAY)
    {
      (Game_object*)((Triangle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      status = temp_obj->get_member_variable(m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == RECTANGLE_ARRAY)
    {
      temp_obj = (Game_object*)((Rectangle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      status = temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == PIXMAP_ARRAY)
    {
      temp_obj = (Game_object*)((Pixmap**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      status = temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == TEXTBOX_ARRAY)
    {
      temp_obj = (Game_object*)((Textbox**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      status = temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else if (m_symbol->m_type == CIRCLE_ARRAY)
    {
      temp_obj = (Game_object*)((Circle**)
                  (m_symbol->m_value))[m_expr->eval_int()];
      status = temp_obj->get_member_variable(this->m_param, ret_value);
      return ret_value;
    }
    else
    {
      cerr << "Trouble in Var::get_int_value for object_array!" << endl;
      return -1;
    }

    if (status != OK)
    {
      cerr << "ERROR::VAR.CPP(158): while getting member";
      cerr << " variable in get_int_value()!" << endl;
      cerr << "---STATUS RETURNED: " << status_to_string(status) << endl;
      return -1;
    }
  }
  else
  {
    cerr << "ERROR::VAR.CPP(198) cannot find m_var_type!" << endl;
    return -1;
  }
}

double Variable::get_double_value()
{
  if (m_var_type == "CONSTANT")
  {
    void *temp;
    double value;
    temp = m_symbol->m_value;
    value = *(double*)temp;
    return value;
  }
  else if (m_var_type == "EXPRESSION")
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
  else if (m_var_type == "GAME_OBJECT_ARRAY")
  {
    //cerr << "this printed in var.cpp get_int_value" << endl;
    double ret_value;
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
      cerr << "Trouble in Var::cannot find m_type for object_array!" << endl;
      return -1;
    }
  }
  else
  {
    cerr << "ERROR::VAR.CPP(line:190): cannot find m_var_type";
    cerr << " for get_double_value!" << endl;
    return -1;
  }
}

string Variable::get_string_value()
{
  //cerr << " THIS RAN IN GET STRING VAL OF VAR>CPP " << endl;
  void *temp;
  stringstream ss;
  string s_value;
  if (m_var_type == "CONSTANT")
  {
    string value;
    temp = m_symbol->m_value;
    value = *(string*)temp;
    return value;
  }
  else if (m_var_type == "EXPRESSION")
  {
    if (m_expr->m_type == INT && m_type == INT)
    {
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
      return "-1";
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
    //cerr << "  THIS RAN IN GAME_OBJECT _ARRAY" << endl;
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
      //cerr << "---247: m_expr->eval_int is : " << m_expr->eval_int() << endl;
      //Status status;
      /*status = */temp_obj->get_member_variable(this->m_param, ret_value);
      //cerr << " ---- status " << status_to_string(status) << endl;
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
      return "-1";
    }
  }
  else 
  {
    cerr << "ERROR::VAR.CPP(line:260): cannot find m_var_type!" << endl;
    return "-1";
  }
}

Game_object* Variable::get_game_object()
{
  if(m_symbol->is_array())
  {
    return m_symbol->get_game_object_value(m_expr->eval_int());
  }
  else
  {
    return m_symbol->get_game_object_value();
  }
}
/*######################################################################*/
/*                       SET NEW VALUES BEGINS                          */
/*######################################################################*/
// Added in p7
void Variable::set_new_value(void* new_value)
{
  if (m_var_type == "CONSTANT")
  { 
    m_symbol->m_value = new_value;
  }
  else if (m_var_type == "EXPRESSION")
  {
    //cerr << " current index is : " << m_symbol->m_size << endl;
    //cerr << " new index is : " <<  m_expr->eval_int() << endl; 
    if (m_symbol->m_size < m_expr->eval_int() || m_expr->eval_int() < 0)
    {
      stringstream ss;
      ss << m_expr->eval_int();
      string s2;
      ss >> s2;
      Error::starting_execution();
      Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, m_symbol->m_name, s2);  
      if (m_symbol->m_type == INT_ARRAY)
      {
        ((int*)m_symbol->m_value)[0] = *(int*) new_value;
      }
      else if (m_symbol->m_type == DOUBLE_ARRAY)
      {
        ((double*)m_symbol->m_value)[0] = *(double*) new_value;
      }
      else if (m_symbol->m_type == STRING_ARRAY)
      {
        ((string*)m_symbol->m_value)[0] = *(string*) new_value;
      }
      else
      {
         cerr << "ERROR: VAR(428): CANNOT FIND TYPE IN SETTING TO [0]!" << endl;
      }
    }
    else
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
         cerr << "ERROR: VAR.CPP(4488): CANNOT FIND TYPE";
         cerr << " WHILE SETTING VALUE FOR ARRAY!" << endl;
      }
    }
  }
  else 
  {
     cerr << "Error: cannot find m_var_type in var::set_new_value!" << endl;
  }
}

void Variable::set_game_object_value(void* value)
{
  if (m_var_type == "GAME_OBJECT")
  {
    if (m_type == INT)
    {
      Game_object* temp_obj;
      temp_obj = (Game_object*)(m_symbol->m_value);
      temp_obj->set_member_variable(this->m_param, *(int*) value);
    }
    else if (m_type == DOUBLE)
    {
      Game_object* temp_obj;
      temp_obj = (Game_object*)(m_symbol->m_value);
      temp_obj->set_member_variable(this->m_param, *(double*) value);       
    }
    else if (m_type == STRING)
    {
      Game_object* temp_obj;
      temp_obj = (Game_object*)(m_symbol->m_value);
      temp_obj->set_member_variable(this->m_param, *(string*) value);       
    }
    else if (m_type == ANIMATION_BLOCK)
    {
      cerr << " THIS RAN IN ANI" << endl;
      Status status;
      Game_object* temp_obj;
      temp_obj = (Game_object*)(m_symbol->m_value);
      status = temp_obj->set_member_variable(this->m_param, (Animation_block*) value);
      cerr << "Status 531 var: " << status_to_string(status) << endl;
    }
    else
    {
      cerr << "ERROR::VAR.CPP: cannot find object type in";
      cerr << "set_game_object_value!" << endl;
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
      cerr << "Trouble in Var::setting int value for object_array!" << endl;
    }

    //cerr << "--game object type is: " << m_type << endl;

    if (m_type == INT)
    {
      temp_obj->set_member_variable(m_param, *(int*) value); 
    }
    else if (m_type == DOUBLE)
    {
      temp_obj->set_member_variable(m_param, *(double*) value); 
    }
    else if (m_type == STRING)
    {
      temp_obj->set_member_variable(m_param, *(string*) value); 
    }
    else if (m_type == ANIMATION_BLOCK)
    {
      temp_obj->set_member_variable(m_param, (Animation_block*) value);
    }
    else
    {
      cerr << "ERROR::Var.cpp: CANNOT FIND TYPE WHILE SETTING GAME-OBJECT VALUE!" << endl;
    }
  }
  else
  {
    cerr << "ERROR::VAR.CPP: something went wrong while setting value to game object! " << endl;
  }
}

/*############################################################################*/

Animation_block *Variable::get_animation_block()
{
  if (m_type == ANIMATION_BLOCK)
  {
    return m_symbol->get_animation_block();
  }
  else 
  {
    cerr << "ERROR:VAR(256): M_TYPE == ANIMATION_BLOCK?" << endl;
    return NULL;
  }
}
