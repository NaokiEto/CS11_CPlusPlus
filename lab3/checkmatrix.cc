//
// FILE: checkmatrix.cc
//
//       Test script for the Matrix class.
//
//       If this program produces any other warning or error messages when
//       compiled, it means you need to fix a problem in your matrix class.
//

using namespace std;

#include "Matrix.hh"

#include <stdlib.h>
#include <sstream>
#include <set>
#include <iostream>

// Reliably reproducible pseudorandom numbers:
void srnd(long s) {
  srand(s);
}
int rnd() {
  return int(rand());
}
int rnd(int mac) {
  return int(((double) rand() / (double) RAND_MAX) * mac);
}

// ----------------------------------------------------------------------

// Normally, this declaration would go in a separate header file.

class ErrorContext              // displays test results
{
public:
    ErrorContext(ostream &os);              // write header to stream
    void desc(const char *msg, int line);   // write line/description
    void desc(string msg, int line);
    void result(bool good);                 // write test result
    ~ErrorContext();                        // write summary info
    bool ok() const;                        // true iff all tests passed
    
private:
    ostream &os;                            // output stream to use
    int passed;                             // # of tests which passed
    int total;                              // total # of tests
    int lastline;                           // line # of most recent test
    set<int> badlines;                      // line #'s of failed tests
    bool skip;                              // skip a line before title?
};


// ----------------------------------------------------------------------

// Normally, these method implementations would go in a separate source file.

ErrorContext::ErrorContext(ostream &os)
  : os(os), passed(0), total(0), lastline(0), skip(false)
{
    os << "line: ";
    os.width(65);
    os.setf(ios::left, ios::adjustfield);
    os << "description" << " result" << endl;
    os.width(78);
    os.fill('~');
    os << "~" << endl;
    os.fill(' ');
    os.setf(ios::right, ios::adjustfield);
}


void ErrorContext::desc(const char *msg, int line)
{
    if (lastline != 0 || (*msg == '-' && skip))
    {
        os << endl;
    }
    
    os.width(4);
    os << line << ": ";
    os.width(65);
    os.setf(ios::left, ios::adjustfield);
    os << msg << " ";
    os.setf(ios::right, ios::adjustfield);
    os.flush();
    
    lastline = line;
    skip = true;
}


void ErrorContext::desc(string msg, int line)
{
    if ((lastline != 0) || ((msg[0] == '-') && skip))
    {
        os << endl;
    }
    
    os.width(4);
    os << line << ": ";
    os.width(65);
    os.setf(ios::left, ios::adjustfield);
    os << msg << " ";
    os.setf(ios::right, ios::adjustfield);
    os.flush();
    
    lastline = line;
    skip = true;
}


#define DESC(x) desc(x, __LINE__)  // ugly hack

void ErrorContext::result(bool good)
{
    if (good)
    {
        os << "ok";
        passed++;
    }
    else
    {
        os << "ERROR";
        badlines.insert(lastline);
    }
    
    os << endl;
    total++;
    lastline = 0;
}


ErrorContext::~ErrorContext()
{
    os << endl << "Passed " << passed << "/" << total << " tests." << endl
       << endl;
    
    if (badlines.size() > 0)
    {
        os << "For more information, please consult:" << endl;
        for (set<int>::const_iterator it = badlines.begin();
            it != badlines.end(); it++)
        {
            os << "  " << __FILE__ << ", line " << *it << endl;
        }
        os << endl;
        
        if (badlines.size() > 2)
        {
            os << "We recommend that you "
               << "fix the topmost failure before going on."
               << endl << endl;
        }
    }
}


bool ErrorContext::ok() const
{
    return passed == total;
}


// ----------------------------------------------------------------------

