#include <iostream>
using namespace std;

class Symbol_table
{
  public:
    static Symbol_table *symbol_table();
    
  private:
    static Symbol_table *m_symbol_table;


}
