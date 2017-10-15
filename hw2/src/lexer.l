%option noyywrap
%{
#include <stdio.h>
#include "header.h"

int linenumber;
symtab * lookup();
symtab * ptr;
void     insertID();
void    printSymTab();

#define INT       10
#define FLOAT     11
#define STRING    12
#define COMMENT   13
#define OP_ADD    14
#define OP_SUB    15
#define OP_DIV    16
#define OP_MUL    17
#define OP_LT     18
#define OP_GT     19
#define OP_GE     20
#define OP_LE     21
#define OP_NE     22
#define OP_EQ     23
#define OP_OR     24
#define OP_AND    25
#define OP_NOT    26
#define OP_ASSIGN 27
#define MK_LPAREN 28
#define MK_RPAREN 29
#define MK_LBRACK 30
#define MK_RBRACK 31
#define MK_LBRACE 32
#define MK_RBRACE 33
#define ERROR     100


%}

letter          [A-Za-z]
digit           [0-9]
hex             [a-fA-F0-9]
hexprefix       (0x|0X)
exp             [Ee][+-]?{digit}+
bin_exp         [Pp][+-]?{digit}+
fsuffix         (f|F|l|L)
ID              {letter}({letter}|{digit}|"_")*
WS              [ \t]+
Int_constant    {digit}+
Float_dec1      {digit}+{exp}
Float_dec2      {digit}*"."{digit}+({exp})?
Float_dec3      {digit}+"."{digit}*({exp})?
Float_hex1      {hexprefix}{hex}+{bin_exp}
Float_hex2      {hexprefix}{hex}*"."{hex}+({bin_exp})?
Float_hex3      {hexprefix}{hex}+"."{hex}*({bin_exp})?
Float_constant  [+-]?({Float_dec1}|{Float_dec2}|{Float_dec3}|{Float_hex1}|{Float_hex2}|{Float_hex3})({fsuffix})?
String_constant \".*\"
comment         ("/*"[^*]*[*]+([^*/][^*]*[*]+)*"/"|"//".*)

OP_add          "+"
OP_sub          "-"
OP_div          "/"
OP_mul          "*"
OP_lt           "<"
OP_gt           ">"
OP_ge           ">="
OP_le           "<="
OP_ne           "!="
OP_eq           "=="
OP_or           "||"
OP_and          "&&"
OP_not          "!"
OP_assign       "="

newline         "\n"

DL_lparen       "("
DL_rparen       ")"
DL_lbrack       "["
DL_rbrack       "]"
DL_lbrace       "{"
DL_rbrace       "}"
DL_comma        ","
DL_semicol      ";"
DL_dot          "."

error           .

%%

{WS}              {}
{Int_constant}    /* return INT; */
{Float_constant}  /* return FLOAT; */
{String_constant} /* return STRING; */
{comment}         puts(yytext);/* return COMMENT; */
{ID}              {
  ptr = lookup(yytext);
  if (ptr == NULL)
    insertID(yytext);
  else
    ptr->counter++;
                  }

{OP_add}          /* return OP_ADD; */
{OP_sub}          /* return OP_SUB; */
{OP_div}          /* return OP_DIV; */
{OP_mul}          /* return OP_MUL; */
{OP_lt}           /* return OP_LT; */
{OP_gt}           /* return OP_GT; */
{OP_ge}           /* return OP_GE; */
{OP_le}           /* return OP_LE; */
{OP_ne}           /* return OP_NE; */
{OP_eq}           /* return OP_EQ; */
{OP_or}           /* return OP_OR; */
{OP_and}          /* return OP_AND; */
{OP_not}          /* return OP_NOT; */
{OP_assign}       /* return OP_ASSIGN; */
{DL_lparen}       /* return MK_LPAREN; */
{DL_rparen}       /* return MK_RPAREN; */
{DL_lbrack}       /* return MK_LBRACK; */
{DL_rbrack}       /* return MK_RBRACK; */
{DL_lbrace}       /* return MK_LBRACE; */
{DL_rbrace}       /* return MK_RBRACE; */
{DL_comma}        {}
{DL_semicol}      {}
{newline}         linenumber += 1;
{error}           {
  printf("ERR %s\n", yytext);
  exit(ERROR);
  return ERROR;
                  }


%%

main(int argc, char **argv)
{
  argc--; ++argv;
  if (argc > 0)
    yyin = fopen(argv[0], "r");
  else
    yyin = stdin;
  yylex();
  printSymTab();
}

