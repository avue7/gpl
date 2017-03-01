#include "variable.h"
#include "expression.h"
#include "symbol.h"
#include "symbol_table.h"

Variable::Variable(string symbol_name)
{
  // Look for the symbol in the symbol table
  // store it in m_symbol
  m_symbol = Symbol_table::instance()->lookup(symbol_name);
  m_type = m_symbol->m_type;
  m_expr = NULL;
  m_var_type = "CONSTANT";
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
