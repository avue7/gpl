#include "symbol.h"

/****************************************
 * Constructors for int, double, string *
****************************************/

// Check for arrays in this function. 
Symbol::Symbol(string name, Gpl_type type, int value)
{
  if (type == INT_ARRAY)
  {
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new int[value];
  }
  if (type == DOUBLE_ARRAY)
  {
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new double[value];
  }
  if (type == STRING_ARRAY)
  {
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new string[value];
  }
  else
  {
    m_name = name;
    m_type = type;
    m_value = (void*) new int(value);
  }
}

Symbol::Symbol(string name, Gpl_type type, double value)
{
   m_name = name;
   m_type = type;
   m_value = (void *) new double(value);
}

Symbol::Symbol(string name, Gpl_type type, string value)
{
   m_name = name;
   m_type = type;
   m_value = (void*) new string(value);
}


/*  // THIS FUNCTION CAN BE USED INSTEAD FOR SIMPLICITY //
****************************************************************
    If you want to use this function, then you must dynamically
    allocate your variables in gpl.y grammar rules. This can cut
    down alot of code. However, we were told to allocate memory 
    for the variable types in the constructors
****************************************************************
Symbol::Symbol(string name, Gpl_type type, void* value)
{
  m_name = name;
  m_type = type;
  m_value = value;
  if (m_type == INT_ARRAY || m_type == DOUBLE_ARRAY || m_type == STRING_ARRAY)
  {
    if (*(int*) value == 0)
    {
     Error::error(Error::INVALID_ARRAY_SIZE, m_name, "0");
    }
    else
    {
      m_size = *(int*) value;
    }
  }
}
*/


/*********************************************
 ******** HELPER FUNCTIONS BELOW *************
*********************************************/

// Check to see if a symbol is an array
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

// Get the string type instead of a digit
string Symbol::get_type()
{
  return  m_type;
}

// Get the base type of an array
string Symbol::get_base_type()
{
  return gpl_type_to_base_string(m_type);
}

string Symbol::get_name()
{
  return m_name;
}

