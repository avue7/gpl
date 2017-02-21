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

// If find() doesn't find any matching string in the map
// then return NULL, else return the pointer to the SYMBOL.
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

bool Symbol_table::compare_symbols (Symbol *a, Symbol *b)
{
  return a->get_name() < b->get_name();
}


/********************************************************
 * NEED THE ADD FUNCTION TO ADD SYMBOLS TO SYMBOL TABLE *
********************************************************/

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


/****************************
 *** PRINT FUNCTION BELOW ***
****************************/

void Symbol_table::print(ostream &os)
{
  // Use a vector to temporarily store symbols for sorting
  vector<Symbol*>sort_vector;

  // Iterate thru map and add to sort_vector
  for (unordered_map<string, Symbol*>::iterator it = m_map.begin();
       it != m_map.end(); it++)
  {  
    Symbol *symbol = it->second;
    sort_vector.push_back(symbol);
  }
  // Sort the vector aphabetically with -> name.
  sort(sort_vector.begin(), sort_vector.end(), compare_symbols);
  
  for (vector<Symbol*>::iterator it=sort_vector.begin();
    it < sort_vector.end(); it++) {

    Symbol *temp = *it; // Need to set new temp object to work

    if (temp->m_type == INT)
    {
      os << temp->get_type() << " " << 
      temp->m_name << " = " << *(int *)(temp->m_value) << endl;
    }
    else if (temp->m_type == DOUBLE)
    {
      os << temp->get_type() << " " << 
      temp->m_name << " = " << *(double *)(temp->m_value) << endl;
    }
    else if (temp->m_type == INT_ARRAY)
    {
      os << temp->get_type() << " " << 
      temp->m_name << " = " << *(int *)(temp->m_value) << endl;
    }

    else
    {
      os << temp->get_type() << " " <<
      temp->m_name << " = " << *(string *)(temp->m_value) << endl;
    }
  }  
}

