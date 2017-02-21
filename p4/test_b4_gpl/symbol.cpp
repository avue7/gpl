#include "symbol.h"

/****************************************
 * Constructors for int, double, string *
****************************************/
Symbol::Symbol(string name, Gpl_type type, int value)
{
  m_name = name;
  m_type = type;
  m_value = (void*) new int(value);
}

Symbol::Symbol(string name, Gpl_type type, double value)
{
  m_name = name;
  m_type = type;
  m_value = (void*) new double(value);
}

Symbol::Symbol(string name, Gpl_type type, string value)
{
  m_name = name;
  m_type = type;
  m_value = (void*) new string(value);
}


string Symbol::get_name()
{
  return m_name;
}

void Symbol::print()
{
  if (m_type == 1)
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((int*)m_value) << endl;
  }
  else if (m_type == 2)
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((double*)m_value) << endl;
  }
  else
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((string*)m_value) << endl;
  }
}
