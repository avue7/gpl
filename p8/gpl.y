%{  // bison syntax to indicate the start of the header
    // the header is copied directly into y.tab.c (the generated parser)
extern int yylex();               // this lexer function returns next token
extern int yyerror(const char *); // used to print errors
extern int line_count;            // current line in the input; from record.l
 
#include "error.h"      // class for printing errors (used by gpl)
#include "parser.h"
#include "symbol_table.h"
#include "symbol.h"
#include "gpl_type.h"
#include "expression.h"
#include "variable.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
Game_object* cur_obj; // Global variable that stores current obj under const.
string cur_name; // Current name for object
int counter=0; //THis is for debugging....
// Globalizing the declaring of stack. Library header is included
// in the parser.h
stack <Statement_block*> global_stack;
vector <Animation_block*> animation_stack; //Added in p8
// bison syntax to indicate the end of the header
%} 

%union {
 int            union_int;
 double         union_double;
 int            union_line_number;
 std::string    *union_string;  // MUST be a pointer to a string (this sucks!)
 std::string    *union_string_constant;
 Gpl_type       union_gpl_type;
 Expression     *union_expression;
 Variable 	*union_variable;
 Operator_type  union_oper_type;
 Statement_block *union_statement_block;
 Window::Keystroke union_keystroke;
}

// if a token has a type associated with it, put that type (as named in the
// union) inside of <> after the %token
// the value is put in the union by the scanner (in the .l file ) so it can be
// used by the parser (in the .y file)
// Tokens with a < > after the %token require a type.
// This is the type of the variable the scanner puts into the union.
// Fill in the < > with the appropriate type
//     for example
//     %token <union_int> T_INT_CONSTANT       "int constant"

%error-verbose

%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"
%token <union_int> T_FORWARD         "forward" // value is line number
%token T_INITIALIZATION      "initialization"
%token T_TERMINATION          "termination"

%token T_TRUE                "true"
%token T_FALSE               "false"

%token T_TOUCHES             "touches"
%token T_NEAR                "near"

%token T_ANIMATION           "animation"

%token T_IF                  "if"
%token T_FOR                 "for"
%token T_ELSE                "else"
%token <union_int> T_PRINT           "print" // value is line number
%token <union_int> T_EXIT            "exit" // value is line number

%token T_LPAREN              "("
%token T_RPAREN              ")"
%token T_LBRACE              "{"
%token T_RBRACE              "}"
%token T_LBRACKET            "["
%token T_RBRACKET            "]"
%token T_SEMIC               ";"
%token T_COMMA               ","
%token T_PERIOD              "."

%token T_ASSIGN              "="
%token T_PLUS_ASSIGN         "+="
%token T_MINUS_ASSIGN        "-="
%token T_PLUS_PLUS           "++"
%token T_MINUS_MINUS         "--"

%token T_MULTIPLY            "*"
%token T_DIVIDE              "/"
%token T_MOD                 "%"
%token T_PLUS                "+"
%token T_MINUS               "-"
%token T_SIN                 "sin"
%token T_COS                 "cos"
%token T_TAN                 "tan"
%token T_ASIN                "asin"
%token T_ACOS                "acos"
%token T_ATAN                "atan"
%token T_SQRT                "sqrt"
%token T_FLOOR               "floor"
%token T_ABS                 "abs"
%token T_RANDOM              "random"

%token T_LESS                "<"
%token T_GREATER             ">"
%token T_LESS_EQUAL          "<="
%token T_GREATER_EQUAL       ">="
%token T_EQUAL               "=="
%token T_NOT_EQUAL           "!="

%token T_AND                 "&&"
%token T_OR                  "||"
%token T_NOT                 "!"

%token T_ON                  "on"
%token T_SPACE               "space"
%token T_LEFTARROW           "leftarrow"
%token T_RIGHTARROW          "rightarrow"
%token T_UPARROW             "uparrow"
%token T_DOWNARROW           "downarrow"
%token T_LEFTMOUSE_DOWN      "leftmouse_down"
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down"
%token T_RIGHTMOUSE_DOWN     "rightmouse_down"
%token T_LEFTMOUSE_UP        "leftmouse_up"
%token T_MIDDLEMOUSE_UP      "middlemouse_up"
%token T_RIGHTMOUSE_UP       "rightmouse_up"
%token T_MOUSE_MOVE          "mouse_move"
%token T_MOUSE_DRAG          "mouse_drag"
%token T_F1                  "f1"
%token T_AKEY                "akey"
%token T_SKEY                "skey"
%token T_DKEY                "dkey"
%token T_FKEY                "fkey"
%token T_HKEY                "hkey"
%token T_JKEY                "jkey"
%token T_KKEY                "kkey"
%token T_LKEY                "lkey"
%token T_WKEY                "wkey"


%token <union_string> T_ID             "identifier"
%token <union_int> T_INT_CONSTANT    "int constant"
%token <union_double> T_DOUBLE_CONSTANT "double constant"
%token <union_string_constant> T_STRING_CONSTANT "string constant"

// special token that does not match any production
// used for characters that are not part of the language
%token T_ERROR               "error"


