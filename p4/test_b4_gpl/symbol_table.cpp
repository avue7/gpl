#include "symbol_table.h"

Symbol_table::Symbol_table()
{
  

}

/* static */ Symbol_table *Symbol_table::m_instance = NULL;
/* static */ Symbol_table *Symbol_table::instance()
{
  if (m_instance == NULL)
  {
    m_instance = new Symbol_table();
  }
  return m_instance;
}

/*void Symbol_table::print(ostream &os)
{

}
*/
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
