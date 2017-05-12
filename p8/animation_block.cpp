// updated 2/14/2016

#include <vector>
#include "animation_block.h"
#include "game_object.h"
#include "gpl_assert.h"
#include "symbol.h"
using namespace std;

void Animation_block::initialize(Symbol *parameter_symbol, string name)
{
  m_name = name;
  // during error recovery a NULL parameter_symbol can be passed to Animation_block()
  if (parameter_symbol)
    assert(parameter_symbol->is_game_object());
  m_parameter_symbol = parameter_symbol;
  m_complete = false;
}

void Animation_block::mark_complete()
{
  m_complete = true;
}

bool Animation_block::is_complete()
{
  return m_complete;
}

void Animation_block::execute(Game_object *argument)
{
  m_parameter_symbol->m_value = argument;
  Statement_block::execute();
}