// Just like tokens, grammar symbols can be associated with a type
// This allows values to be passed up (and down) the parse tree
%type <union_gpl_type> simple_type
%type <union_expression> expression
%type <union_variable> variable
%type <union_expression> primary_expression
%type <union_expression> optional_initializer
%type <union_oper_type> math_operator 
%type <union_int> object_type
%type <union_string> animation_parameter
%type <union_keystroke> keystroke
%type <union_statement_block> statement_block
%type <union_statement_block> statement_block_creator
%type <union_statement_block> if_block
%type <union_int> check_animation_parameter /* Added in p8: need for id */
%type <union_expression> geometric_operator /* Added in p8 */ 
///////////// Precedence = low to high ////////////////////////////////
%nonassoc IF_NO_ELSE
%nonassoc T_ELSE
%left T_OR
%left T_AND
%left T_EQUAL T_NOT_EQUAL
%left T_LESS T_LESS_EQUAL T_GREATER T_GREATER_EQUAL 
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_MOD
%nonassoc UNARY_OPS
///////////////////////////////////////////////////////////////////////

%% // indicates the start of the rules

//---------------------------------------------------------------------
program:
    declaration_list block_list
    {
      vector<Animation_block*>::iterator it; 
      for (it = animation_stack.begin(); it != animation_stack.end(); it++)
      {
        Animation_block* anim_block = *it;
        if (!anim_block->is_complete())
        {
          Error::error(Error::NO_BODY_PROVIDED_FOR_FORWARD, anim_block->name());
        }
      } 
    }
    ;

//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration
    | empty
    ;

//---------------------------------------------------------------------
declaration:
    variable_declaration T_SEMIC
    | object_declaration T_SEMIC
    | forward_declaration T_SEMIC
    ;

//---------------------------------------------------------------------
variable_declaration:
    simple_type  T_ID  optional_initializer
    {
      Symbol *symbol;
      Expression *expr = $3;
      if ($3 && ($3->m_type > $1))
      {
        Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, 
               gpl_type_to_string($3->m_type), *$2, gpl_type_to_string($1));
      }
      else if ($3)
      {
        if ($1 == INT)
        {
          bool status; 
          if ($3->m_type == DOUBLE)
          {
            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->m_type), *$2, gpl_type_to_string($1));
            symbol = new Symbol(*$2, INT, 0);
          }
          else if ($3->m_type == STRING)
          {
            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->m_type), *$2, gpl_type_to_string($1));
            symbol = new Symbol(*$2, INT, 0); 
          }
          else if ($3->m_type == INT || $3->m_type == INT_ARRAY)
          {
            symbol = new Symbol(*$2, INT, $3->eval_int());
          }
        }
        else if ($1 == DOUBLE)
        {
          if ($3->m_type == STRING)
          {
            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->m_type), *$2, gpl_type_to_string($1));
            symbol = new Symbol(*$2, INT, 0); 
          } 
          else if ($3->m_type == INT || $3->m_type == INT_ARRAY)
          {
            symbol = new Symbol(*$2, DOUBLE, (double) $3->eval_int());
          }
          else if ($3->m_type == DOUBLE || $3->m_type == DOUBLE_ARRAY)
          {  
            symbol = new Symbol(*$2, DOUBLE, $3->eval_double());
          }
        }
        else if ($1 == STRING)
        {
          if ($3->m_type == INT || $3->m_type == INT_ARRAY)
          {
            stringstream ss;
            int ret_val;
            ret_val = $3->eval_int();
            string s_ret_val;
            ss << ret_val;
            ss >> s_ret_val;
            symbol = new Symbol(*$2, STRING, s_ret_val);
          }
          else if ($3->m_type == DOUBLE || $3->m_type == DOUBLE_ARRAY)
          {
            stringstream ss;
            double ret_val;
            ret_val = $3->eval_double();
            string s_ret_val;
            ss << ret_val;
            ss >> s_ret_val;
            symbol = new Symbol(*$2, STRING, s_ret_val);
          }
          else
          {
            symbol = new Symbol(*$2, STRING, $3->eval_string());
          }
        }
        if(!Symbol_table::instance()->insert_symbol(symbol))
        {
          Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
        }
      }
      else
      {
        //cerr << "NO INITIALIZER" << endl;
        switch($1)
        {
          case INT:
            symbol = new Symbol(*$2, $1, 0);
            break;
          case DOUBLE:
            symbol = new Symbol(*$2, $1, 0.0);
            break;
          case STRING:
            symbol = new Symbol(*$2, $1, "");
            break;
        }
        if(!Symbol_table::instance()->insert_symbol(symbol))
        {
          Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
        }
      }
    }
    | simple_type  T_ID  T_LBRACKET expression T_RBRACKET
    {
      Symbol *symbol;
      if($4->m_type == DOUBLE || $4->m_type == STRING)
      { 
        Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, gpl_type_to_string($4->m_type), *$2);
      }
      if ($4->m_type == INT)
      {      
        if ($4->eval_int() < 1)
        {
          Error::error(Error::INVALID_ARRAY_SIZE, *$2, $4->eval_string());
        }
        else
        {
          int array_size = $4->eval_int();
          if ($1 == INT)
          {
            symbol = new Symbol(*$2, INT_ARRAY, array_size);  
          }      
          else if ($1 == DOUBLE)
          { 
            symbol = new Symbol(*$2, DOUBLE_ARRAY, array_size);
          }
          else
          { 
            symbol = new Symbol(*$2, STRING_ARRAY, array_size);
          }
          if(!Symbol_table::instance()->insert_symbol(symbol))
          {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
          }
        }
      }
    }
    ;


//---------------------------------------------------------------------
simple_type:
    T_INT
    { $$ = INT;}
    | T_DOUBLE
    { $$ = DOUBLE; }
    | T_STRING
    { $$ =  STRING; }
    ;

