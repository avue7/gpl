#include <iostream>
#include "symbol.h"

int main()
{
  std::string name = "hello world";
  Gpl_type type = INT;
  void* value = (void*) new int(14);

  Symbol *test;
  test  = new Symbol(name, type, value);
  test->print();

}
