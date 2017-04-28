// updated 2/14/16

/***
  This file is a placeholder for the Event_manager class you will write 
  in phase 7 (p7).

  My class Window uses class Event_manager.  Since p6 uses class Window
  you need this placeholder class to get p6 to work.

  You may use this file and event_manager.cpp w/o modification in p6.

  You may use them as a starting point for your Event_manager class for p7.

  I have put in just enough for it to work in p6.

***/

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <iostream>
#include <string>
#include <vector>

#include "window.h" // for Keystroke enum
#include "statement_block.h"

class Statement_block;

class Event_manager
{
  public:

    static Event_manager *instance();

    void execute_handlers(Window::Keystroke keystroke);

    ~Event_manager();

    // P7 modification below:
    
    // Need vector for statement_blocks
    std::vector<Statement_block*> m_events[Window::NUMBER_OF_KEYS];
    void register_event(Window::Keystroke key, Statement_block* block);

  private:
    // hide default constructor because this is a singleton
    Event_manager();

    static Event_manager *m_instance;

    // disable default copy constructor and default assignment
    // done as a precaution, they should never be called
    Event_manager(const Event_manager&); 
    const Event_manager &operator=(const Event_manager&); 
};

#endif // #ifndef EVENT_MANAGER_H