void empty(ErrorContext &ec)
{
    ec.DESC("--- Empty matrices (0 by 0) ---");
    
    // If this test fails, it means that getrows returned a non-zero value
    // when called on an "empty" (0x0) matrix created with the default
    // constructor.
    ec.DESC("default constructor and getrows");
    
    // Construct an empty matrix using the default constructor.
    const Matrix a;
    
    // Make sure 'getrows' method returns zero for this matrix.
    ec.result(a.getrows() == 0);
    
    
    // Same as above, for getcols instead of getrows.
    ec.DESC("default constructor and getcols");
    ec.result(a.getcols() == 0);
    
    
    // If this test fails, it means that getrows returned a non-zero value
    // when called on an "empty" (0x0) matrix created with the 2-argument
    // constructor.
    ec.DESC("two-argument constructor and getrows");
    
    // Construct an empty matrix using the two-argument constructor.
    const Matrix b(0, 0);
    
    // Make sure 'getrows' method returns zero for this matrix.
    ec.result(b.getrows() == 0);
    
    // Same as above, for getcols instead of getrows.
    ec.DESC("two-argument constructor and getcols");
    ec.result(b.getcols() == 0);
}


void basic(ErrorContext &ec, int level)
{
    const int rows = rnd(level * level) + 1;
    const int cols = rnd(level * level) + 1;
    
    {
        ostringstream oss;
        oss << "--- Basic operations (" << rows << " by " 
            << cols << " matrix) ---" << ends;
        ec.DESC(oss.str());
        
        // Make sure getrows and getcols work for non-empty matrices.
        ec.DESC("getrows and getcols");
        Matrix a(rows, cols);
        ec.result((a.getrows() == rows) && (a.getcols() == cols));
    }
    
    // Repeat 'level' times.
    for (int pass = 1; pass <= level; pass++)
    {
        // Choose a valid matrix position and value.
        const int r = rnd(rows);
        const int c = rnd(cols);
        const int v = rnd();
        
        // Let the user know what we're about to try.
        ostringstream oss;
        oss << "getelem and setelem (1), pass " << pass << ": element (" << r
            << "," << c << ")" << ends;
        ec.DESC(oss.str());
        
        // Create a new matrix of the appropriate size.
        Matrix a(rows, cols);
        
        // Set the value.
        a.setelem(r, c, v);
        
        // Verify the value.
        ec.result(a.getelem(r, c) == v);
    }
    
    
    // Repeat 'level' times.
    for (int pass = 1; pass <= level; pass++)
    {
        {
            // If this part (2a) of the test fails, but part (1) succeeded,
            // you might have forgotten to explicitly initialize the contents
            // of your matrix to all-zeroes in your two-argument constructor.
            // You can do this using a loop which sets each element to zero.
            
            ostringstream oss;
            oss << "getelem and setelem (2a), pass " << pass 
                << " [read]" << ends;
            ec.DESC(oss.str());
        }
        
        // Create a new matrix.
        Matrix a(rows, cols);
        
        // Ensure that the matrix initially contains only zeroes.
        bool good = true;

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                good &= (a.getelem(r, c) == 0);
            }
        }
        
        ec.result(good);
        
        {
            // A failure here may be due to a bug in getelem, setelem, or
            // your two-argument constructor.  Did you swap the order of the
            // row and column somewhere?  Did you allocate enough space?
            
            ostringstream oss;
            oss << "getelem and setelem (2b), pass " << pass 
                << " [write]" << ends;
            ec.DESC(oss.str());
        }
        
        // Fill the matrix with various exciting values.
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                a.setelem(r, c, (r - 666 * c) * pass);
            }
        }
        
        // Now read the values back out and see if they're all correct.
        good = true;

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                good &= (a.getelem(r, c) == ((r - 666 * c) * pass));
            }
        }
        
        ec.result(good);
    }
}


