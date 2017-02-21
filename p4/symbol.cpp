#include <symbol.h>
#include <iostream>

Symbol::Symbol(string m_name, Gpl_type m_type, void* m_value)
{
  name = m_name;
  type = m_type;
  value = m_value;
}



