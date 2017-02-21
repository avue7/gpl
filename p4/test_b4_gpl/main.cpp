#include <iostream>
#include "symbol.h"
#include "symbol_table.h"

int main()
{
  std::string name = "hello world";
  Gpl_type type = INT;
  int value = 14;

  Symbol *test;
  test  = new Symbol(name, type, value);
  cout << "This is the symbol we are testing: " << endl;
  test->print();
  cout << "---------------------------------------------------" << endl;

//  Symbol_table *test_table = Symbol_table::instance();

  

}
