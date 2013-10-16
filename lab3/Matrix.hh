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
    Matrix(Matrix const &mat);

    // Destructor
    ~Matrix();

    // Mutator
    void setelem(int ro, int co, int elem);

    // Accessors
    int getrows();
    int getcols();
    int getelem(int ro, int co);

    void add(const Matrix& mat);
    void subtract(const Matrix& mat);
    bool equals(const Matrix& mat);
};