//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression
    { $$ = $2; }
    | empty
    { $$ = NULL; }
    ;

//---------------------------------------------------------------------
object_declaration:
    object_type T_ID
    {
      Symbol *symbol; 
      cur_name = *$2;
      switch($1)
      {
        case TRIANGLE:
             symbol = new Symbol(*$2, TRIANGLE);
             cur_obj = symbol->get_game_object_value();
             break;
        case CIRCLE:
             symbol = new Symbol(*$2, CIRCLE);
             cur_obj = symbol->get_game_object_value();
             break;
        case RECTANGLE: 
             symbol = new Symbol(*$2, RECTANGLE);
             cur_obj = symbol->get_game_object_value();
             break;
        case TEXTBOX:
             symbol = new Symbol(*$2, TEXTBOX);
             cur_obj = symbol->get_game_object_value();
             break;
        case PIXMAP:
             symbol = new Symbol(*$2, PIXMAP);
             cur_obj = symbol->get_game_object_value();
             break;
      }
      if(!Symbol_table::instance()->insert_symbol(symbol))
      {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
      }
    }
    T_LPAREN parameter_list_or_empty T_RPAREN
    {
      
    }
    | object_type T_ID T_LBRACKET expression T_RBRACKET
    {
      Symbol *symbol; 
      if ($4->m_type != INT || $4->eval_int() <= 0)
      {
        Error::error(Error::INVALID_ARRAY_SIZE, *$2, $4->eval_string());
        symbol = new Symbol(*$2, INT, 0);
      }
      else
      {
        switch($1)
        {
          case TRIANGLE:
             cerr << "THIS HAPPENED IN GPL 411 " << endl;
             symbol = new Symbol(*$2, TRIANGLE_ARRAY, $4->eval_int());
             break;
          case CIRCLE:
             symbol = new Symbol(*$2, CIRCLE_ARRAY, $4->eval_int());
             break;
          case RECTANGLE: 
             symbol = new Symbol(*$2, RECTANGLE_ARRAY, $4->eval_int());
             break;
          case TEXTBOX:
             symbol = new Symbol(*$2, TEXTBOX_ARRAY, $4->eval_int());
             break;
          case PIXMAP:
             symbol = new Symbol(*$2, PIXMAP_ARRAY, $4->eval_int());
             break;
        }
      }
      if(!Symbol_table::instance()->insert_symbol(symbol))
      {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
      }
    }
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    { $$ = TRIANGLE; }
    | T_PIXMAP
    { $$ = PIXMAP; }
    | T_CIRCLE
    { $$ = CIRCLE; }
    | T_RECTANGLE
    { $$ = RECTANGLE; }
    | T_TEXTBOX
    { $$ = TEXTBOX; }
    ;

//---------------------------------------------------------------------
parameter_list_or_empty :
    parameter_list
    | empty
    ;

//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter
    | parameter
    ;

//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression
    {
      Gpl_type member_type;
      Status status;
      if ((status = cur_obj->get_member_variable_type(*$1, member_type)) != OK)
      {
        switch(status)
        {
          case MEMBER_NOT_DECLARED:
            Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, 
            gpl_type_to_string(cur_obj->type()), *$1);
            break;
          case MEMBER_NOT_OF_GIVEN_TYPE:
            Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, 
            gpl_type_to_string(cur_obj->type()), *$1);
            break;
        } 
      }
      else
      { 
        switch(member_type)
        {
          case INT:
          {
            if ($3->m_type != INT)
            {
              Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, 
                     cur_name, *$1);
              break;  
            }
            else
            {
              int int_value;
              int_value = $3->eval_int();
              status = cur_obj->set_member_variable(*$1, int_value);
              break;
            } 
          }
          case DOUBLE:
          {
              double d_value;
              d_value = $3->eval_double();
              status = cur_obj->set_member_variable(*$1, d_value);
              break;
          }
          case STRING:
          {
              string s_value;
              s_value = $3->eval_string();
              status = cur_obj->set_member_variable(*$1, s_value);
              break;
           
          }
          case ANIMATION_BLOCK:
          {      
            Animation_block *a_value;
            a_value = $3->eval_animation_block();
            if (cur_obj->type() != a_value->get_parameter_symbol()->m_type)
            {
              Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT, cur_name, a_value->name());
              break;
            }
            else
            {
              status = cur_obj->set_member_variable(*$1, a_value);
              break;
            } 
          }
        }
       //cerr << status_to_string(status) << endl;
      }
    }
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
    {
      Animation_block* anim_block;
      Symbol *found_sym, *symbol; 

      symbol = new Symbol(*$3, ANIMATION_BLOCK);            
      if(!Symbol_table::instance()->insert_symbol(symbol))
      {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$3);
      }
      if ($5)
      {
        found_sym = Symbol_table::instance()->lookup(*$5);       
        anim_block = (Animation_block*) symbol->m_value; 
        anim_block->initialize(found_sym, *$3);
        animation_stack.push_back(anim_block);
      }

    }
    ;

//---------------------------------------------------------------------
block_list:
    block_list block
    | empty
    ;

//---------------------------------------------------------------------
block:
    initialization_block
    | termination_block
    | animation_block
    | on_block
    ;

//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block
    {
      Event_manager::instance()->register_event(Window::INITIALIZE, $2);
    }
    ;

