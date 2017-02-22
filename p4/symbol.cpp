#include "symbol.h"

/****************************************
 * Constructors for int, double, string *
****************************************/
Symbol::Symbol(string name, Gpl_type type, void* value)
{
  m_name = name;
  m_type = type;
  m_value = value;
  if (m_type == INT_ARRAY || m_type == DOUBLE_ARRAY || m_type == STRING_ARRAY)
  {
    m_size = *(int*) value;
  }
}
/*
Symbol::Symbol(string name, Gpl_type type, void *value)
{
  if (type == INT_ARRAY)
  {
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new int[value];
  }
  else
  {
    m_name = name;
    m_type = type;
    m_value = (void*) new int(value);
  }
}

Symbol::Symbol(string name, Gpl_type type, int value)
{
  if (type == DOUBLE_ARRAY)
  {
   m_name = name;
   int temp = (int) value;
   m_value = (void *) new double[temp];
   m_size = temp;
  }
  else
  {
   m_name = name;
   m_type = type;
   m_value = (void *) new double(value);
  }
}

Symbol::Symbol(string name, Gpl_type type, void* value)
{
  if (type == STRING_ARRAY)
  {
    m_name = name;
    m_type = type;
    int temp = stoi(value);
    m_value = (void *) new string[temp];
    m_size = temp;
  }
  else
  {
    m_name = name;
    m_type = type;
    m_value = (void*) new string(value);
  }
}
*/
bool Symbol::is_array()
{
  if (m_type == INT_ARRAY)
  {
    return true;
  }
  else if (m_type == DOUBLE_ARRAY)
  {
    return true;
  }
  else if (m_type == STRING_ARRAY)
  {
    return true;
  }
  else
  {
    return false;
  }
}

string Symbol::get_type()
{
  return  gpl_type_to_string(m_type);
}

string Symbol::get_base_type()
{
  return gpl_type_to_base_string(m_type);
}

string Symbol::get_name()
{
  return m_name;
}

/*void Symbol::print()
{
  if (m_type == 1)
  {
    cout << "Name: " << m_name << ", Type: " << gpl_type_to_string(m_type) << ", Value: " << *((int*)m_value) << endl;
  }
  else if (m_type == 2)
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((double*)m_value) << endl;
  }
  else if (m_type == 4)
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((string*)m_value) << endl;
  }
  else
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << m_size <<*((int*)m_value) << endl;
  } 
}*/
