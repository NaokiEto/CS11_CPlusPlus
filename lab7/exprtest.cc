#include <iostream>

#include "environment.hh"
#include "expressions.hh"


using namespace std;


/*
 * This is a very simple test program whose main purpose is to help students
 * identify compile errors with their expression class hierarchy, OUTSIDE of
 * the parsing and lexing code, where the source of errors will be easier to
 * identify.  This test is by no means exhaustive, but it uses a handful of
 * the expression nodes to evaluate a few things.  Further testing within the
 * alge program is essential.
 */
int main() {

  cout << "Running some simple tests on your expression classes." << endl;

  Environment env;
  env.setSymbolValue("x", 0.4);
  env.setSymbolValue("y", -3.1);

  Expression *pExp1 = new Value(25.3);

  cout << "Value(25.3) evaluates to " << pExp1->evaluate(env) << endl;

  Expression *pExp2 = new Symbol("x");

  Expression *pExp3 = new DivOper(pExp1, pExp2);
  cout << "25.3 / 0.4 = " << pExp3->evaluate(env) << " (should be 63.25)"
       << endl;

  Expression *pExp4 = new SubOper(new Symbol("y"), new NegOper(pExp3));
  cout << "-3.1 - -(25.3 / 0.4) = " << pExp4->evaluate(env)
       << " (should be 60.15)" << endl;

  // Since all the other expressions are children of pExp4, deleting pExp4
  // should clean *everything* up.
  delete pExp4;

  return 0;
}


