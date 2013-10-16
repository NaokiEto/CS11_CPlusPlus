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

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int index = i * c + j;
            arr[index] = 0;
        }
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

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int index = i * col + j;
            arr[index] = mat.arr[index];
        }
    }
}

// Mutator
void Matrix::setelem(int ro, int co, int elem)
{
    int index = ro * col + co;
    arr[index] = elem;
}

// Accessors

int Matrix::getrows()
{
    return row;
}

int Matrix::getcols()
{
    return col;
}

int Matrix::getelem(int ro, int co)
{
    int index = ro * col + co;
    return arr[index];
}

void Matrix::add(Matrix &mat)
{
    assert(row == mat.row);
    assert(col == mat.col);

// make this one for loop
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int index = i*col + j;
            arr[index] += mat.arr[index];
        }
    }
}

void Matrix::subtract(Matrix &mat)
{
    assert(row == mat.row);
    assert(col == mat.col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int index = i*col + j;
            arr[index] -= mat.arr[index];
        }
    }
}

bool Matrix::equals(Matrix &mat)
{
    if ((row != mat.row) || (col != mat.col))
    {
        return false;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int index = i*col + j;
            if (arr[index] != mat.arr[index])
            {
                return false;
            }   
        }
    }
    return true;
}
