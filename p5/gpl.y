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
      if ($3)
      {
        if ($1 == INT)
        { 
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
          Symbol_table::instance()->insert_symbol(symbol);
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
          Symbol_table::instance()->insert_symbol(symbol);
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
          Symbol_table::instance()->insert_symbol(symbol);
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
        Symbol_table::instance()->insert_symbol(symbol);
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
          Symbol_table::instance()->insert_symbol(symbol);
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
    object_type T_ID T_LPAREN parameter_list_or_empty T_RPAREN
    | object_type T_ID T_LBRACKET expression T_RBRACKET
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    | T_PIXMAP
    | T_CIRCLE
    | T_RECTANGLE
    | T_TEXTBOX
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
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
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
    ;

//---------------------------------------------------------------------
termination_block:
    T_TERMINATION statement_block
    ;

//---------------------------------------------------------------------
animation_block:
    T_ANIMATION T_ID T_LPAREN check_animation_parameter T_RPAREN T_LBRACE statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    ;

//---------------------------------------------------------------------
check_animation_parameter:
    T_TRIANGLE T_ID
    | T_PIXMAP T_ID
    | T_CIRCLE T_ID
    | T_RECTANGLE T_ID
    | T_TEXTBOX T_ID
    ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block
    ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
    | T_UPARROW
    | T_DOWNARROW
    | T_LEFTARROW
    | T_RIGHTARROW
    | T_LEFTMOUSE_DOWN
    | T_MIDDLEMOUSE_DOWN
    | T_RIGHTMOUSE_DOWN
    | T_LEFTMOUSE_UP
    | T_MIDDLEMOUSE_UP
    | T_RIGHTMOUSE_UP
    | T_MOUSE_MOVE
    | T_MOUSE_DRAG
    | T_AKEY 
    | T_SKEY 
    | T_DKEY 
    | T_FKEY 
    | T_HKEY 
    | T_JKEY 
    | T_KKEY 
    | T_LKEY 
    | T_WKEY 
    | T_F1
    ;

//---------------------------------------------------------------------
if_block:
    statement_block_creator statement end_of_statement_block
    | statement_block
    ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
statement_block_creator:
    // this goes to nothing so that you can put an action here in p7
    ;

//---------------------------------------------------------------------
end_of_statement_block:
    // this goes to nothing so that you can put an action here in p7
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
    | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block 
    ;

//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN statement_block_creator assign_statement end_of_statement_block T_SEMIC expression T_SEMIC statement_block_creator assign_statement end_of_statement_block T_RPAREN statement_block
    ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    | variable T_PLUS_ASSIGN expression
    | variable T_MINUS_ASSIGN expression
    | variable T_PLUS_PLUS
    | variable T_MINUS_MINUS
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
            int index_size;
            index_size = $3->eval_int();
            if (index_size > (ret_sym->m_size)-1)
            {
              Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, *$1, std::to_string(index_size));
              $$ = new Variable("DUMMY");
            }
            else
            {
              $$ = new Variable(*$1, $3);
            }
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
    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
    {
    }
    ;

//---------------------------------------------------------------------
expression:
    primary_expression
    { $$ = $1; } 
    | expression T_OR expression
    {
      if ($1->m_type == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||");
        $$ = new Expression(0, INT, NULL, NULL);
        if ($3->m_type == STRING)
        {
          Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||");
          $$ = new Expression(0, INT, NULL, NULL);
        }
      }
      else if ($3->m_type == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||");
        $$ = new Expression(0, INT, NULL, NULL);
      }
      else 
      {
        $$ = new Expression(OR, INT, $1, $3);
      }
    }
    | expression T_AND expression 
    {
      if ($1->m_type == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&");
        $$ = new Expression(0, INT, NULL, NULL);
        if ($3->m_type == STRING)
        {
          Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
          $$ = new Expression(0, INT, NULL, NULL);
        }
      }
      else if ($3->m_type == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
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
    }
    | expression T_MINUS expression
    {
      if ($1->m_type == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-");
        $$ = new Expression(0, INT, NULL, NULL); 
      }
      if($3->m_type == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-");
        $$ = new Expression(0, INT, NULL, NULL);
      }
      if ($1->m_type == DOUBLE || $3->m_type == DOUBLE)
      {
        $$ = new Expression(MINUS, DOUBLE, $1, $3);
      } 
      if ($1->m_type == INT && $3->m_type == INT)
      {
        $$ = new Expression(MINUS, INT, $1, $3);
      }
    }
    | expression T_MULTIPLY expression
    {
      if ($1->m_type == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*");
        $$ = new Expression(0, INT, NULL, NULL);
      }
      if($3->m_type == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*");
        $$ = new Expression(0, INT, NULL, NULL);
      }
      if ($1->m_type == DOUBLE || $3->m_type == DOUBLE)
      {
        $$ = new Expression(MULTIPLY, DOUBLE, $1, $3);
      }
      if ($1->m_type == INT && $3->m_type == INT)
      {
        $$ = new Expression(MULTIPLY, INT, $1, $3);
      }
    }
    | expression T_DIVIDE expression
    {
      if ($1->m_type == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/");
        $$ = new Expression(0, INT, NULL, NULL);
      }
      if($3->m_type == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/");
        $$ = new Expression(0, INT, NULL, NULL);
      }
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
    | expression T_MOD expression
    {
      if ($1->m_type == DOUBLE || $1->m_type == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%");
        $$ = new Expression(0, INT, NULL, NULL);
      }
      if ($3->m_type == DOUBLE || $3->m_type == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%");
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
        /* Check the Random for any values < 1 since any value 
           < 1 is not legal. In p6 need to change this to default to 2 */
        if ($3->m_type == DOUBLE)
        {
           if ($3->eval_double() < 1)
           {
             stringstream ss;
             double value;
             value = $3->eval_double();
             ss << value;
             Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, ss.str());
             $$ = new Expression(0, INT, NULL, NULL);
           }
           else
           {
             $$ = new Expression($1, INT, expr, NULL);
           }  
        }
        else if ($3->m_type == INT)
        {
           if ($3->eval_int() < 1)
           {
             stringstream ss;
             int value;
             value = $3->eval_double();
             ss << value;
             Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, ss.str());
             $$ = new Expression(0, INT, NULL, NULL);
           }
           else
           {
             $$ = new Expression($1, INT, expr, NULL);
           }
        }
      /*$$ = new Expression($1, $3->m_type, expr, NULL);*/
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
    | T_NEAR
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
    // when you want a production to go to nothing
    ;
