#include "for_stmt.h"

For_stmt::For_stmt(Statement_block* initializer, Statement_block* incrementor, Statement_block* body, Expression* expr)
{
  m_initializer = initializer;
  m_incrementor = incrementor;
  m_body = body;
  m_expr = expr;
}

void For_stmt::execute()
{
  for(m_initializer->execute(); m_expr->eval_int(); m_incrementor->execute())
  {
   
  /* cerr << "body executed" << endl;  
   cerr << "for_stmt: new end condition should be: ";
   cerr << m_expr->m_lhs->m_var->get_int_value() << endl;
   cerr << "for_statment: type should be int_array : ";
   cerr << m_expr->m_lhs->m_var->m_type << endl;
   cerr << "is index[?] < 3? :" << m_expr->eval_int() << endl;
   *** IF YOU NEED THESE ERROR CHECKING AGAIN THEN GO TO EXPRESSION.CPP
       and EXPRESSION.H UNCOMMENT THE VARIABLE.H IN EXPRESSION.H SO THAT 
       YOU CAN REFERENCE VAR_M_TYPE AND SUCH FROM THE EXPRESSION CLASS ***
   */
    m_body->execute();
  }
}
