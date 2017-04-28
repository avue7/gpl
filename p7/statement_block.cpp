// updated 2/14/16

#include "statement_block.h"
#include "gpl_assert.h"
using namespace std;


Statement_block::Statement_block()
{
  /* According to the instructions, when I see a "{", I need to create 
     and empty statement_block, so leaving this empty for now. If fails 
     then maybe I need to put some code here. */
}

// this function is called for all non-animation_block statement_blocks
// Implement it for p7
void Statement_block::execute()
{
  // This function should be defined before it is ever called
  // This assert will cause the program to abort if this function 
  // is called before it is implemented.

  // *** ==> Remove this assert when you implement this function
  // assert(false);
  for (unsigned int i = 0; i < m_statements.size(); i++)
  {
    m_statements[i]->execute();
  }
}
