#include "symbol.h"

/****************************************
 * Constructors for int, double, string *
****************************************/
Symbol::Symbol(string name, Gpl_type type, int value)
{
  m_name = name;
  m_type = type;
  
  if (m_type == INT_ARRAY)
  { 
    m_value = (void*) new int[value];
    m_size = value;
  } 
  else
  {
    m_value = (void*) new int(value);
  }
}
/*
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

Symbol::Symbol(string name, Gpl_type type, double value, int size)
{
  m_name = name;
  m_type = type;
  m_value = (void*) new double(value);
  m_size = size;
}

Symbol::Symbol(string name, Gpl_type type, string value, int size)
{
  m_name = name;
  m_type = type;
  m_value = (void*) new string(value);
  m_size = size;
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

void Symbol::print()
{
  if (m_type == INT)
  {
    cout << "Name: " << m_name << ", Type: " << gpl_type_to_string(m_type) << ", Value: " << *((int*)m_value) << endl;
  }
/*  else if (m_type == 2)
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((double*)m_value) << endl;
  }
  else if (m_type == 4)
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << *((string*)m_value) << endl;
  }*/
  else
  {
    cout << "Name: " << m_name << ", Type: " << m_type << ", Value: " << m_size <<*((int*)m_value) << endl;
  } 
}