//---------------------------------------------------------------------
termination_block:
    T_TERMINATION statement_block
    {
      Event_manager::instance()->register_event(Window::TERMINATE, $2);
    }
    ;

//---------------------------------------------------------------------
animation_block:
    T_ANIMATION T_ID  T_LPAREN check_animation_parameter 
    {
      Symbol* symbol;
      Animation_block* anim_block;
      symbol = Symbol_table::instance()->lookup(*$2);
      anim_block = symbol->get_animation_block();
      if (!symbol)
      {
        Error::error(Error::NO_FORWARD_FOR_ANIMATION_BLOCK, *$2);
      }
      else
      {
        if (!anim_block)
        {
          Error::error(Error::NO_FORWARD_FOR_ANIMATION_BLOCK, *$2);
        }
        else if (anim_block->is_complete())
        {
          Error::error(Error::PREVIOUSLY_DEFINED_ANIMATION_BLOCK, anim_block->name());
        }
        else
        {
          anim_block->mark_complete();
          global_stack.push(anim_block);
        }
      }
    }
    T_RPAREN T_LBRACE statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    {
      cur_name = *$2;
      $$ = $2;
      Symbol *symbol; 
      
      switch($1)
      {
          case TRIANGLE:
             symbol = new Symbol(*$2, TRIANGLE);
             cur_obj = symbol->get_game_object_value();
             break;
          case CIRCLE:
             symbol = new Symbol(*$2, CIRCLE);
             cur_obj = symbol->get_game_object_value();
             break;
          case RECTANGLE: 
             symbol = new Symbol(*$2, RECTANGLE);
             cur_obj = symbol->get_game_object_value();
             break;
          case TEXTBOX:
             symbol = new Symbol(*$2, TEXTBOX);
             cur_obj = symbol->get_game_object_value();
             break;
          case PIXMAP:
             symbol = new Symbol(*$2, PIXMAP);
             cur_obj = symbol->get_game_object_value();
             break;
      }
      cur_obj->never_animate();
      cur_obj->never_draw();

      if (!Symbol_table::instance()->insert_symbol(symbol))
      {
        Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *$2);
        symbol = new Symbol("DUMMY", INT, 0);
        $$ = 0;
      }    
    }
    ;

//---------------------------------------------------------------------
check_animation_parameter:
    T_TRIANGLE T_ID
    {
      $$ = TRIANGLE;
    }
    | T_PIXMAP T_ID
    {
      $$ = PIXMAP;
    }
    | T_CIRCLE T_ID
    {
      $$ = CIRCLE;
    }
    | T_RECTANGLE T_ID
    {
      $$ = RECTANGLE;
    }
    | T_TEXTBOX T_ID
    {
      $$ = TEXTBOX;
    }
    ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block
    {
      Event_manager::instance()->register_event($2, $3);
    }
    ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
    { $$ = Window::SPACE; }
    | T_UPARROW
    { $$ = Window::UPARROW; }
    | T_DOWNARROW
    { $$ = Window::DOWNARROW; }
    | T_LEFTARROW
    { $$ = Window::LEFTARROW; }
    | T_RIGHTARROW
    { $$ = Window::RIGHTARROW; }
    | T_LEFTMOUSE_DOWN
    { $$ = Window::LEFTMOUSE_DOWN; }
    | T_MIDDLEMOUSE_DOWN
    { $$ = Window::MIDDLEMOUSE_DOWN; }
    | T_RIGHTMOUSE_DOWN
    { $$ = Window::RIGHTMOUSE_DOWN; }
    | T_LEFTMOUSE_UP
    { $$ = Window::LEFTMOUSE_UP; }
    | T_MIDDLEMOUSE_UP
    { $$ = Window::MIDDLEMOUSE_UP; }
    | T_RIGHTMOUSE_UP
    { $$ = Window::RIGHTMOUSE_UP; }
    | T_MOUSE_MOVE
    { $$ = Window::MOUSE_MOVE; }
    | T_MOUSE_DRAG
    { $$ = Window::MOUSE_DRAG; }
    | T_AKEY 
    { $$ = Window::AKEY; }
    | T_SKEY 
    { $$ = Window::SKEY; }
    | T_DKEY 
    { $$ = Window::DKEY; }
    | T_FKEY 
    { $$ = Window::FKEY; }
    | T_HKEY 
    { $$ = Window::HKEY; }
    | T_JKEY 
    { $$ = Window::JKEY; }
    | T_KKEY 
    { $$ = Window::KKEY; }
    | T_LKEY 
    { $$ = Window::LKEY; }
    | T_WKEY 
    { $$ = Window::WKEY; }
    | T_F1
    { $$ = Window::F1; }
    ;

//---------------------------------------------------------------------
if_block:
    statement_block_creator statement end_of_statement_block
    {
      $$ = $1;
    }
    | statement_block
    {

    }
    ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
    { 
      /* assert(false); */
      $$= $2;
    }
    ;

//---------------------------------------------------------------------
statement_block_creator:
    {
      /*assert(false);*/
      /* Need to create empty statement block and push it on the global
         stack declared at the start of this file */
      Statement_block* stmt_block = new Statement_block();
      global_stack.push(stmt_block);
      /* Need to pass something up tree*/
      $$ = stmt_block;      
    }
    ;

//---------------------------------------------------------------------
end_of_statement_block:
    {
      /* Pop a statement block off the stack when we see T_RBRACE */
      global_stack.pop();
    }
    ;

//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | empty
    ;

