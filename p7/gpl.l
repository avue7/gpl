%{

#include "error.h"    // gpl file, using now to get use to it
#include "parser.h"   // gpl file, using now to get use to it
#include "expression.h"
#include "gpl_type.h"
#include "symbol_table.h"
#include <string>
#include <ctype.h>
#include <iostream>
using namespace std;

Error error_handler; // error reporting object

// The following variable keeps track of what input line flex is reading.
// It will be used for reporting the line numbers of errors.
// 
// It will be used by other parts of the program via the "extern" construct
//   If another .cpp file declares "extern int line_count" that line_count
//   in that file will be the line_count in this file (it becomes global)
int line_count = 1;

void get_int_value()
{
  // assumes that the string in yytext is an integer
  // convert the string yytext into an integer
  // put the int into global union used to send values to the parser (record.y)
  // the union and its union_int field are declared in record.y
  yylval.union_int = atoi(yytext);
}
 
// Adding get_double_value from P2 #2 to account for doubles
void get_double_value()
{
  yylval.union_double = atof(yytext);
}

void get_string_value()
{
  // Would like to put a string in the union, but the way the union works
  // it has to be a pointer to a string.
  // This is a potential memory leak.  Think carefully about where and when
  // this memory should be deleted.
  yylval.union_string = new string(yytext);
}

// Adding this from P2 #3 to account for string constants (those having a quotation mark)
// Need to get rid of quation marks so new string (yytext) will point to first element of array
//  do new string (yytext + 1) to point to next element of the array.
// Now we have to get rid of last quotation. YYTEXT is a c-style string so we have a null pointer
//  at the end. Need to get the last quotation out of the string by doing strlen(yytext) - 1.
void get_string_constant_value()
{
  yytext[strlen(yytext) - 1]='\0';  // Moving the null terminator to the last quotation's place
  yylval.union_string_constant = new string(yytext + 1);
}

void get_line_number()
{
  yylval.union_line_number = line_count;
}

void error()
{
  // have the error handling object report the problem
  // note: it uses line_count as a global variable
  error_handler.error(Error::ILLEGAL_TOKEN, yytext);

  // create a string to hold the current text
  // put that string in the yylval union so it can be used by parser (.y file)
  yylval.union_string = new string(yytext);
}


// the %} below indicates the end of the C/C++ code section

%}

%%

[\n]            line_count++; // count the lines for error reporting
[ \t\r]         ; // ignore spaces, tabs and the microsoft line feed (\r)

"int"               return T_INT;               
"double"            return T_DOUBLE;            
"string"            return T_STRING;            
"triangle"          return T_TRIANGLE;          
"pixmap"            return T_PIXMAP;            
"circle"            return T_CIRCLE;           
"rectangle"         return T_RECTANGLE;         
"textbox"           return T_TEXTBOX;          

"initialization"    return T_INITIALIZATION;    
"termination"       return T_TERMINATION;       

"true"              return T_TRUE;              
"false"             return T_FALSE;             

"touches"           return T_TOUCHES;          
"near"              return T_NEAR;                    
"animation"         return T_ANIMATION;         

"if"                return T_IF;                
"for"               return T_FOR;               
"else"              return T_ELSE;

"("                 return T_LPAREN;            
")"                 return T_RPAREN;            
"{"                 return T_LBRACE;            
"}"                 return T_RBRACE;            
"["                 return T_LBRACKET;          
"]"                 return T_RBRACKET;          
";"                 return T_SEMIC;             
","                 return T_COMMA;             
"."                 return T_PERIOD;            
                    
"="                 return T_ASSIGN;            
"+="                return T_PLUS_ASSIGN;       
"-="                return T_MINUS_ASSIGN;      
"++"                return T_PLUS_PLUS;         
"--"                return T_MINUS_MINUS; 

"*"                 return T_MULTIPLY;          
"/"                 return T_DIVIDE;            
"%"                 return T_MOD;               
"+"                 return T_PLUS;              
"-"                 return T_MINUS;             
"sin"               return T_SIN;               
"cos"               return T_COS;               
"tan"               return T_TAN;               
"asin"              return T_ASIN;              
"acos"              return T_ACOS;              
"atan"              return T_ATAN;              
"sqrt"              return T_SQRT;              
"floor"             return T_FLOOR;             
"abs"               return T_ABS;               
"random"            return T_RANDOM; 

"<"                 return T_LESS;              
">"                 return T_GREATER;           
"<="                return T_LESS_EQUAL;        
">="                return T_GREATER_EQUAL;     
"=="                return T_EQUAL;             
"!="                return T_NOT_EQUAL;

"&&"                return T_AND;               
"||"                return T_OR;                
"!"                 return T_NOT;  

"on"                return T_ON;                
"space"             return T_SPACE;             
"leftarrow"         return T_LEFTARROW;         
"rightarrow"        return T_RIGHTARROW;        
"uparrow"           return T_UPARROW;           
"downarrow"         return T_DOWNARROW;         
"leftmouse_down"    return T_LEFTMOUSE_DOWN;    
"middlemouse_down"  return T_MIDDLEMOUSE_DOWN;  
"rightmouse_down"   return T_RIGHTMOUSE_DOWN;   
"leftmouse_up"      return T_LEFTMOUSE_UP;      
"middlemouse_up"    return T_MIDDLEMOUSE_UP;    
"rightmouse_up"     return T_RIGHTMOUSE_UP;     
"mouse_move"        return T_MOUSE_MOVE;        
"mouse_drag"        return T_MOUSE_DRAG; 

"f1"                return T_F1;                
"akey"              return T_AKEY;              
"skey"              return T_SKEY;              
"dkey"              return T_DKEY;              
"fkey"              return T_FKEY;              
"hkey"              return T_HKEY;              
"jkey"              return T_JKEY;              
"kkey"              return T_KKEY;              
"lkey"              return T_LKEY;              
"wkey"              return T_WKEY; 

[/][/][^\n]*\n                      line_count++;
"forward"                           get_int_value(); return T_FORWARD;
"print"                             get_line_number(); return T_PRINT;
"exit"                              get_int_value(); return T_EXIT;
[0-9]+                              get_int_value(); return T_INT_CONSTANT;
([0-9]*\.+[0-9]+|[0-9]+\.+[0-9]*)   get_double_value(); return T_DOUBLE_CONSTANT;
\"[^\"\n]*\]*\"                     get_string_constant_value(); return T_STRING_CONSTANT;
[A-Za-z_][A-Za-z0-9_]*              get_string_value(); return T_ID;

.                                   error(); return T_ERROR;

