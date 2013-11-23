#include <iostream>

#include "alge.hh"
#include "commands.hh"
#include "alge-parser.tab.hh"

using namespace std;


extern Command *parsed_command;


/**
 * Simple error-reporting function.  Called by yyparse on error.
 **/
void yyerror(const char *msg) {
  cerr << "ERROR:  " << msg << endl;
}


int main() {
  string line;
  Environment env;

  cout << "Welcome to alge, the Algebra calculator." << endl << endl;

  while (true) {
    cout << "COMMAND:  ";
    
    getline(cin, line);
    
    // Get outta the program if we got EOF, or if input was "quit".
    if (!cin || line == "quit")
      break;
    
    scan_begin(line);
    
    int rc = yyparse();
    
    switch (rc) {
    case 0:
      // Parse succeeded.  Try to run the beast.
      try {
        parsed_command->run(env);
      }
      catch (runtime_error &re) {
        cout << "ERROR:  " << re.what() << endl << endl;
      }
      catch (...) {
        cout << "UNRECOGNIZED ERROR.  :(" << endl << endl;
      }

      break;

    case 1:
      cout << "PARSE FAILED.  :(" << endl << endl;
      break;

    case 2:
      cout << "Out of memory.  What did you type?!" << endl << endl;
      break;

    default:
      // Allegedly, that's all that yyparse() will return...
      assert(false);
    }
    
    scan_end();
  }

  cout << endl << "Goodbye!" << endl << endl;
}

