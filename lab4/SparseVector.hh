class SparseVector
{
    private:
    // make the node struct private access only
    // this is so it is not visible to clients of the SparseVector class
    struct node
    {
        int index;
        int value;
        node *next;
    };
    int size;

    // node-pointer to the first nonzero element in the list
    node *firstnon0;
    node *arr;
    void clear();
    void copyList(const SparseVector &sv);
    void setNonzeroElem(int idx, int val);

    public:
    // Constructors
    
    // One-argument constructor
    SparseVector(int s);

    // Copy-constructor
    SparseVector(const SparseVector &sv);

    // Destructor
    ~SparseVector();

    // Accessor member function
    int getSize() const;
    int getElem(int idx) const;

    // Overloading the assignment operator
    SparseVector& operator=(const SparseVector &sv);
};
