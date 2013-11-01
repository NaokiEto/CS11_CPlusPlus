#include "SparseVector.hh"
SparseVector::SparseVector(int s)
{
    // make sure that the size of the vector is positive
    assert(s > 0);
    arr = new node[s];

    
    size = s;
    for (int i = 0; i < s; i++)
    {
        arr[i].index = i;
        arr[i].value = 0;
        if(i < s)
        {
            arr[i]->next = arr[i+1];
        }  
    }
}

// Helper function to delete sparse vector
void SparseVector::clear()
{
    node *curr = arr[0];
    // keep deleting the nodes until the first node pointer is 0
    while (curr != 0) 
    {
        // Get what is next, before deleting curr.
        node *next = curr->next;
        // Delete this node.
        delete curr;
        // Go to next node in list
        curr = next;
    }
}

// Helper function to copy sparse vector
void SparseVector::copyList(const SparseVector &sv)
{
    size = sv.size;
    arr = new node[s];
    for (int i = 0; i < s; i++)
    {
        arr[i].index = i;
        arr[i].value = sv.arr[i].value;
        if(i < s)
        {
            arr[i]->next = arr[i+1];
        }  
    }
}

void SparseVector::setNonzeroElem(int idx, int val)
{
    assert(val != 0);
    int i = 0;

    // go through the sparse vector
    while ((arr[i].index <= idx) && (arr[i].index != idx))
    {
        i += 1;
    }
    // if we find the index
    if (arr[i].index == idx)
    {
        arr[i].value = val;
    }
    // if we can't find the index
    if (arr[i].index > idx)
    {
        node a;
        arr[i - 1]->next = a;
        a.index = idx;
        a.value = val;
        a->next = arr[i];
    }
}

// Copy-constructor
SparseVector::SparseVector(const SparseVector &sv)
{
    this->copyList(sv);
}

// Destructor
SparseVector::~SparseVector()
{
    this->clear();
}


// Get the number of elements in SparseVector
int SparseVector::getSize() const
{
    return size;
}

// Get the value at the specified node
int SparseVector::getElem(int idx) const
{
    if (idx <= arr[size - 1].index)
    {
        int i = 0;
        while(arr[i].index < idx)
        {
            // if we find the desired index, return the value
            if (arr[i].index == idx)
            {
                return arr[i].value;
            }
            i += 1;
        }
    }
    // if the desired index is bigger than the max index, return 0
    // if the desired index is not in list, return 0 too;
    return 0;
}

// Overloading assignment operator
SparseVector::SparseVector& operator=(const SparseVector &sv)
{
    if (this != sv)
    {
        // Delete the sparse vector
        this->clear();
        
        // Make a copy
        this->copyList(sv);
    }
    return *this;
}


