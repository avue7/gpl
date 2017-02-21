#include <iostream>
#include <string>
#include "symbol.h"
#include "symbol_table.h"

void get_int()
{
  std::string name = "hello world";
  Gpl_type type = INT;
  int value = 14;

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

//  Symbol_table *test_table = Symbol_table::instance();
void get_double()
{
  std::string name = "DOUBLE";
  Gpl_type type = DOUBLE;
  double value = 14.567;

  Symbol *test2;
  test2  = new Symbol(name, type, value);
  cout << "This is the symbol #2 (DOUBLE) we are testing: " << endl;
  test2->print();
  cout << "---------------------------------------------------" << endl;
}

void get_string()
{
  std::string name = "STRING";
  Gpl_type type = STRING;
  string value = "HELLO";

  Symbol *test3;
  test3  = new Symbol(name, type, value);
  cout << "This is the symbol #3 (string) we are testing: " << endl;
  test3->print();
  cout << "---------------------------------------------------" << endl;
}

int main()
{
  get_int();
  get_double();
  get_string();


}