//---------------------------------------------------------------------
statement:
    if_statement
    | for_statement
    | assign_statement T_SEMIC
    | print_statement T_SEMIC
    | exit_statement T_SEMIC
    ;

//---------------------------------------------------------------------
if_statement:
    T_IF T_LPAREN expression T_RPAREN if_block %prec IF_NO_ELSE
    {
      /*if ($3->m_type != INT)
      {
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
      }
      else
      {
        If_stmt* if_stmt = new If_stmt($3, $5);
        global_stack.top()->m_statements.push_back(if_stmt);
      }*/
      If_stmt* if_stmt = new If_stmt($3, $5);
      global_stack.top()->m_statements.push_back(if_stmt);
    }
    | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block 
    {
      /*if ($3->m_type != INT)
      {
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
      }
      else
      {
        If_stmt* if_stmt = new If_stmt($3, $5, $7);
        global_stack.top()->m_statements.push_back(if_stmt);
      }*/
      If_stmt* if_stmt = new If_stmt($3, $5, $7);
      global_stack.top()->m_statements.push_back(if_stmt);
    }
    ;

//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN statement_block_creator assign_statement end_of_statement_block T_SEMIC expression T_SEMIC statement_block_creator assign_statement end_of_statement_block T_RPAREN statement_block
    {  
      if ($7->m_type != INT)
      {
        Error::error(Error::INVALID_TYPE_FOR_FOR_STMT_EXPRESSION);
      }
      For_stmt* for_stmt = new For_stmt($3,$9,$13,$7);
      global_stack.top()->m_statements.push_back(for_stmt); 
    }
    ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN
    {
      if ($3->m_type > 4)
      {
        Error::error(Error::INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION);
      }
      Print_stmt* print_stmt = new Print_stmt($1, $3);
      global_stack.top()->m_statements.push_back(print_stmt);      
    }
    ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN
    {
      if ($3->m_type != INT)
      {
        string s_value;
        if ($3->m_type == DOUBLE)
        {
          Error::error(Error::EXIT_STATUS_MUST_BE_AN_INTEGER, gpl_type_to_string($3->m_type));
        }
        else if ($3->m_type == STRING)
        {
          Error::error(Error::EXIT_STATUS_MUST_BE_AN_INTEGER, gpl_type_to_string($3->m_type));
        }
      }
      else
      {
        Exit_stmt* exit_stmt = new Exit_stmt($3, $1);
        global_stack.top()->m_statements.push_back(exit_stmt);
      }   
    }
    ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    {
      if ($1->m_type < $3->m_type)
      {
        if ($1->m_var_type == "GAME_OBJECT")
        {
          Error::error(Error::INVALID_LHS_OF_ASSIGNMENT,
          $1->m_symbol->m_name+"."+$1->m_param, gpl_type_to_string($3->m_type));
        }
        else
        {
          Error::error(Error::ASSIGNMENT_TYPE_ERROR, 
          gpl_type_to_string($1->m_type), gpl_type_to_string($3->m_type));
        }
      }
      else if ($1->m_type >= 16 && $1->m_type < 529)
      {
        Error::error(Error::INVALID_LHS_OF_ASSIGNMENT, $1->m_symbol->m_name,
               gpl_type_to_string($1->m_type));
      }
      else if ($1->m_type == ANIMATION_BLOCK && $1->m_var_type == "CONSTANT")
      {
        
        Error::error(Error::CANNOT_ASSIGN_TO_NON_MEMBER_ANIMATION_BLOCK,
               $1->m_symbol->m_name);
       cerr << "gpl.y895:: animation name is " << $1->m_symbol->m_name << endl;
      }
      else
      {
        cerr << "gpl.y 896 : 1 m_type = " << $1->m_type << endl;

       cerr << "gpl.y895:: var type is " << $1->m_var_type<< endl;
        Assignment_stmt* ass_stmt = new Assignment_stmt($1, $3, ASS_ASSIGN);
        global_stack.top()->m_statements.push_back(ass_stmt);
      }
    }
    | variable T_PLUS_ASSIGN expression
    {
      if ($1->m_type < $3->m_type)
      {
        if ($1->m_var_type == "GAME_OBJECT")
        {
          Error::error(Error::INVALID_LHS_OF_PLUS_ASSIGNMENT,
          $1->m_symbol->m_name+"."+$1->m_param, gpl_type_to_string($3->m_type));
        }
        else
        {
          Error::error(Error::PLUS_ASSIGNMENT_TYPE_ERROR, 
          gpl_type_to_string($1->m_type), gpl_type_to_string($3->m_type));
        }
      }
      else if ($1->m_type >= 16 && $1->m_type < 529)
      {
        Error::error(Error::INVALID_LHS_OF_PLUS_ASSIGNMENT, $1->m_symbol->m_name,
               gpl_type_to_string($1->m_type));
      }
      else
      {
        Assignment_stmt* plus_stmt = new Assignment_stmt($1, $3, ASS_PLUS);
        global_stack.top()->m_statements.push_back(plus_stmt); 
      }
    }
    | variable T_MINUS_ASSIGN expression
    {
      if ($1->m_type < $3->m_type)
      {
        if ($1->m_var_type == "GAME_OBJECT")
        {
          Error::error(Error::INVALID_LHS_OF_MINUS_ASSIGNMENT,
          $1->m_symbol->m_name+"."+$1->m_param, gpl_type_to_string($3->m_type));
        }
        else
        {
          Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR, 
          gpl_type_to_string($1->m_type), gpl_type_to_string($3->m_type));
        }
      }
      else if ($1->m_type == STRING)
      {
        if ($1->m_var_type == "GAME_OBJECT")
        {
          Error::error(Error::INVALID_LHS_OF_MINUS_ASSIGNMENT,
          $1->m_symbol->m_name+"."+$1->m_param, gpl_type_to_string($3->m_type));
        }
        else
        {
          Error::error(Error::INVALID_LHS_OF_MINUS_ASSIGNMENT, 
          $1->m_symbol->m_name, gpl_type_to_string($1->m_type));
        }
      }
      else
      {
        Assignment_stmt* plus_stmt = new Assignment_stmt($1, $3, ASS_MINUS);
        global_stack.top()->m_statements.push_back(plus_stmt); 
      }
    }
    | variable T_PLUS_PLUS
    {
      if ($1->m_type == DOUBLE)
      {
        Error::error(Error::INVALID_LHS_OF_PLUS_PLUS,
               $1->m_symbol->m_name, gpl_type_to_string($1->m_type));
      }
      if ($1->m_type == STRING)
      {
         Error::error(Error::INVALID_LHS_OF_PLUS_PLUS,
               $1->m_symbol->m_name, gpl_type_to_string($1->m_type));         
      }

      Assignment_stmt* stmt = new Assignment_stmt($1, NULL, ASS_PLUS_PLUS);
      global_stack.top()->m_statements.push_back(stmt); 
    }
    | variable T_MINUS_MINUS
    {
      if ($1->m_type == DOUBLE)
      {
        Error::error(Error::INVALID_LHS_OF_MINUS_MINUS,
               $1->m_symbol->m_name, gpl_type_to_string($1->m_type));
      }
      if ($1->m_type == STRING)
      {
         Error::error(Error::INVALID_LHS_OF_MINUS_MINUS,
               $1->m_symbol->m_name, gpl_type_to_string($1->m_type));         
      }

      Assignment_stmt* stmt = new Assignment_stmt($1, NULL, ASS_MINUS_MINUS); 
      global_stack.top()->m_statements.push_back(stmt); 
    }
    ;

