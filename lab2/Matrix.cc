#include "Matrix.hh"
#include <cassert>
#include <cstddef>

// Default Constructor: initializes matrix to 0 by 0.
Matrix::Matrix() 
{
    row = 0;
    col = 0;
    arr = new int[0];
}

// Initializes the matrix to be filled with 0's.
Matrix::Matrix(int r, int c) 
{
    assert(r >= 0);
    assert(c >= 0);

    row = r;
    col = c;

    arr = new int[r * c];

    for (int i = 0; i < r * c; i++)
    {
        arr[i] = 0;
    }
}

// Destructor
Matrix::~Matrix() 
{
    // Release the memory for the array
    if (arr != NULL)
    {
        delete[] arr;
    }
}

// Copy-constructor
Matrix::Matrix(Matrix &mat)
{
    row = mat.row;
    col = mat.col;

    arr = new int[row * col];

    for (int i = 0; i < row * col; i++)
    {
        arr[i] = mat.arr[i];
    }
}

// Mutator
void Matrix::setelem(int ro, int co, int elem)
{
    int index = ro * col + co;
    arr[index] = elem;
}

// Accessors
// get the number of rows
int Matrix::getrows()
{
    return row;
}

// get the number of columns
int Matrix::getcols()
{
    return col;
}

// get the element
int Matrix::getelem(int ro, int co)
{
    int index = ro * col + co;
    return arr[index];
}

// Matrix addition
void Matrix::add(Matrix &mat)
{
    assert(row == mat.row);
    assert(col == mat.col);

    for (int i = 0; i < row * col; i++)
    {
        arr[i] += mat.arr[i];
    }
}

// Matrix subtraction
void Matrix::subtract(Matrix &mat)
{
    assert(row == mat.row);
    assert(col == mat.col);

    for (int i = 0; i < row; i++)
    {
        arr[i] -= mat.arr[i];
    }
}

// Matrix equals (see if two matrices are equal to each other)
bool Matrix::equals(Matrix &mat)
{
    if ((row != mat.row) || (col != mat.col))
    {
        return false;
    }

    for (int i = 0; i < row * col; i++)
    {
        if (arr[i] != mat.arr[i])
        {
            return false;
        }
    }
    return true;
}
