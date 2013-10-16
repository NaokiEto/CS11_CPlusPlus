#include <iostream>
#include "Matrix.hh"

using namespace std;

// Have some fun playing with a Matrix!
int main() {

  // Create a new matrix with two rows and three columns
  Matrix a(2, 3);  

  // Print out some information about the size of this matrix:
  cout << "Matrix a is " << a.getrows() << " rows tall." << endl;
  cout << "Matrix a is " << a.getcols() << " columns wide." << endl;

  // Print out the contents of this matrix (should be all zeroes!):
  for(int r = 0; r < a.getrows(); r++) {
    for(int c = 0; c < a.getcols(); c++) {
      cout << "Element (" << r << ", " << c << ") = " << a.getelem(r,c) << endl;
    }
  }

  // Fill in a few values
  a.setelem(1, 2, -5280);  // bottom right element is now -5280
  a.setelem(0, 1, 123);    // top center element is now 123

  // Create an identical copy of this matrix
  Matrix b = a;

  // Change the original matrix some more
  a.setelem(1, 2, 555);  // bottom right element is now 555

  // Examine some elements of each matrix
  cout << "(1,2) of a = " << a.getelem(1,2) << " [should be 555]" << endl;
  cout << "(1,2) of b = " << b.getelem(1,2) << " [should be -5280]" << endl;

  // So if a and b are different, let's copy a into a new matrix and add b to it:
  Matrix c = a;
  c.add(b);

  // Now let's copy c into another new matrix, d, and subtract a from it:
  Matrix d = c;
  d.subtract(a);

  // Hmm...  that means d should be b, no?
  if (d.equals(b)) {
    cout << "Yay!  d = b!" << endl;
  } else {
    cout << "Uh-oh!  Something went wrong, d isn't b!" << endl;
  }

  // Let's create a tiny 0 by 0 matrix using the default constructor:
  Matrix e;
  cout << "0x0 matrix e is " << e.getrows() << " by " << e.getcols() << endl;

  // Of course, e and d are different, since they have different sizes!
  if(!e.equals(d)) {
    cout << "e and d are indeed different!" << endl;
  } else {
    cout << "Oh well, back to the drawing board...." << endl;
  }

  // Let's create two matrices with the same elements and sizes but 
  // different dimensions.
  int matelems [] = {0, 1, -2, 3, 4, -5, 6, 7, -8, 9, 10, -11};
  Matrix f(3, 4);
  Matrix g(2, 6);

  for (int i = 0; i < 12; ++i) {
    f.setelem(i / 4, i % 4, matelems[i]);
    g.setelem(i / 6, i % 6, matelems[i]);
  }
  if (f.equals(g) || g.equals(f)) {
    cout << "You missed a spot. Are you checking dimensions!" << endl;    
  } else {
    cout << "Don't mind me, just some more testing." << endl;
  }

  // Let's also compare a matrix with one of it's submatrices.
  Matrix h(2, 2);
  for (int y = 0; y < 2; ++y) {
    for (int x = 0; x < 2; ++x) {
      h.setelem(x, y, g.getelem(x, y));
    }
  }
  
  if (g.equals(h) || h.equals(g)) {
    cout << "Whoops. Try again." << endl;
  } else {
    cout << "Still doin' fine." << endl;
  }

  // OK, that stuff was silly. Now what happens if just the first element
  // is different?
  Matrix k = g;
  k.setelem(0, 0, g.getelem(0, 0) + 1);
  if (k.equals(g)) {
    cout << "You apparently have a loose definition of \"equals\"." << endl
         << "Why don't you try again?" << endl;
  } else {
    cout << "OK I'm done, I promise. Good job. " << endl;
  }

  // Okay, enough of this; destroy all those matrices and end the program:
  return 0;
}
