#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdexcept>      // std::overflow, underflow
#include "heap.hh"
using namespace std;

/* This function is for testing the string type of template */
bool testString()
{
    Heap <string, 10> stringtest;
    int i;
    string laststr;

    /* 10 strings to put in the heap*/
    /* They form 3 separate thoughts */
    string s0 = "Has to";
    string s1 = "my Lakers Are";
    string s2 = "number";
    string s3 = "class or recitation now";
    string s4 = "one";
    string s5 = "fixed size array error in my CS 11 lab 5 is fixed";
    string s6 = "this year";
    string s7 = "CS171";
    string s8 = "Teach more OpenGL in";
    string s9 = "it was a throw error";

    /* Fill up the heap with random strings. */
    stringtest.add_value(s0);
    stringtest.add_value(s1);
    stringtest.add_value(s2);
    stringtest.add_value(s3);
    stringtest.add_value(s4);
    stringtest.add_value(s5);
    stringtest.add_value(s6);
    stringtest.add_value(s7);
    stringtest.add_value(s8);
    stringtest.add_value(s9);

    laststr = stringtest.get_first_value();
    cout << "Value 0= " << laststr << endl;

    for (i = 1; i < 10; i++)
    {
        string str = stringtest.get_first_value();

        // Using cout because printf is not typesafe for strings
        // If in order, it will reveal the 3 "hidden" messages
        cout << "Value " << i << "= " << str << endl;

        // if out of order
        if (str < laststr)
        {
            // Using cout because printf is not typesafe for strings
            cout << "  ERROR:  OUT OF ORDER.\n" << endl;
            return false;
        }
        laststr = str;
    }
    return true;
}

/* This function tests to make sure the underflow exception is working */
bool testUnderflow()
{
    Heap <float, 100> underflow;
    try
    {
        // Do something invalid, that should throw an overflow exception.
        underflow.get_first_value();
        // If we get here then the operation didn't throw an exception!
        // Report a failure - nothing was thrown.
        printf("Oh no! Underflow exception was not thrown! \n");
        return false;
    }
    catch (underflow_error &e)
    {
        // Report success.
        printf("Underflow exception was successfully thrown! \n");
        return true;
    }
    catch (...)
    {
        // If the function throws something other than what we expected,
        // this catch-block will run.

        // Report a failure - the wrong thing was thrown.
        printf("Uh oh - the wrong exception was thrown! \n");
        return false;
    }
}

/* This function tests to make sure the overflow exception is working */
bool testOverflow()
{
    Heap <float, 100> overflow;
    int i;

    /* Use a seed so that the sequence of random values
    * is always the same.
    */
    srand(12);

    /* Fill up the heap with random values. */
    for (i = 0; i < 100; i++)
        overflow.add_value(rand() % 1000);

    try 
    {
        // Do something invalid, that should throw an overflow exception.
        overflow.add_value(2800);
        // If we get here then the operation didn't throw an exception!
        // Report a failure - nothing was thrown.
        printf("Oh no! Overflow error exception was not thrown!\n");
        return false;
    }
    catch (overflow_error &e) 
    {
        // Report success.
        printf("Overflow error exception was succesfully thrown! \n");
        return true;
    }
    catch (...) 
    {
        // If the function throws something other than what we expected,
        // this catch-block will run.

        // Report a failure - the wrong thing was thrown.
        printf("Uh oh - the wrong exception was thrown! \n");
        return false;
    }
}

/* Test the heap. */
int main(int argc, char **argv)
{
    Heap <float, 100> hp;
    int i;
    float lastval;

    /* Use a seed so that the sequence of random values
    * is always the same.
    */
    srand(11);

    /* Fill up the heap with random values. */
    for (i = 0; i < 100; i++)
        hp.add_value(rand() % 1000);

    /*
    * Print out the results.  If anything is out of order,
    * flag it.  (Pull the very first value separately so that
    * we don't have to set lastval to something strange just
    * to get the test to work...)
    */
    lastval = hp.get_first_value();
    printf("Value 0 = %f\n", lastval);

    for (i = 1; i < 100; i++)
    {
        float val = hp.get_first_value();

        printf("Value %d = %f\n", i, val);
        if (val < lastval)
        printf("  ERROR:  OUT OF ORDER.\n");

        lastval = val;
    }

    // Testing the overflow exception
    if (testOverflow() == true)
    {
        printf("Overflow test works\n");
    }
    else
    {
        printf("Overflow test failed\n");
    }

    // Testing the underflow exception
    if (testUnderflow() == true)
    {
        printf("Underflow test works\n");
    }
    else
    {
        printf("Underflow test failed\n");
    }

    // Testing the use of strings in template
    if (testString() == true)
    {
        printf("String test works \n");
    }
    else
    {
        printf("String test failed \n");
    }
    return 0;
}