//---------------------------------------------------------------------
variable:
    T_ID
    {
      Symbol *return_sym;
      if (Symbol_table::instance()->lookup(*$1))
      {
        return_sym = Symbol_table::instance()->lookup(*$1);
        if (return_sym->m_type == INT_ARRAY)
        {
          Error::error(Error::VARIABLE_IS_AN_ARRAY, *$1);
          $$ = new Variable("DUMMY");
        }
        else
        {
          $$ = new Variable(*$1);
        }
      }
      else
      {
        Error::error(Error::UNDECLARED_VARIABLE, *$1);
        $$ = new Variable("DUMMY");
      }
    }
    | T_ID T_LBRACKET expression T_RBRACKET
    {
      Expression *expr = $3;
      Symbol *ret_sym;
      if (expr->m_type == DOUBLE)
      {
        Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A double expression");
        $$ = new Variable("DUMMY");
      }
      else if (expr->m_type == STRING)
      {
        Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A string expression");
        $$ = new Variable("DUMMY");
      }
      else
      {
        if (Symbol_table::instance()->lookup(*$1))
        {
          ret_sym = Symbol_table::instance()->lookup(*$1);
          if (ret_sym->m_type == INT)
          {
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
            $$ = new Variable("DUMMY");
          }
          else
          {
            $$ = new Variable(*$1, $3);
          }
        }
        else
        {
          Error::error(Error::UNDECLARED_VARIABLE, *$1+"[]");
          $$ = new Variable("DUMMY");
        }
      }
    }
    | T_ID T_PERIOD T_ID
    {
      Symbol* symbol;
      symbol = Symbol_table::instance()->lookup(*$1);
      Status status;
      if (symbol != NULL)
      {
        if (!symbol->is_game_object())
        {
          Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
          $$ = new Variable("DUMMY");
        }
        else
        {
          Gpl_type temp_type;
          status = ((Game_object*)(symbol->m_value))->get_member_variable_type(*$3, temp_type);
          if (status == MEMBER_NOT_DECLARED)
          {
            Error::error(Error::UNDECLARED_MEMBER, *$1, *$3);
            $$ = new Variable("DUMMY");
          }
          else
          {
           $$ = new Variable(symbol->m_name, *$3);
          }
        }
      }
      else
      { 
        Error::error(Error::UNDECLARED_VARIABLE, *$1);
        $$ = new Variable("DUMMY");
      }
    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
    {
      Symbol* symbol;
      symbol = Symbol_table::instance()->lookup(*$1);
      Status status;
      if (symbol != NULL)
      {
        if (!(symbol->is_game_object()))
        {         
          Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
          $$ = new Variable("DUMMY");
        }
        else if ($3->m_type != INT)
        { 
          if ($3->m_type == DOUBLE)
          {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, 
                  "A double expression");
          }
          else if ($3->m_type == STRING)
          {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, 
                  "A string expression");           
          }
          else if ($3->m_type == ANIMATION_BLOCK)
          {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, 
                  "A animation_block expression");
          }
          else
          {
            cerr << "ERROR:: I have to error in checking expression type for";
            cerr << " game_object_params in the action." << endl;
          }
          $$ = new Variable("DUMMY");
        }
        else
        {
          $$ = new Variable(symbol->m_name, *$6, $3);
        }
      }
      else
      {
        Error::error(Error::UNDECLARED_VARIABLE, *$1);
        $$ = new Variable("DUMMY");
      }     
    }
    ;

