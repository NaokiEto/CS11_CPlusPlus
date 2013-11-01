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
        node(int idx, int val, node *nxt = 0) :
        index(idx), value(val), next(nxt) { }
    };
    int size;

    // node-pointer to the first nonzero element in the list
    node *firstnon0;
    void clear();
    void copyList(const SparseVector &sv);
    void setNonzeroElem(int idx, int val);
    void removeElem(int idx);
    void checkListOrder() const;

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

    // Mutators
    void setElem(int idx, int val);

    // Overloading the assignment operator
    SparseVector& operator=(const SparseVector &sv);
};
