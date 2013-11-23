#ifndef ALGE_HH
#define ALGE_HH

#include <string>

int yyparse();
void yyerror(const char *msg);

// Defined in alge-scanner.flex.

void scan_begin(const std::string &line);
void scan_end();

#endif // ALGE_HH

