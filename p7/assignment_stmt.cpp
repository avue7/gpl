#include "assignment_stmt.h"

Assignment_stmt::Assignment_stmt(Variable* lhs, Expression* rhs, Assignment_type type)
{
  m_var_lhs = lhs;
  m_expr_rhs = rhs;
  m_oper = type;
}

void Assignment_stmt::execute()
{
  if (m_oper == ASS_ASSIGN)
  {
    if (m_var_lhs->m_type == INT || m_var_lhs->m_type == INT_ARRAY)
    {
      if (m_var_lhs->m_type == INT)
      {
        int value; 
        value = m_expr_rhs->eval_int();
        cerr << " value in assignment.cpp to be set is " << value << endl;
        void* v_value = (void*) new int(value);
        m_var_lhs->set_new_value(v_value);
      }
      else if (m_var_lhs->m_type == INT_ARRAY)
      {
        cerr << "THIS RAN IN INT_ARRAY: ass_stmt(26) " << endl;
        int value; 
        value = m_expr_rhs->eval_int();
        cerr << "THIS RAN ASS: new value should be 1: " << value << endl;
        cerr << "THIS RAN IN ASS: m_oper should be +: " << m_expr_rhs->m_oper << endl;
        void* v_value = (void*) new int(value);
        m_var_lhs->set_new_value(v_value);
      }
      else
      {
        cerr << "ERROR::ASS_STMT(line:34): don't know type!" << endl; 
      }
    }
    else if (m_var_lhs->m_type == DOUBLE || m_var_lhs->m_type == DOUBLE_ARRAY)
    {
      if (m_expr_rhs->m_type == DOUBLE || m_expr_rhs->m_type == INT)
      {
        double d_value;
        d_value = m_expr_rhs->eval_double();
        void* v_value = (void*) new double(d_value);
        m_var_lhs->set_new_value(v_value);
      }
    }     
    else if (m_expr_rhs->m_type == STRING || m_var_lhs->m_type == STRING_ARRAY)
    {
      cerr << "this ran in ass.cpp line 36" << endl;
      string s_value;
      s_value = m_expr_rhs->eval_string();
      void* v_value = (void*) new string(s_value);
      cerr << "Ass 40: S: string value is : " << s_value << endl;
      m_var_lhs->set_new_value(v_value);
    }
    else
    {
      cerr << "Error: Trouble finding (RHS) expr->m_type in";
      cerr << " Assignment_stmt::execute()!!!" << endl;
    }     
  }
  else if (m_oper == ASS_PLUS)
  {
    cout << "this printed in assPlus " << endl;
    int expr_ret_val = m_expr_rhs->eval_int();
    int var_ret_val = m_var_lhs->get_int_value();
    int sum = expr_ret_val + var_ret_val;
    void* v_value = (void*) new int(sum);
    cout << "New sum value of int array is : " << sum << endl;
    m_var_lhs->set_new_value(v_value);
  }
  else
  {
     cerr << "ERROR: CANNOT FIND TYPE IN ASS.CPP" << endl;
  }
}
