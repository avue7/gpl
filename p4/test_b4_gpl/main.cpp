#include <iostream>
#include <string>
#include "symbol.h"
#include "symbol_table.h"

void get_int()
{
  std::string name = "a";
  Gpl_type type = INT;
  int value = 42;

  Symbol *test;
  test  = new Symbol(name, type, value);
  cout << "This is the symbol #1 (INT) we are testing: " << endl;
  test->print();
  cout << "---------------------------------------------------" << endl;
  
  cout << "TESTING OF THE SYMBOL_TABLE CLASS: " << endl;
  // Testing the adding of this symbol to the symbol_table
  Symbol_table *table = Symbol_table::instance();
  table->add_symbol(test);
  table->print(cout);
  
  // Testing the look_up function in symbol_table to make sure it works
  cout << "Testing the lookup function inside of symbol_table:" << endl;
  table->lookup(name);

  cout << "_-----------------------------------------------" << endl;
}

void get_int2()
{
  std::string name = "c";
  Gpl_type type = INT;
  int value = 42;

  Symbol *test;
  test  = new Symbol(name, type, value);
  cout << "This is the symbol #3 (INT) we are testing: " << endl;
  test->print();
  cout << "---------------------------------------------------" << endl;
  
  cout << "TESTING OF THE SYMBOL_TABLE CLASS: " << endl;
  // Testing the adding of this symbol to the symbol_table
  Symbol_table *table = Symbol_table::instance();
  table->add_symbol(test);
  table->print(cout);
  
  // Testing the look_up function in symbol_table to make sure it works
  cout << "Testing the lookup function inside of symbol_table:" << endl;
  table->lookup(name);

  cout << "_-----------------------------------------------" << endl;
}

//  Symbol_table *test_table = Symbol_table::instance();
void get_double()
{
  std::string name = "b";
  Gpl_type type = DOUBLE;
  double value = 3.14159;

  Symbol *test2;
  test2  = new Symbol(name, type, value);
  cout << "This is the symbol #2 (DOUBLE) we are testing: " << endl;
  test2->print();
  cout << "---------------------------------------------------" << endl;
  
  cout << "TESTING OF THE SYMBOL_TABLE CLASS: " << endl;
  // Testing the adding of this symbol to the symbol_table
  Symbol_table *table = Symbol_table::instance();
  table->add_symbol(test2);
  table->print(cout);
  
  // Testing the look_up function in symbol_table to make sure it works
  cout << "Testing the lookup function inside of symbol_table:" << endl;
  table->lookup(name);

  cout << endl;
  cout << endl;
  cout << " PURPOSELY TESTING WRONG LOOKUP NAME :WHOWHO TO CHECK LOOKUP:" << endl;
  table->lookup("WHOWHO");

  cout << "_-----------------------------------------------" << endl;
}

void get_string()
{
  std::string name = "d";
  Gpl_type type = STRING;
  string value = "HELLO WORLD";

  Symbol *test3;
  test3  = new Symbol(name, type, value);
  cout << "This is the symbol #4 (string) we are testing: " << endl;
  test3->print();
  cout << "---------------------------------------------------" << endl;
  
  cout << "TESTING OF THE SYMBOL_TABLE CLASS: " << endl;
  // Testing the adding of this symbol to the symbol_table
  Symbol_table *table = Symbol_table::instance();
  table->add_symbol(test3);
  table->print(cout);
  
  // Testing the look_up function in symbol_table to make sure it works
  cout << "Testing the lookup function inside of symbol_table:" << endl;
  table->lookup(name);

  cout << "_-----------------------------------------------" << endl;
}

void get_array_int()
{
  std::string name = "nums[0]";
  Gpl_type type = INT_ARRAY;
  int size = 4;
  int value = 42;

  Symbol *test;
  test  = new Symbol(name, type, value, size);
  cout << "This is the symbol #1 (INT) we are testing: " << endl;
  test->print();
  cout << "---------------------------------------------------" << endl;
  
  cout << "TESTING OF THE SYMBOL_TABLE CLASS: " << endl;
  // Testing the adding of this symbol to the symbol_table
  Symbol_table *table = Symbol_table::instance();
  table->add_symbol(test);
  table->print(cout);
  
  // Testing the look_up function in symbol_table to make sure it works
  cout << "Testing the lookup function inside of symbol_table:" << endl;
  table->lookup(name);

  cout << "_-----------------------------------------------" << endl;

}

void get_array_double()
{

}

void get_array_string()
{
 
}

int main()
{
  get_int();
  get_double();
  get_int2();
  get_string();
  
  // Testing the arrays now:
  get_array_int();
  get_array_double();
  get_array_string();
}

