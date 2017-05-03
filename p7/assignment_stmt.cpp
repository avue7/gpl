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
    if (m_var_lhs->m_var_type == "CONSTANT" && m_var_lhs->m_var_type == "EXPRESSION")
    {
      if (m_expr_rhs->m_type == INT)
      {
        cerr << " THIS SHIT IS a double" << endl;
        int value; 
        value = m_expr_rhs->eval_double();
        //m_var_lhs->m_symbol->set(value);
        cerr << "ASS(22):: new value is " << value << endl;
        void* v_value = (void*) new int(value);
        m_var_lhs->set_new_value(v_value);
        cerr << " NEW VALUE SHOULD BE: " << m_var_lhs->get_int_value(); 
        cerr << " at address :" << m_var_lhs->m_symbol<< endl;
      }    
      else if (m_expr_rhs->m_type == DOUBLE)
      {
        cerr << " THIS SHIT IS a double" << endl;
        double value; 
        value = m_expr_rhs->eval_double();
        //m_var_lhs->m_symbol->set(value);
        cerr << "ASS(22):: new value is " << value << endl;
        void* v_value = (void*) new double(value);
        m_var_lhs->set_new_value(v_value);
        cerr << " NEW VALUE SHOULD BE: " << m_var_lhs->get_int_value(); 
        cerr << " at address :" << m_var_lhs->m_symbol<< endl;
      }    
      else if (m_expr_rhs->m_type == STRING)
      {
        string s_value;
        s_value = m_expr_rhs->eval_string();
        cerr << "s_value is " << s_value << endl;
        void* v_value = (void*) new string(s_value);
        m_var_lhs->set_new_value(v_value);
      }
      else
      {
        cerr << "ERROR::(ASS.CPP:41) cannot find m_expr->m_type for CONSTANT!" << endl;
      }
    }
    else if (m_var_lhs->m_var_type == "GAME_OBJECT_ARRAY")
    {
      cerr << " M_VAR IS AN GAME_OBJECT" << endl;
      if (m_expr_rhs->m_type == INT)
      {
        int int_value = m_expr_rhs->eval_int();
        void* v_value = (void*) new int(int_value);
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
    cerr << "NEED TO IMPLEMENT THE += (Ass: 62) " << endl;
    exit(1);
  }
  else
  {
     cerr << "ERROR: CANNOT FIND TYPE IN ASS.CPP" << endl;
  }
}
