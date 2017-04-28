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
    //cout << "NAME NOT FOUND IN MAP" << endl;   
    return NULL;
  }
  else
  {
    return got->second;
  }
}

bool Symbol_table::compare_symbols (Symbol *a, Symbol *b)
{
  return a->get_name() < b->get_name();
}


/********************************************************
 * NEED THE INSERT FUNCTION TO ADD SYMBOLS TO SYMBOL TABLE *
********************************************************/

bool Symbol_table::insert_symbol(Symbol *symbol)
{
  /* Use find() to see if we can find the symbol
     name to the end of the map. If it reaches end
     then name is not yet in the map. Lets add it. */  
  if (m_map.find(symbol->m_name) == m_map.end())
  {
    if (symbol->is_array())
    {
/*      if (symbol->m_size == 0)
      {
        string str = "0"; 
        Error::error(Error::INVALID_ARRAY_SIZE, symbol->m_name, str); 
      }*/
      if (symbol->m_type == INT_ARRAY)
      { 
        for (int i = 0; i < symbol->m_size; i++)
        {
          ((int*) symbol->m_value)[i] = 0;
        }
/*        string count;
        int *temp_array = new int[symbol->m_size];
        for (int i = 0; i < symbol->m_size; i++)
        {
          temp_array[i] = 0;
        }
        symbol->m_value = (void*) temp_array;*/
      }
      else if (symbol->m_type == DOUBLE_ARRAY)
      {
        double *temp_array = new double[symbol->m_size];   
        for (int i = 0; i < symbol->m_size; i++)
        {
          temp_array[i] = 0.0;
        }
        symbol->m_value = (void*) temp_array;
      }
      else if (symbol->m_type == CIRCLE_ARRAY)
      {
       // cerr << "this printed from circle_array in sym_table" << endl;
        for (int i = 0; i < symbol->m_size; i++)
        {
          ((Circle**) symbol->m_value)[i] = new Circle();
        }
      }
      else if (symbol->m_type == RECTANGLE_ARRAY)
      {
        for (int i = 0; i < symbol->m_size; i++)
        {
          ((Rectangle**) symbol->m_value)[i] = new Rectangle();
        }
      }
      else if (symbol->m_type == TRIANGLE_ARRAY)
      {
        for (int i = 0; i < symbol->m_size; i++)
        {
          //cerr << "this printed in trangle array of sym_table " << endl;
          ((Triangle**) symbol->m_value)[i] = new Triangle();
        }
      }
      else if (symbol->m_type == TEXTBOX_ARRAY)
      {
        for (int i = 0; i < symbol->m_size; i++)
        {
          ((Textbox**) symbol->m_value)[i] = new Textbox();
        }
      }
      else if (symbol->m_type == PIXMAP_ARRAY)
      {
        for (int i = 0; i < symbol->m_size; i++)
        {
          ((Pixmap**) symbol->m_value)[i] = new Pixmap();
        }
      }
      else  // It's a string
      {
/*        string *temp_array = new string[symbol->m_size];
        for (int i = 0; i < symbol->m_size; i++)
        {
          temp_array[i] = "";
        }
        symbol->m_value = (void*) temp_array;*/
        //cerr << "this printed from string in sym_table " << endl;
        for (int i = 0; i < symbol->m_size; i++)
        {
          ((string**) symbol->m_value)[i] = new string("");
        }
        
      }
    }
    m_map.insert(pair<string, Symbol*>(symbol->m_name, symbol)); 
    return true;
  }
  else
  {
    if (symbol->m_name == "DUMMY")
    {
     // cerr << "PRINTINING INSIDE OF SYMBOL_TABLE" << endl;
    }
/*    else
    {
      Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, symbol->m_name);
    }*/
    return false;
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
                           it < sort_vector.end(); it++) 
  {
    Symbol *temp = *it; // Need to set new temp object to work
    if (temp->m_type == INT)
    {
      os << gpl_type_to_string(temp->get_type()) << " " << 
      temp->m_name << " = " << *(int *)(temp->m_value) << endl;
    }
    else if (temp->m_type == DOUBLE)
    {
      os << gpl_type_to_string(temp->get_type()) << " " << 
      temp->m_name << " = " << *(double *)(temp->m_value) << endl;
    }
    else if (temp->m_type == STRING)
    {
     // cerr << "this printed in string of sym_table " << endl;
      os << gpl_type_to_string(temp->get_type()) << " " <<
      temp->m_name << " = " << "\"" << *(string *)(temp->m_value)
       << "\"" << endl;
    }
    else if (temp->m_type >= 16 && temp->m_type <= 528)
    {
        Game_object *obj_tmp;
        obj_tmp = temp->get_game_object_value();
        obj_tmp->print(temp->m_name, os);
        os << endl;
    }
    else if (temp->m_type == ANIMATION_BLOCK)
    {
      os << gpl_type_to_string(temp->get_type()) << " " << 
      temp->m_name << endl;
    }
    /* ARRAYS PRINTOUT BEGINS HERE */
    else if (temp->m_type == INT_ARRAY)
    {
      for (int i=0; i < temp->m_size; i++)
      {
        os << temp->get_base_type() << " " << 
        temp->m_name << "[" << i << "]" << " = " <<
       ((int *) temp->m_value)[i] << endl;
      }
    }
    else if (temp->m_type == DOUBLE_ARRAY)
    {
      for (int i=0; i < temp->m_size; i++)
      {
        os << temp->get_base_type() << " " << 
        temp->m_name << "[" << i << "]" << " = " <<
         *(double *)(temp->m_value) << endl;
      }
    }
    else if (temp->m_type == STRING_ARRAY)
    {
      for (int i=0; i < temp->m_size; i++)
      {
        os << temp->get_base_type() << " " << 
        temp->m_name << "[" << i << "]" << " = " << "\""
        << *(string *)(temp->m_value) << "\"" << endl;
      }
    }
    else if (temp->m_type == CIRCLE_ARRAY)
    {
        string count;
        Circle** temp_array = new Circle*[temp->m_size];
        Circle* obj_tmp = new Circle();
        temp_array = (Circle**) temp->m_value;
        for (int i=0; i < temp->m_size; i++)
        {
          stringstream ss;
          ss << i;
          count = ss.str();
          obj_tmp = temp_array[i];        
          obj_tmp->print(temp->m_name + "["+count+"]" , os);
          os << endl;
        } 
    }
    else if (temp->m_type == RECTANGLE_ARRAY)
    {
        string count;
        Rectangle** temp_array = new Rectangle*[temp->m_size];
        Rectangle* obj_tmp = new Rectangle();
        temp_array = (Rectangle**) temp->m_value;
        for (int i=0; i < temp->m_size; i++)
        {
          stringstream ss;
          ss << i;
          count = ss.str();
          obj_tmp = temp_array[i];        
          obj_tmp->print(temp->m_name + "["+count+"]" , os);
          os << endl;
        } 
    }
    else if (temp->m_type == TRIANGLE_ARRAY)
    {
        string count;
        Triangle** temp_array = new Triangle*[temp->m_size];
        Triangle* obj_tmp = new Triangle();
        temp_array = (Triangle**) temp->m_value;
        for (int i=0; i < temp->m_size; i++)
        {
          stringstream ss;
          ss << i;
          count = ss.str();
          obj_tmp = temp_array[i];        
          obj_tmp->print(temp->m_name + "["+count+"]" , os);
          os << endl;
        } 
    }
    else if (temp->m_type == TEXTBOX_ARRAY)
    {
        string count;
        Textbox** temp_array = new Textbox*[temp->m_size];
        Textbox* obj_tmp = new Textbox();
        temp_array = (Textbox**) temp->m_value;
        for (int i=0; i < temp->m_size; i++)
        { 
          stringstream ss;
          ss << i;
          count = ss.str();
          obj_tmp = temp_array[i];        
          obj_tmp->print(temp->m_name + "["+count+"]" , os);
          os << endl;
        } 
    }
    else if (temp->m_type == PIXMAP_ARRAY)
    {
        string count;
        Pixmap** temp_array = new Pixmap*[temp->m_size];
        Pixmap* obj_tmp = new Pixmap();
        temp_array = (Pixmap**) temp->m_value;
        for (int i=0; i < temp->m_size; i++)
        {
          stringstream ss;
          ss << i;
          count = ss.str();
          obj_tmp = temp_array[i];        
          obj_tmp->print(temp->m_name + "["+count+"]" , os);
          os << endl;
        } 
    }
    else
    {
      cerr << "ERROR: inside of symbol_table print(). Cannot find m_type!" << endl;
    }
  }
}