//---------------------------------------------------------------------
expression:
    primary_expression
    { $$ = $1; } 
    | expression T_OR expression
    {
      if($1->m_type == STRING || $3->m_type == STRING)
      {
        if ($1->m_type == STRING)
        {
          Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||");
        }
        if ($3->m_type == STRING)
        {
          Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||");
        }
        $$ = new Expression(0, INT, NULL, NULL);
      }
      else 
      {
        $$ = new Expression(OR, INT, $1, $3);
      }
    }
    | expression T_AND expression 
    {
      if($1->m_type == STRING || $3->m_type == STRING)
      {
        if ($1->m_type == STRING)
        {
          Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&");
        }
        if ($3->m_type == STRING)
        {
          Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
        }
        $$ = new Expression(0, INT, NULL, NULL);
      }
      else
      {
        $$ = new Expression(AND, INT, $1, $3);
      }
    }
    | expression T_LESS_EQUAL expression
    {
      $$ = new Expression(LESS_EQUAL, INT, $1, $3);
    }
    | expression T_GREATER_EQUAL expression
    {
      $$ = new Expression(GREATER_EQUAL, INT, $1, $3);
    }
    | expression T_LESS expression 
    {
      $$ = new Expression(LESS_THAN, INT, $1, $3);
    }
    | expression T_GREATER  expression
    {
      $$ = new Expression(GREATER_THAN, INT, $1, $3);
    }
    | expression T_EQUAL expression
    {
      $$ = new Expression(EQUAL, INT, $1, $3);
    }
    | expression T_NOT_EQUAL expression
    {
      $$ = new Expression(NOT_EQUAL, INT, $1, $3);
    }
    | expression T_PLUS expression 
    {
      //cerr << "LEFT EXPR TYPE IS: " << $1->m_type << endl;
      //cerr << "RIGHT EXPR TYPE IS: " << $3->m_type << endl;
      
      if (($1->m_type > 4 && $1->m_type < 1025)||
          ($1->m_type > 1028))
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "+");
      }
      if (($3->m_type > 4 && $3->m_type < 1025)||
          ($3->m_type > 1028))
      { 
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "+");
      }
      $$ = new Expression(0, INT, NULL, NULL);

      if ($1->m_type == STRING || $3->m_type == STRING)
      {
        $$= new Expression(PLUS, STRING, $1, $3);
      }
      else if ($1->m_type == DOUBLE || $3->m_type == DOUBLE)
      {
        $$= new Expression(PLUS, DOUBLE, $1, $3);
      }
      else if ($1->m_type == INT && $1->m_type == INT)
      {
        $$= new Expression(PLUS, INT, $1, $3);
      }
      else if ($1->m_type == INT_ARRAY)
      {
        $$= new Expression(PLUS, INT, $1, $3);
      }
    /*  else
      {
        cerr << "ERROR::GPL.CPP: I CANNOT FIND EXPR TYPE!" << endl;
      }*/
    }
    | expression T_MINUS expression
    {
      if ($1->m_type == STRING || $3->m_type == STRING)
      {
        if ($1->m_type == STRING)
        {
          Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-");
        }
        if($3->m_type == STRING)
        {
          Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-");
        }
        $$ = new Expression(0, INT, NULL, NULL);
      }
      else
      {
        if ($1->m_type == DOUBLE || $3->m_type == DOUBLE)
        {
          $$ = new Expression(MINUS, DOUBLE, $1, $3);
        } 
        if ($1->m_type == INT && $3->m_type == INT)
        {
          $$ = new Expression(MINUS, INT, $1, $3);
        }
      }
    }
    | expression T_MULTIPLY expression
    {
      if ($1->m_type == STRING || $3->m_type == STRING)
      {
        if ($1->m_type == STRING)
        {
          Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*");
        }
        if($3->m_type == STRING)
        {
          Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*");
        }
        $$ = new Expression(0, INT, NULL, NULL);
      }
      else
      {
        if ($1->m_type == DOUBLE || $3->m_type == DOUBLE)
        {
          $$ = new Expression(MULTIPLY, DOUBLE, $1, $3);
        }
        else if ($1->m_type == INT && $3->m_type == INT)
        {
          $$ = new Expression(MULTIPLY, INT, $1, $3);
        }
      }
    }
    | expression T_DIVIDE expression
    {
      if ($1->m_type == STRING || $3->m_type == STRING)
      {
        if ($1->m_type == STRING)
        {
          Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/");
        }
        if($3->m_type == STRING)
        {
          Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/");
        }
        $$ = new Expression(0, INT, NULL, NULL);
      }
      else 
      {
        if ($1->m_type == DOUBLE || $3->m_type == DOUBLE)
        {
          if ($3->eval_double() == 0.0)
          {
            Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME, "/");
            $$ = new Expression(0, INT, NULL, NULL);
          }
          else
          {
            $$ = new Expression(DIVIDE, DOUBLE, $1, $3);
          }
        }
        if ($1->m_type == INT && $3->m_type == INT)
        {
          if ($3->eval_int() == 0)
          {
            Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME, "/");
            $$ = new Expression(0, INT, NULL, NULL);
          }
          else
          {
            $$ = new Expression(DIVIDE, INT, $1, $3);
          }
        }
      }
    }
    | expression T_MOD expression
    {
      if ($1->m_type == DOUBLE || $1->m_type == STRING || 
            $3->m_type == DOUBLE || $3->m_type == STRING)
      {
        if ($1->m_type == DOUBLE || $1->m_type == STRING)
        {
          Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%");
        }
        if ($3->m_type == DOUBLE || $3->m_type == STRING)
        {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%");
        }
        $$ = new Expression(0, INT, NULL, NULL);
      } 
      if ($1->m_type == INT && $3->m_type == INT)
      {
        if ($3->eval_int() == 0)
        {
          Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME, "%");
          $$ = new Expression(0, INT, NULL, NULL);
        }
        else
        {
          $$ = new Expression(MOD, INT, $1, $3);
        }
      }
    }
    | T_MINUS  expression %prec UNARY_OPS
    {
      if ($2->m_type == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-");
        $$ = new Expression(0, INT, NULL, NULL); 
      }
      else if ($2->m_type == INT)
      {
        $$ = new Expression(UNARY_MINUS, INT, $2, NULL);
      }
      else
      {
        $$ = new Expression(UNARY_MINUS, DOUBLE, $2, NULL);
      }
    }
    | T_NOT  expression  %prec UNARY_OPS
    {
      if ($2->m_type == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!");
        $$ = new Expression(0, INT, NULL, NULL);
      }
      $$ = new Expression(NOT, INT, $2, NULL);
    }
    | math_operator T_LPAREN expression T_RPAREN
    {
      Expression *expr = $3;
      if ($3->m_type == STRING)
      {
        switch ($1)
        {
          case COS:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "cos");
            break;
          case SIN:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "sin");
            break;
          case TAN:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "tan");
            break;
          case ACOS:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "acos");
            break;
          case ASIN:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "asin");
            break;
          case ATAN:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "atan");
            break;
          case SQRT:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "sqrt");
            break;
          case ABS:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "abs");
            break;
          case FLOOR:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "floor");
            break;
          case RANDOM:
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "random");
            break;
          default:
            break;
        }
        $$ = new Expression(0, INT, NULL, NULL);
      }
      else if ($1 == RANDOM)
      {
       $$ = new Expression($1, INT, expr, NULL);         
      } 
      else if ($1 == FLOOR)
      {
        if ($3->m_type == DOUBLE)
        {
          $$ = new Expression($1, INT, expr, NULL);
        }
        else
        {
          $$ = new Expression($1, INT, expr, NULL);
        }
      }
      else if ($1 == ABS)
      {
        if ($3->m_type == INT)
        {
          $$ = new Expression($1, INT, expr, NULL);
        }
        else 
        {
          $$ = new Expression($1, DOUBLE, expr, NULL);
        }
      }
      else
      {
        //Cannot be a string at all
        assert($3->m_type != STRING);
       
        if ($3)
        { 
          $$ = new Expression($1, DOUBLE, expr, NULL);
        }
        else
        {
          cerr << "ERROR: NO EXPRESSION DECLARED IN MATH_OPERS" << endl;
        }
      }
    }
    | variable geometric_operator variable
    {
      if ($1->m_symbol->is_game_object() == false ||
          $3->m_symbol->is_game_object() == false)
      {
        if($1->m_symbol->is_game_object() == false)
          Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, $1->m_symbol->get_name());
        if($3->m_symbol->is_game_object() == false)
          Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, $3->m_symbol->get_name());
        $$ = new Expression(0, INT, NULL, NULL);
      }
      else
      { 
        /*cerr << "COUNT: " << counter << endl;
        cerr << "GPL 1478: lhs m_type = " << $1->m_type << endl;
        cerr << "--rhs_m_type = " << $3->m_type << endl;*/
        $$ = new Expression($2->m_oper, INT, new Expression($1), new Expression($3));
      }
    /*  cerr << "GPL.y:1478: var_lhs m_type is : " << $1->m_symbol->is_game_object() << endl;*/
    } 
    ;

