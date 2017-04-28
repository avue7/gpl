// updated 2/14/2016

#include "event_manager.h"
#include "gpl_assert.h"
using namespace std;

/* static */ Event_manager *Event_manager::m_instance = 0;

/* static */ Event_manager * Event_manager::instance()
{
  if (!m_instance)
    m_instance = new Event_manager();
  return m_instance;
}

Event_manager::Event_manager()
{
}

Event_manager::~Event_manager()
{
}


void Event_manager::execute_handlers(Window::Keystroke keystroke)
{
  // Create temp vector to store
  vector <Statement_block*> my_vector = Event_manager::instance()->m_events[keystroke];
  for (unsigned int i = 0; i < my_vector.size(); i++)
  {
    my_vector[i]->execute();
  }
}

void Event_manager::register_event(Window::Keystroke key, Statement_block* block)
{ 
  // Add (register) keystroke to the events
  Event_manager::instance()->m_events[key].push_back(block);  
}

