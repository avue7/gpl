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

int Variable::get_int_value()
{
  if (m_var_type == "DUMMY")
  {
    int value = 0;
    return value;
  }
  void *temp;
  int value;
  temp = m_symbol->m_value;
  value = *(int*)temp;
  return value;

}

double Variable::get_double_value()
{
  void *temp;
  double value;
  temp = m_symbol->m_value;
  value = *(double*)temp;
  return value;
}

string Variable::get_string_value()
{
  void *temp;
  string value;
  temp = m_symbol->m_value;
  value = *(string*)temp;
  return value;
}
