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
  cout << "This is the symbol we are testing: " << endl;
  test->print();
  cout << "---------------------------------------------------" << endl;
}

//  Symbol_table *test_table = Symbol_table::instance();
void get_double()
{
  std::string name = "DOUBLE";
  Gpl_type type = DOUBLE;
  double value = 14.567;

  Symbol *test2;
  test2  = new Symbol(name, type, value);
  cout << "This is the symbol we are testing: " << endl;
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
  cout << "This is the symbol we are testing: " << endl;
  test3->print();
  cout << "---------------------------------------------------" << endl;
}

int main()
{
  get_int();
  get_double();
  get_string();
}