void copy(ErrorContext &ec)
{
    ec.DESC("--- Copying matrices ---");

    
    ec.DESC("copy constructor: target dimensions");
    
    // Create a largish matrix and fill in some values.
    Matrix a(123, 456);
    
    for (int r = 0; r < 123; r++)
    {
        for (int c = 0; c < 456; c++)
        {
            a.setelem(r, c, r * (c - 246));
        }
    }
    
    // Invoke copy constructor.
    const Matrix &ref = a;
    const Matrix b = ref;
    
    // See if the resulting matrix has the correct size.
    ec.result((b.getrows() == 123) && (b.getcols() == 456));
    
    
    ec.DESC("copy constructor: target values");
    
    // See if the values were copied correctly.
    bool good = true;
    
    for (int r = 0; r < 123; r++)
    {
        for (int c = 0; c < 123; c++)
        {
            good &= (b.getelem(r, c) == r * (c - 246));
        }
    }
    
    ec.result(good);
    
    
    ec.DESC("copy constructor: source dimensions and values");
    
    // Verify that the original matrix was not changed by the copy.
    good = (a.getrows() == 123) && (a.getcols() == 456);
    
    for (int r = 0; r < 123; r++)
    {
        for (int c = 0; c < 123; c++)
        {
            good &= (a.getelem(r, c) == r * (c - 246));
        }
    }
  
    ec.result(good);


    // This next test should always pass, unless a previous test failed or
    // you foolishly ignored a compiler warning about "const" somewhere.
    ec.DESC("copy constructor: depth of copy");
    
    // Systematically eradicate the original values.
    for (int r = 0; r < 123; r++)
    {
        for (int c = 0; c < 123; c++)
        {
            a.setelem(r, c, 23);
        }
    }
    
    // Verify that the original matrix is gone but the copy is still there.
    good = (a.getrows() == 123) && (a.getcols() == 456)
        && (b.getrows() == 123) && (b.getcols() == 456);
    
    for (int r = 0; r < 123; r++)
    {
        for (int c = 0; c < 123; c++)
        {
            good &= ((b.getelem(r, c) == r * (c - 246)) 
                     && (a.getelem(r, c) == 23));
        }
    }
    
    ec.result(good);
    
    
    // If the previous test fails, this next test may appear to succeed, even
    // if the assignment operator fails to work.
    ec.DESC("assignment operator: matrices of equal size");
    
    // Copy the values back using the assignment operator.
    a = b;
    
    // Make sure everything is the way it should be.
    good = (a.getrows() == 123) 
        && (a.getcols() == 456)
        && (b.getrows() == 123) 
        && (b.getcols() == 456);
    
    for (int r = 0; r < 123; r++)
    {
        for (int c = 0; c < 123; c++)
        {
            good &= ((a.getelem(r, c) == (r * (c - 246))) 
                     && (b.getelem(r, c) == (r * (c - 246))));
        }
    }
    
    ec.result(good);
    
    
    ec.DESC("assignment operator: matrices of differing size");
    
    // Replace b with a zeroed 23x5 matrix.
    a = Matrix(23, 5);
    
    // Verify the new size and contents of a.
    good = (a.getrows() == 23) && (a.getcols() == 5);
    
    for (int r = 0; r < 23; r++)
    {
        for (int c = 0; c <  5; c++)
        {
            good &= (a.getelem(r, c) == 0);
        }
    }
    
    ec.result(good);
    
    
    // NOTE: This test may fail to detect a common problem!  But we'll try:
    ec.DESC("assignment operator: self-assignment");
    
    // Start out by filling the new 23x5 matrix with some 
    // nice 1-heavy garbage.
    for (int r = 0; r < 23; r++)
    {
        for (int c = 0; c <  5; c++)
        {
            a.setelem(r, c, ~(r ^ (c << 16)));
        }
    }
    
    // Assign a to itself in various exciting different ways.
    a = ((a = a = a) = (a = a = a) = (a = a = a)) = a;
    
    // See how ineffective that really was.
    good = (a.getrows() == 23) && (a.getcols() == 5);
    
    for (int r = 0; r < 23; r++)
    {
        for (int c = 0; c <  5; c++)
        {
            good &= (a.getelem(r, c) == ~(r ^ (c << 16)));
        }
    }
    
    ec.result(good);
}


