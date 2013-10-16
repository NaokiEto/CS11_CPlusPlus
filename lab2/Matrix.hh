// A 2-D Matrix class
class Matrix 
{
    private:
    int row;
    int col;

    //static int* arr = new int[row * col];

    int* arr;

    public:
    //Constructors

    //Default Constructor
    Matrix();

    // Two-argument constructor
    Matrix(int r, int c);

    // Copy-constructor
    Matrix(Matrix &mat);

    // Destructor
    ~Matrix();

    // Mutator
    void setelem(int ro, int co, int elem);

    // Accessors
    int getrows();
    int getcols();
    int getelem(int ro, int co);

    void add(Matrix& mat);
    void subtract(Matrix& mat);
    bool equals(Matrix& mat);
};
