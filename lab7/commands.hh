#ifndef _COMMANDS_HH_
#define _COMMANDS_HH_

#include "environment.hh"
#include "expressions.hh"
#include <iostream>

using namespace std;

// Base class which provides an abstraction of what all commands should be 
// able to do
class Command
{
    public:
    // Command is a generic abstraction, so it shouldn't provide any 
    // implementation for run
    virtual void run(Environment &env)
    {
    }

    // Virtual destructor
    virtual ~Command()
    {
    }
};

// This class just evaluates an expression and then prints out the 
// result.
class PrintCommand: public Command
{
    private:
    // Pointer to the expression to print
    Expression* expPrint;

    public:
    // A single constructor that takes a pointer to an expression to store
    PrintCommand(Expression *exp)
    {
        assert(exp != NULL);
        expPrint = exp;
    }

    // Evaluate the expression, then print the result.
    void run(Environment &env)
    {
        cout << " = " << expPrint->evaluate(env) << endl;
    }

    // Destructor (delete the one pointer)
    ~PrintCommand()
    {
        delete expPrint;
    }
};

class AssignCommand: public Command
{
    private:
    // symbol to assign to
    Symbol* symAssign;
    // value to assign to
    Expression* expAssign;

    public:
    // A constructor that takes in pointers to symbol and expression to store
    AssignCommand(Symbol* sym, Expression* exp)
    {
        assert(sym != NULL);
        assert(exp != NULL);

        symAssign = sym;
        expAssign = exp;
    }

    void run(Environment &env)
    {
        // Evaluate the expression, then store the result
        // Get the name of the symbol and store
        // Set the symbol equal to the value
        env.setSymbolValue(symAssign->getName(), expAssign->evaluate(env));
        cout << symAssign->getName() << " = " << expAssign->evaluate(env) << endl;
    }    

    // Destructor (delete the two pointers)
    ~AssignCommand()
    {
        delete symAssign;
        delete expAssign;
    }
};

#endif // _COMMANDS_HH_
