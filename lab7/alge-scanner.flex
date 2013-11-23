%{
#include <cstdlib>
#include <errno.h>
#include <string>

#include "alge.hh"
#include "expressions.hh"
#include "commands.hh"
#include "alge-parser.tab.hh"

%}

%option noyywrap nounput interactive

digit	[0-9]

id	[a-zA-Z][a-zA-Z_0-9]*
num	[-+]?{digit}+\.?({digit}+)?

ws	[ \t]

%{
/* #define YY_USER_ACTION  yylloc->columns(yyleng); */
%}
%%
%{
/* yylloc->step(); */
%}

{ws}+		/* yylloc->step(); */
[\n]+		/* yylloc->lines(yyleng); yylloc->step(); */

[=\-+*^!/()]	return yytext[0];

{id}	yylval.sval = new std::string(yytext); return TOKEN_IDENTIFIER;

{num}	{
	  double d;
	  char *p_end;

	  d = strtod(yytext, &p_end);
	  if (p_end == yytext) {
	    yyerror( /* *yylloc, */ "could not parse number");
	  }
	  yylval.dval = d;
	  return TOKEN_NUMBER;
	}

.	yyerror( /* *yylloc, */ "invalid character");
%%


void scan_begin(const std::string &line)
{
  // yy_scan_string COPIES the input data, so this is OK!
  /*yy_bufstate =*/ yy_scan_string(line.c_str());
}

void scan_end()
{
  /*yy_delete_buffer(yy_bufstate);*/
}


