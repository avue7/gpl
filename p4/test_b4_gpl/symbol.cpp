#include "symbol.h"

Symbol::Symbol(string name, Gpl_type type, int value)
{
  m_name = name;
  m_type = type;
  m_value = (void*) new int(value);
}

string Symbol::get_name()
{
  return m_name;
}

void Symbol::print()
{
  cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((int*)m_value) << endl;
}