void comp(ErrorContext &ec, int level)
{
    ec.DESC("--- Comparison operators ---");


    for (int pass = 1; pass <= (level / 3) * (level / 3); pass++)
    {
        ec.DESC("two empty matrices, equality");
        ec.result(Matrix() == Matrix(0, 0));
        
        ec.DESC("two empty matrices, inequality");
        ec.result(!(Matrix(0, 0) != Matrix()));
        
        
        const int rows = level + rnd(level);
        const int cols = level + rnd(level * level);

        {
            ostringstream oss;
            oss << "identical " << rows << " by " << cols 
                << " matrices, equality" << ends;
            ec.DESC(oss.str());
        }
        
        // Create two identical random matrices.
        Matrix a(rows, cols), b(rows, cols);

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                int v = rnd();
                a.setelem(r, c, v);
                b.setelem(r, c, v);
            }
        }
        
        ec.result((a == b) && (b == a));
        
        {
            ostringstream oss;
            oss << "identical " << rows << " by " << cols 
                << " matrices, inequality" << ends;
            ec.DESC(oss.str());
        }
        
        ec.result(!((a != b) || (b != a)));
        
        
        int row = rnd(rows);
        int col = rnd(cols);

        {
            ostringstream oss;
            oss << "matrices differing only at (" << row << "," << col
                << "), equality" << ends;
            ec.DESC(oss.str());
        }
        
        // Add 1 to a random element in a.
        a.setelem(row, col, a.getelem(row, col) + 1);
        
        ec.result(!((a == b) || (b == a)));
        
        
        {
            ostringstream oss;
            oss << "matrices differing only at (" << row << "," << col
                << "), inequality" << ends;
            ec.DESC(oss.str());
        }
        
        ec.result((a != b) && (b != a));
        
        
        // Ensure that if one dimension is zero, both will be.
        if ((row == 0) || (col == 0))
        {
            row = col = 0;
        }
        
        {
            ostringstream oss;
            oss << rows << " by " << cols << " vs. " << row << " by " << col
                << ", equality" << ends;
            ec.DESC(oss.str());
        }
        
        // Make b into a "subset" of a.
        b = Matrix(row, col);

        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                b.setelem(r, c, a.getelem(r, c));
            }
        }
        
        ec.result(!((a == b) || (b == a)));
        
        
        {
            ostringstream oss;
            oss << rows << " by " << cols << " vs. " << row << " by " << col
                << ", inequality" << ends;
            ec.DESC(oss.str());
        }
        
        ec.result((a != b) && (b != a));
    }
}