//---------------------------------------------------------------------
primary_expression:
    T_LPAREN  expression T_RPAREN
    { $$ = $2; }
    | variable
    { $$ = new Expression($1); }
    | T_INT_CONSTANT
    { $$ = new Expression($1, INT, NULL, NULL); }
    | T_TRUE
    { $$ = new Expression(1, INT, NULL, NULL); }
    | T_FALSE
    { $$ = new Expression(0, INT, NULL, NULL); }
    | T_DOUBLE_CONSTANT
    { $$ = new Expression($1, DOUBLE, NULL, NULL); }
    | T_STRING_CONSTANT
    { $$ = new Expression($1, STRING, NULL, NULL); }
    ;

//---------------------------------------------------------------------
geometric_operator:
    T_TOUCHES
    {
      $$ = new Expression(TOUCHES, INT, NULL, NULL);
    }
    | T_NEAR
    {
      $$ = new Expression(NEAR, INT, NULL, NULL);
    }
    ;

//---------------------------------------------------------------------
math_operator:
    T_SIN
    { $$ = SIN; }
    | T_COS
    { $$ = COS; }
    | T_TAN
    { $$ = TAN; }
    | T_ASIN
    { $$ = ASIN; }
    | T_ACOS
    { $$ = ACOS; }
    | T_ATAN
    { $$ = ATAN; }
    | T_SQRT
    { $$ = SQRT; }
    | T_ABS
    { $$ = ABS; }
    | T_FLOOR
    { $$ = FLOOR; }
    | T_RANDOM
    { $$ = RANDOM; }
    ;

//---------------------------------------------------------------------
empty:
    {
    }
    // empty goes to nothing so that you can use empty in productions

