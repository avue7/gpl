#include "symbol.h"

Symbol::Symbol(string name, Gpl_type type, void* value)
{
  m_name = name;
  m_type = type;
  m_value = value;
}

void Symbol::print()
{
  cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((int*)m_value) << endl;
}
