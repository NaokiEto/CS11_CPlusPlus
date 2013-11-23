#ifndef _EXPRESSIONS_HH_
#define _EXPRESSIONS_HH_

#include <string>
#include "environment.hh"
#include <cassert>
#include <cmath>

// A base class which declares what every single expression will provide
class Expression
{
    public:
    // Pure virtual function for the evaluation of expressions
    virtual double evaluate(const Environment &env) const = 0;

    // Virtual destructor
    virtual ~Expression()
    {
    }
};

// Class which represents any literal numeric value specified in an expression
class Value: public Expression
{
    private:
    // Actual numeric value that was specified in the expression
    double numval;

    public:
    // A single constructor that takes the value to store
    Value(double num)
    {
        numval = num;
    }

    // Evaluate the value, which is just the value
    double evaluate(const Environment &env) const
    {
        return numval;
    }
};

// Class which represents a symbol in an expression, like pi or x.
class Symbol: public Expression
{
    private:
    // the name of the symbol
    string name;
    
    public:
    // A single constructor that takes the name to store
    Symbol(string nam)
    {
        name = nam;
    }

    // Accessor for the name
    string getName() const
    {
        return name;
    }

    // Get the value corresponding to the symbol
    double evaluate(const Environment &env) const
    {
        double val = env.getSymbolValue(name);
        return val;
    }
};

// Class that provides the common features of all binary operators
class BinaryOperator: public Expression
{
    // protected so the subclasses can access them
    protected:
    // left side expression of binary operator
    Expression *left;
    // right side expression of binary operator
    Expression *right;

    public:
    // A single constructor that takes the pointers to the left/right
    BinaryOperator(Expression *pLHS, Expression *pRHS)
    {
        // Make sure the pointers aren't NULL
        assert(pLHS != NULL);
        assert(pRHS != NULL);

        // set the left pointer to point to the same pointee as pLHS
        left = pLHS;
        // set the right pointer to point to the same pointee as pRHS
        right = pRHS;
    }

    // Accessor to get the left pointer
    Expression* getLeft() const
    {
        return left;
    }

    // Accessor to get the right pointer
    Expression* getRight() const
    {
        return right;
    }
    
    // Destructor (delete the two pointers)
    ~BinaryOperator()
    {
        delete left;
        delete right;
    }
};

// Class for the binary adding operation
class AddOper: public BinaryOperator
{
    public:
    // A single constructor that takes the pointers to the left/right
    AddOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS)
    {
        // Intentionally empty, since the construction is taken care of
        // in BinaryOperator
    }

    // Evaluate the addition operation
    double evaluate(const Environment &env) const
    {
        return left->evaluate(env) + right->evaluate(env);
    }
};

// Class for the binary subtraction operation
class SubOper: public BinaryOperator
{
    public:
    SubOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS)
    {
        // Intentionally empty, since the construction is taken care of
        // in BinaryOperator  
    }

    // Evaluate the subtraction operation
    double evaluate(const Environment &env) const
    {
        return left->evaluate(env) - right->evaluate(env);
    }
};

// Class for the binary multiplication operation
class MulOper: public BinaryOperator
{
    public:
    MulOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS)
    {
        // Intentionally empty, since the construction is taken care of
        // in BinaryOperator 
    }

    // Evaluate the multiplication operation
    double evaluate(const Environment &env) const
    {
        return left->evaluate(env) * right->evaluate(env);
    }
};

// Class for the binary division operation
class DivOper: public BinaryOperator
{
    public:
    DivOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS)
    {
        // Intentionally empty, since the construction is taken care of
        // in BinaryOperator 
    }

    // Evaluate the division operation
    double evaluate(const Environment &env) const
    {
        if (right->evaluate(env) == 0)
        {
            throw runtime_error("Cannot divide by 0!\n");
        }
        else
        {
            return left->evaluate(env) / right->evaluate(env);
        }
    }
};

// Class for the binary exponential operation
class ExpOper: public BinaryOperator
{
    public:
    ExpOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS)
    {
        // Intentionally empty, since the construction is taken care of
        // in BinaryOperator 
    }

    // Evaluate the division operation
    double evaluate(const Environment &env) const
    {
        return pow(left->evaluate(env), right->evaluate(env));
    }
};

// Class that provides the common features of all binary operators
class UnaryOperator: public Expression
{
    // protected so the subclasses can access them
    protected:
    // right side expression of binary operator
    Expression *exp;

    public:
    // A single constructor that takes the pointers to the left/right
    UnaryOperator(Expression *express)
    {
        // Make sure the pointers aren't NULL
        assert(express != NULL);

        // set the right pointer to point to the same pointee as pRHS
        exp = express;
    }

    // Accessor to get the left pointer
    Expression* getExpression() const
    {
        return exp;
    }
    
    // Destructor (delete the one pointer)
    ~UnaryOperator()
    {
        delete exp;
    }
};

class NegOper: public UnaryOperator
{
    public:
    // A single constructor that takes the pointers to a expression
    NegOper(Expression *express): UnaryOperator(express)
    {
        // Intentionally empty, since the construction is taken care of
        // in UnaryOperator
    }
    
    // Evaluate the negative operation
    double evaluate(const Environment &env) const
    {
        return exp->evaluate(env) * -1;
    }
};

#endif // _EXPRESSIONS_HH_