void math(ErrorContext &ec, int level)
{
    ec.DESC("--- Arithmetic operators ---");

    // Note that these tests depend heavily on previously tested operations!
    // They should not be run unless everything else checks out OK.

    if (!ec.ok())
    {
        ec.DESC("one or more previous failures; skipping this section");
        ec.result(false);
        return;
    }
    
    for (int pass = 1; pass <= level / 2; pass++)
    {
        // Make up some dimensions for these matrices.
        const int x = (pass > 1) ? (rnd(level) + 1) : 0;
        const int y = (pass > 1) ? (rnd(level) + 1) : 0;
        const int z = (pass > 1) ? (rnd(level) + 1) : 0;
        
        // These will be three random matrices.
        Matrix a(x, y);
        Matrix b(x, y);
        Matrix c(y, z);
        
        // These will be the correct results of arithmetic operations.
        Matrix a_plus_b(x, y);
        Matrix a_minus_b(x, y);
        Matrix a_times_c(x, z);
        
        // Fill in the values and results.
        
        for (int ix = 0; ix < x; ix++)
        {
            for (int iy = 0; iy < y; iy++)
            {
                const int va = rnd();
                const int vb = rnd();
                
                a.setelem(ix, iy, va);
                b.setelem(ix, iy, vb);
                
                a_plus_b.setelem(ix, iy, va + vb);
                a_minus_b.setelem(ix, iy, va - vb);
            }
        }
        
        for (int iy = 0; iy < y; iy++)
        {
            for (int iz = 0; iz < z; iz++)
            {
                const int vc = rnd();
                c.setelem(iy, iz, vc);
                
                for (int ix = 0; ix < x; ix++)
                {
                    a_times_c.setelem(ix, iz, a_times_c.getelem(ix, iz) 
                                      + vc * a.getelem(ix, iy));
                }
            }
        }
        
        // Set up read-only copies of the three reference matrices.
        const Matrix copy_a = a;
        const Matrix copy_b = b;
        const Matrix copy_c = c;
        
        // Check non-destructive addition.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") + (" << x << " by " 
                << y << ")" << ", return value" << ends;
            ec.DESC(oss.str());
            ec.result(copy_a + copy_b == a_plus_b);
        }
        
        // Ensure arguments were not altered.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") + (" << x << " by " 
                << y << ")" << ", side effects" << ends;
            ec.DESC(oss.str());
            ec.result(copy_a == a && copy_b == b);
        }
        
        // Check non-destructive subtraction.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") - (" << x << " by " 
                << y << ")" << ", return value" << ends;
            ec.DESC(oss.str());
            ec.result(copy_a - copy_b == a_minus_b);
        }
        
        // Ensure arguments were not altered.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") - (" << x << " by " 
                << y << ")" << ", side effects" << ends;
            ec.DESC(oss.str());
            ec.result(copy_a == a && copy_b == b);
        }
        
        // Check non-destructive multiplication.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") * (" << y << " by " 
                << z << ")" << ", return value" << ends;
            ec.DESC(oss.str());
            ec.result(copy_a * copy_c == a_times_c);
        }
        
        // Ensure arguments were not altered.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") * (" << y << " by " 
                << z << ")" << ", side effects" << ends;
            ec.DESC(oss.str());
            ec.result(copy_a == a && copy_c == c);
        }
        
        // Check destructive addition.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") += (" << x << " by " 
                << y << ")" << ", return value" << ends;
            ec.DESC(oss.str());
            ec.result((a_minus_b += copy_b) == copy_a);
        }
        
        // Ensure LHS was altered and RHS was not.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") += (" << x << " by " 
                << y << ")" << ", side effects" << ends;
            ec.DESC(oss.str());
            ec.result(a_minus_b == copy_a && copy_b == b);
        }
        
        // Check destructive subtraction.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") -= (" << x << " by " 
                << y << ")" << ", return value" << ends;
            ec.DESC(oss.str());
            ec.result((a_plus_b -= b) == copy_a);
        }
        
        // Ensure LHS was altered and RHS was not.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") -= (" << x << " by " 
                << y << ")" << ", side effects" << ends;
            ec.DESC(oss.str());
            ec.result(a_plus_b == copy_a && copy_b == b);
        }
        
        // Check destructive multiplication.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") *= (" << y << " by " 
                << z << ")" << ", return value" << ends;
            ec.DESC(oss.str());
            ec.result((a *= copy_c) == a_times_c);
        }
        
        // Ensure LHS was altered and RHS was not.
        {
            ostringstream oss;
            oss << "(" << x << " by " << y << ") *= (" << y << " by " 
                << z << ")" << ", side effects" << ends;
            ec.DESC(oss.str());
            ec.result(a == a_times_c && copy_c == c);
        }
    }
}


// ----------------------------------------------------------------------

int main(int argc, const char *argv[])
{
    // Use first argument, if any, as level.
    int level = (argc > 1) ? atoi(argv[1]) : 0;
    
    if (level <= 0)
    {
        cout << "Test level may be specified as a positive integer argument."
             << endl
             << "Larger levels yield more tests; "
             << "smaller levels yield fewer tests."
             << endl << endl;
        
        level = 5;
    }
    
    // Set everything up.
    cout << "Performing a level " << level 
         << " check of class Matrix." << endl << endl;
    ErrorContext ec(cout);
    srnd(level);
    
    // Perform the appropriate checks for this level.
    
    empty(ec);
    
    if (level >= 2)
    {
        basic(ec, level);
    }
    
    if (level >= 3)
    {
        copy(ec);
    }
    
    if (level >= 4)
    {
        comp(ec, level);
    }
    
    if (level >= 5)
    {
        math(ec, level);
    }
    
    // Return 0 (success) if all the checks passed, 1 otherwise.
    return ec.ok() ? 0 : 1;
}
