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

/*void Symbol_table::print(ostream &os)
{

}
*/
Symbol *Symbol_table::lookup(string name)
{
  for (unordered_map<string, Symbol*>::iterator it = m_map.begin(); it != m_map.end(); it++)
  {
    string m_name = it->first;

    if (m_map.find(name) == m_name)
    {
      cout << "FOUND IT IN THE MAP" << endl;
    }
    else
    {
      return NULL;
    }
  }
}

bool compare_symbols (Symbol *a, Symbol *b)
{
  return a->get_name() < b->get_name();
}
