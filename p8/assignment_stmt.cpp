#include "assignment_stmt.h"
#include "symbol.h"
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
    //cerr << " ASSS: m-var m type is : " << m_var_lhs->m_type << endl;
    if (m_var_lhs->m_var_type == "CONSTANT" || m_var_lhs->m_var_type == "EXPRESSION")
    {
      if (m_var_lhs->m_type == INT || m_var_lhs->m_type == INT_ARRAY)
      {
        int value; 
        value = m_expr_rhs->eval_int();
        void* v_value = (void*) new int(value);
        m_var_lhs->set_new_value(v_value);
      }    
      else if (m_var_lhs->m_type == DOUBLE || m_var_lhs->m_type == DOUBLE_ARRAY)
      {
        double value; 
        value = m_expr_rhs->eval_double();
        void* v_value = (void*) new double(value);
        m_var_lhs->set_new_value(v_value);
      }    
      else if (m_var_lhs->m_type == STRING || m_var_lhs->m_type == STRING_ARRAY)
      {
        string s_value;
        s_value = m_expr_rhs->eval_string();
        void* v_value = (void*) new string(s_value);
        m_var_lhs->set_new_value(v_value);
      }
      else if (m_var_lhs->m_symbol->is_game_object())
      {
        Error::error(Error::INVALID_LHS_OF_ASSIGNMENT, m_var_lhs->m_symbol->m_name,
               gpl_type_to_string(m_var_lhs->m_type));

      }
      else if (m_var_lhs->m_symbol->m_type == ANIMATION_BLOCK)
      {
        Error::error(Error::CANNOT_ASSIGN_TO_NON_MEMBER_ANIMATION_BLOCK,
              m_var_lhs->m_symbol->get_name());
      }
      else
      {
        cerr << "ERROR::(ASS.CPP:41) cannot find m_var->m_type for CONSTANT!" << endl;
      }
    }
    else if (m_var_lhs->m_var_type == "GAME_OBJECT" || m_var_lhs->m_var_type == "GAME_OBJECT_ARRAY")
    {
      if (m_var_lhs->m_type == INT && m_expr_rhs->m_type == INT)
      {
        //cerr << "1) m_lhs is an int and m_rhs is an int" << endl;
        int int_value = m_expr_rhs->eval_int();
        void* v_value = (void*) new int(int_value);
        //cerr << "  Ass.cpp: m_var_lhs type is : " << m_var_lhs->m_type << endl;
        m_var_lhs->set_game_object_value(v_value);
      }
      else if (m_var_lhs->m_type == DOUBLE)
      {
        //cerr << "1)from ass .cpp m_lhs is a double" << endl;
        if (m_expr_rhs->m_type == INT)
        {
          int int_value = m_expr_rhs->eval_int();
          double d_value = (double) int_value;
          void* v_value = (void*) new double(d_value);
          //cerr << "2)--from ass.cpp m_rhs is an int " << endl;
          m_var_lhs->set_game_object_value(v_value);      
        }
        else
        {
          //cerr << "2)--from ass.cpp m_rhs is a double" << endl;
          double d_value = m_expr_rhs->eval_double();
          //cerr << "3)-- VALUE: m_expr_rhs  in ass.cpp is " << d_value << endl;
          void* v_value = (void*) new double(d_value);
          //cerr << "  Ass.cpp: m_var_lhs type is : " << m_var_lhs->m_type << endl;
          m_var_lhs->set_game_object_value(v_value);
        }
      }
      else if (m_var_lhs->m_type == STRING)
      {
        stringstream ss;
        string s_value;
        if (m_expr_rhs->m_type == INT)
        {
          int int_value = m_expr_rhs->eval_int();
          ss << int_value;
          ss >> s_value;
          void* v_value = (void*) new string(s_value);
          //cerr << "2)--from ass.cpp m_rhs is an int " << endl;
          m_var_lhs->set_game_object_value(v_value);      
        }
        else if (m_expr_rhs->m_type == DOUBLE)
        {
          //cerr << "2)--from ass.cpp m_rhs is a double" << endl;
          double d_value = m_expr_rhs->eval_double();
          //cerr << "3)-- VALUE: m_expr_rhs  in ass.cpp is " << d_value << endl;
          ss << d_value;
          ss >> s_value;
          void* v_value = (void*) new string(s_value);
          //cerr << "  Ass.cpp: m_var_lhs type is : " << m_var_lhs->m_type << endl;
          m_var_lhs->set_game_object_value(v_value);
        }
        else if (m_expr_rhs->m_type == STRING)
        {
          string s_value = m_expr_rhs->eval_string();
          void* v_value = (void*) new string(s_value);
          m_var_lhs->set_game_object_value(v_value);
        }
        else
        {
          cerr << "ERROR::ASS.CPP(line:112): cannot find m_expr_rhs m_type!" << endl;
        }
      }
      else if (m_expr_rhs->m_type == ANIMATION_BLOCK)
      {
        cerr << "YOURE ON THE RIGHT TRACK PRINTED FROM ASS.CPP 87";
        cerr << " FOR ANIMATION BLOCK" << endl;
        cerr << "--eval_animation_block() returned : " << m_expr_rhs->eval_animation_block() << endl;
        cerr << "--m_expr_rhs m_type is: " << m_expr_rhs->m_type << endl;
        cerr << "--m_var_lhs m_type = " << m_var_lhs->m_type << endl;
        void* v_value = (void*) m_expr_rhs->eval_animation_block();
        m_var_lhs->set_game_object_value(v_value);
      }
      else
      {
        cerr << "ERROR::(ASS.CPP:87) cannot find m_var_lhs type!" << endl;
        cerr << "--m_expr_rhs m_type is: " << m_expr_rhs->m_type << endl;
        cerr << "--m_var_lhs m_type = " << m_var_lhs->m_type << endl;
      }
    }
    else
    {
      cerr << "ERROR::TROUBLE FINDING M_VAR_TYPE in";
      cerr << " Assignment_stmt::execute()!!!" << endl;
    }
  }
