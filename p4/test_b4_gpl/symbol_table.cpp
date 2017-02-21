#include "symbol_table.h"

/* static */ Symbol_table *Symbol_table::m_instance = NULL;
/* static */ Symbol_table *Symbol_table::instance()
{
  if (m_instance == NULL)
  {
    m_instance = new Symbol_table();
  }
  return m_instance;
}

/* Reference to unordered_map (might need it later):
http://www.cplusplus.com/reference/unordered_map/unordered_map/insert/
*/

void Symbol_table::add_symbol(Symbol *symbol)
{
  /* Use find() to see if we can find the symbol
     name to the end of the map. If it reaches end
     then name is not yet in the map. Lets add it. */
  if (m_map.find(symbol->m_name) == m_map.end())
  {
    m_map.insert(pair<string, Symbol*>(symbol->m_name, symbol));
  }
}


void Symbol_table::print(ostream &os)
{
  // Iterate thru map and print
  for (unordered_map<string, Symbol*>::iterator it = m_map.begin();
       it != m_map.end(); it++)
  {  
    Symbol *temp = it->second;

    if (temp->m_type == INT)
    {
      os << temp->m_type << " " << temp->m_name << " = " << 
           *(int *)(temp->m_value) << endl;
    }
  }  
}

Symbol *Symbol_table::lookup(string name)
{
  unordered_map<string, Symbol*>::const_iterator got = m_map.find(name);
  
  if (got == m_map.end())
  {
    cout << "NAME NOT FOUND IN MAP" << endl;   
    return NULL;
  }
  else
  {
    cout << got->first << " is located at " << got->second << endl;
    return got->second;
  }
}

bool compare_symbols (Symbol *a, Symbol *b)
{
  return a->get_name() < b->get_name();
}
