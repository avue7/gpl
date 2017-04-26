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
  else if (type == DOUBLE_ARRAY)
  {
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new double[value];
  }
  else if (type == STRING_ARRAY)
  {
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new string*[value];
  }
  else if (type == CIRCLE_ARRAY)
  {
    //cerr << "this printed inside circle array of symbol.cpp " << endl;
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new Circle*[value];
  }
  else if (type == RECTANGLE_ARRAY)
  {
    //cerr << "this printed inside rectangle array of symbol.cpp " << endl;
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new Rectangle*[value];
  }
  else if (type == TRIANGLE_ARRAY)
  {
    //cerr << "this printed inside triangle array of symbol.cpp " << endl;
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new Triangle*[value];
  }
  else if (type == TEXTBOX_ARRAY)
  {
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new Textbox*[value];
  }
  else if (type == PIXMAP_ARRAY)
  {
    m_size = value;
    m_name = name;
    m_type = type;
    m_value = (void*) new Pixmap*[value];
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

Symbol::Symbol(string name, Gpl_type type)
{
  //cerr << "this was called in symbol game_object" << endl;
  m_name = name;
  if (type == TRIANGLE)
  {
    m_type = GAME_OBJECT;
    m_value = (void*) new Triangle();
  }
  else if (type == CIRCLE)
  {
    m_type = GAME_OBJECT;
    m_value = (void*) new Circle();
  }
  else if (type == RECTANGLE)
  {
    m_type = GAME_OBJECT;
    m_value = (void*) new Rectangle();
  }
  else if (type == TEXTBOX)
  {
    m_type = GAME_OBJECT;
    m_value = (void*) new Textbox();
  }
  else if (type == PIXMAP)
  {
    m_type = GAME_OBJECT;
    m_value = (void*) new Pixmap();
  }
  else if (type == ANIMATION_BLOCK)
  {
    m_type = ANIMATION_BLOCK;
    m_value = (void*) new Animation_block();
  }
  else
  {
    cerr << "Trouble in game_object constr" << endl;
  }
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
  else if (m_type == RECTANGLE_ARRAY)
  {
    return true;
  }
  else if (m_type == TRIANGLE_ARRAY)
  {
    return true;
  }
  else if (m_type == CIRCLE_ARRAY)
  {
    return true;
  }
  else if (m_type == TEXTBOX_ARRAY)
  {
    return true;
  }
  else if (m_type == PIXMAP_ARRAY)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Symbol::is_game_object()
{
  if (m_type >= 16 && m_type <= 528)
  {
    return true;
  }
  else if (m_type >= 1040 && m_type <= 1552)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Get the string type instead of a digit
Gpl_type Symbol::get_type()
{
  return m_type;
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

int Symbol::get_int_value()
{
  assert(m_type == INT);
  return *(int*) m_value;
}
 
double Symbol::get_double_value()
{
  // Make sure m_type is really a double
  assert(m_type == DOUBLE);
  return *(double*) m_value;
}

string Symbol::get_string_value()
{
  assert(m_type == STRING);
  stringstream ss;
  string value;
  ss << m_value;
  ss >> value;
  return value;
}

Game_object *Symbol::get_game_object_value()
{
  return (Game_object*) m_value;
}

void Symbol::set(int value)
{
  assert(m_type == INT);
  m_value = (void*) new int(value);
}

Animation_block* Symbol::get_animation_block()
{
  assert(m_type == ANIMATION_BLOCK);
  return (Animation_block*) m_value;
}