/*###########################################################################*/
  else if (m_oper == ASS_PLUS)
  {
    if (m_var_lhs->m_var_type == "CONSTANT" || m_var_lhs->m_var_type == "EXPRESSION")
    {
      /*
      cerr << "THIS RAN IN ASS.CPP +=" << endl;
      cerr << "----m_var_lhs->m_var_type is :" << m_var_lhs->m_var_type << endl;
      cerr << "----m_var_lhs->m_type is :" << m_var_lhs->m_type << endl;
      cerr << "----m_expr_rhs->m_type is :" << m_expr_rhs->m_type << endl;
      */
      if (m_var_lhs->m_type == INT || m_var_lhs->m_type == INT_ARRAY)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        //cerr << "---value with new expr in ass:85 " << result->eval_int() << endl;
        void* v_value = (void*) new int(result->eval_int());
        m_var_lhs->set_new_value(v_value);
      }
      else if (m_var_lhs->m_type == DOUBLE || m_var_lhs->m_type == DOUBLE_ARRAY)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
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
        cerr << "ERROR::ASS.CPP(line:117): cannot find type!" << endl;
      }
    }
    else if (m_var_lhs->m_var_type == "GAME_OBJECT" || m_var_lhs->m_var_type == "GAME_OBJECT_ARRAY")
    {
      if (m_expr_rhs->m_type == INT)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new int(result->eval_int());
        m_var_lhs->set_game_object_value(v_value);     
      }
      else if (m_expr_rhs->m_type == DOUBLE)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new double(result->eval_double());
        m_var_lhs->set_game_object_value(v_value);     
      }
      else if (m_expr_rhs->m_type == STRING)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(PLUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new string(result->eval_string());
        m_var_lhs->set_game_object_value(v_value);     
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
/*###########################################################################q*/
  else if (m_oper == ASS_MINUS)
  {
    if (m_var_lhs->m_var_type == "CONSTANT" || m_var_lhs->m_var_type == "EXPRESSION")
    {
      /*cerr << "THIS RAN IN ASS.CPP +=" << endl;
      cerr << "----m_var_lhs->m_var_type is :" << m_var_lhs->m_var_type << endl;
      cerr << "----m_var_lhs->m_type is :" << m_var_lhs->m_type << endl;
      cerr << "----m_expr_rhs->m_type is :" << m_expr_rhs->m_type << endl;
      */
      if (m_var_lhs->m_type == INT || m_var_lhs->m_type == INT_ARRAY)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(MINUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new int(result->eval_int());
        m_var_lhs->set_new_value(v_value);
      }
      else if (m_var_lhs->m_type == DOUBLE || m_var_lhs->m_type == DOUBLE_ARRAY)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(MINUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new double(result->eval_double());
        m_var_lhs->set_new_value(v_value);     
      }
      else
      {
        cerr << "ERROR::ASS.CPP(line:93): cannot find type!" << endl;
      }
    }
    else if (m_var_lhs->m_var_type == "GAME_OBJECT" || m_var_lhs->m_var_type == "GAME_OBJECT_ARRAY")
    {
      if (m_expr_rhs->m_type == INT)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(MINUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new int(result->eval_int());
        m_var_lhs->set_game_object_value(v_value);     
      }
      else if (m_expr_rhs->m_type == DOUBLE)
      {
        Expression* new_left = new Expression(m_var_lhs);
        Expression* result = new Expression(MINUS, m_var_lhs->m_type, new_left, m_expr_rhs);
        void* v_value = (void*) new double(result->eval_double());
        m_var_lhs->set_game_object_value(v_value);     
      }
      else
      {
        cerr << "ERROR::(ASS.CPP: \"minus\") cannot find m_expr_rhs type!" << endl;
      }
    }
    else
    {
      cerr << "ERROR::ASS.CPP(-=): cannot find m_var_type!" << endl;
    }
  }
/*#################################################################################*/
  else if (m_oper == ASS_PLUS_PLUS)
  {
    if (m_var_lhs->m_var_type == "CONSTANT" || m_var_lhs->m_var_type == "EXPRESSION")
    { 
      int old_value = m_var_lhs->get_int_value();
      old_value = old_value + 1;
      void* v_value = (void*) new int(old_value);
      m_var_lhs->set_new_value(v_value);
    }
    else
    {
      cerr << "ERROR::(ASS.CPP++): cannnot find m_var_type!" << endl;
      exit(1);
    }
  }
/*##################################################################################*/
  else if (m_oper == ASS_MINUS_MINUS)
  {
    int old_value = m_var_lhs->get_int_value();
    old_value = old_value - 1;
    int new_value = old_value;
    void* v_value = (void*) new int(new_value);
    m_var_lhs->set_new_value(v_value);
  }
  else
  {
     cerr << "ERROR: CANNOT FIND TYPE IN ASS.CPP" << endl;
  }
}
