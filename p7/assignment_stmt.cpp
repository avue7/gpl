#include "assignment_stmt.h"

Assignment_stmt::Assignment_stmt(Variable* lhs, Expression* rhs, Assignment_type type)
{
  m_var_lhs = lhs;
  m_expr_rhs = rhs;
  m_oper = type;
}

void Assignment_stmt::execute()
{
  /* We dont really care what the lhs is since we are not setting the values
     here....however, I just wanted to be sure....HOWEVER, we must check the
     quality or type of the right hand side to correctly allocate the correct
     amount of space. */

  if (m_oper == ASS_ASSIGN)
  {
    cerr << "THIS RAN IN ASS" << endl;
    if (m_var_lhs->m_var_type == "CONSTANT" || m_var_lhs->m_var_type == "EXPRESSION")
    {
      if (m_var_lhs->m_type == INT || m_var_lhs->m_type == INT_ARRAY)
      {
        cerr << " THIS SHIT IS a int" << endl;
        int value; 
        value = m_expr_rhs->eval_int();
        cerr << "ASS(22):: new value is " << value << endl;
        void* v_value = (void*) new int(value);
        m_var_lhs->set_new_value(v_value);
        cerr << " NEW VALUE SHOULD BE: " << m_var_lhs->get_int_value(); 
        cerr << " at address :" << m_var_lhs->m_symbol<< endl;
      }    
      else if (m_var_lhs->m_type == DOUBLE || m_var_lhs->m_type == DOUBLE_ARRAY)
      {
        cerr << " THIS SHIT IS a double" << endl;
        double value; 
        value = m_expr_rhs->eval_double();
        //m_var_lhs->m_symbol->set(value);
        cerr << "ASS(22):: new value is " << value << endl;
        void* v_value = (void*) new double(value);
        m_var_lhs->set_new_value(v_value);
        cerr << " NEW VALUE SHOULD BE: " << m_var_lhs->get_double_value(); 
        cerr << " at address :" << m_var_lhs->m_symbol<< endl;
      }    
      else if (m_var_lhs->m_type == STRING || m_var_lhs->m_type == STRING_ARRAY)
      {
        cerr << "THIS SHI IS A STRING" << endl;
        string s_value;
        s_value = m_expr_rhs->eval_string();
        void* v_value = (void*) new string(s_value);
        cerr << "s_value is " << s_value << endl;
        m_var_lhs->set_new_value(v_value);
      }
      else
      {
        cerr << "ERROR::(ASS.CPP:41) cannot find m_expr->m_type for CONSTANT!" << endl;
      }
    }
    else if (m_var_lhs->m_var_type == "GAME_OBJECT" || m_var_lhs->m_var_type == "GAME_OBJECT_ARRAY")
    {
      cerr << " M_VAR IS AN GAME_OBJECT" << endl;
      if (m_expr_rhs->m_type == INT)
      {
        int int_value = m_expr_rhs->eval_int();
        cerr << " VALUE: m_expr_rhs  in ass.cpp is " << int_value << endl;
        void* v_value = (void*) new int(int_value);
        cerr << "  Ass.cpp: m_var_lhs type is : " << m_var_lhs->m_type << endl;
        m_var_lhs->set_new_value(v_value);
      }
      else
      {
        cerr << "ERROR::(ASS.CPP:71) cannot find m_expr_rhs type!" << endl;
      }
    }
    else
    {
      cerr << "ERROR::TROUBLE FINDING M_VAR_TYPE in";
      cerr << " Assignment_stmt::execute()!!!" << endl;
    }
  }
  else if (m_oper == ASS_PLUS)
  {
    if (m_var_lhs->m_var_type == "CONSTANT" || m_var_lhs->m_var_type == "EXPRESSION")
    {
      cerr << "THIS RAN IN ASS.CPP +=" << endl;
      cerr << "----m_var_lhs->m_var_type is :" << m_var_lhs->m_var_type << endl;
      cerr << "----m_var_lhs->m_type is :" << m_var_lhs->m_type << endl;
      cerr << "----m_expr_rhs->m_type is :" << m_expr_rhs->m_type << endl;
      if (m_var_lhs->m_type == INT)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        cerr << "---value with new expr in ass:85 " << result->eval_int() << endl;
        void* v_value = (void*) new int(result->eval_int());
        m_var_lhs->set_new_value(v_value);
      }
      else if (m_var_lhs->m_type == DOUBLE)
      {
        Expression* new_left = new Expression(m_var_lhs);
        cerr << "---m_var_lhs eval_double () value : " << new_left->eval_double() << endl;
        cerr << "---m_expr_rhs eval_double() value : " << m_expr_rhs->eval_double() << endl;
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        cerr << "---value with new expr in ass:85 " << result->eval_double() << endl;
        void* v_value = (void*) new double(result->eval_double());
        m_var_lhs->set_new_value(v_value);     
      }
      else if (m_var_lhs->m_type == STRING || m_var_lhs->m_type == STRING_ARRAY)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new string(result->eval_string());
        m_var_lhs->set_new_value(v_value);     
      }
      else
      {
        cerr << "ERROR::ASS.CPP(line:93): cannot find type!" << endl;
      }
    }
    else if (m_var_lhs->m_var_type == "GAME_OBJECT" || m_var_lhs->m_var_type == "GAME_OBJECT_ARRAY")
    {
      cerr << " M_VAR IS AN GAME_OBJECT in ASS_PLUS" << endl;
      if (m_expr_rhs->m_type == STRING)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new string(result->eval_string());
        cerr << "  Ass.cpp: m_var_lhs type is : " << m_var_lhs->m_type << endl;
        m_var_lhs->set_new_value(v_value);     
      }
      else
      {
        cerr << "ERROR::(ASS.CPP:132 \"plus\") cannot find m_expr_rhs type!" << endl;
      }
    }
    else
    {
      cerr << "ERROR::ASS.CPP(line:107): cannot find m_var_type!" << endl;
    }
  }
  else if (m_oper == ASS_MINUS)
  {
    if (m_var_lhs->m_var_type == "CONSTANT" || m_var_lhs->m_var_type == "EXPRESSION")
    {
      cerr << "THIS RAN IN ASS.CPP +=" << endl;
      cerr << "----m_var_lhs->m_var_type is :" << m_var_lhs->m_var_type << endl;
      cerr << "----m_var_lhs->m_type is :" << m_var_lhs->m_type << endl;
      cerr << "----m_expr_rhs->m_type is :" << m_expr_rhs->m_type << endl;
      if (m_var_lhs->m_type == INT)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(MINUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        cerr << "---value with new expr in ass:85 " << result->eval_int() << endl;
        void* v_value = (void*) new int(result->eval_int());
        m_var_lhs->set_new_value(v_value);
      }
      else if (m_var_lhs->m_type == DOUBLE)
      {
        Expression* new_left = new Expression(m_var_lhs);
        cerr << "---m_var_lhs eval_double () value : " << new_left->eval_double() << endl;
        cerr << "---m_expr_rhs eval_double() value : " << m_expr_rhs->eval_double() << endl;
        Expression* result = new Expression(MINUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        cerr << "---value with new expr in ass:85 " << result->eval_double() << endl;
        void* v_value = (void*) new double(result->eval_double());
        m_var_lhs->set_new_value(v_value);     
      }
      else if (m_var_lhs->m_type == STRING || m_var_lhs->m_type == STRING_ARRAY)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(MINUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new string(result->eval_string());
        m_var_lhs->set_new_value(v_value);     
      }
      else
      {
        cerr << "ERROR::ASS.CPP(line:93): cannot find type!" << endl;
      }
    }
  }
  else
  {
     cerr << "ERROR: CANNOT FIND TYPE IN ASS.CPP" << endl;
  }
}
