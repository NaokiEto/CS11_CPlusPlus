#include "SparseVector.hh"
#include <cassert>

SparseVector::SparseVector(int s)
{
    // make sure that the size of the vector is positive
    assert(s > 0);
    
    size = s;
    firstnon0 = new node(0, 1);
    node *curr = firstnon0;
    for (int i = 0; i < s; i++)
    {
        curr->next = new node(i, 1);
        curr = curr->next;
    }
}

// Helper function to delete sparse vector
void SparseVector::clear()
{
    node *curr = firstnon0;
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
    // Get a pointer to other list's first node
    node *otherCurr = sv.firstnon0;
    // Use prev and curr to create the copy
    node *prev = 0;
    while (otherCurr != 0) 
    {
        // Copy other list's current node
        node *curr = new node(otherCurr->index, otherCurr->value);
        if (prev == 0)
            firstnon0 = curr;
        // curr is the first node in our copy!
        else
            prev->next = curr; // Make previous node point to current
        prev = curr;
        otherCurr = otherCurr->next;
    }
}

// helper method to set a nonzero value for a node with specified index
void SparseVector::setNonzeroElem(int idx, int val)
{
    assert(val != 0);
    node *curr = firstnon0;
    node *prev;

    // go through the sparse vector
    while (curr != 0 and curr->index < idx)
    {
        prev = curr;
        curr = curr->next;
    }

    // if we find the index
    if (curr->index == idx)
    {
        curr->value = val;
    }
    // if we can't find the index and are at the beginning of the list
    else if (firstnon0->index > idx)
    {
        node *newnode = new node(idx, 1, firstnon0);
        firstnon0 = newnode;
    }
    // if we can't find the index and are at the end of the list
    else if (curr == 0)
    {
        node *newnode = new node(idx, 1);
        prev->next = newnode;
    }
    // if we can't find the index and are in the middle of the list
    else if (curr->index > idx)
    {
        node *newnode = new node(idx, 1, curr);
        prev->next = newnode;
    }
}

// helper method to delete a node from the list
void SparseVector::removeElem(int idx)
{
    node *curr = firstnon0;
    node *prev;

    // go through the sparse vector
    while (curr != 0 and curr->index < idx)
    {
        prev = curr;
        curr = curr->next;
    }
    // if we find the index
    if (curr->index == idx)
    {
        prev->next = curr->next;
        delete curr;
    }
    // if we don't find the index, nothing needs to be done!
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
    node *curr = firstnon0;
    while (curr->next != 0)
    {
        int i = 0;
        while(curr->index < idx)
        {
            // if we find the desired index, return the value
            if (curr->index == idx)
            {
                return curr->value;
            }
            i += 1;
        }
    }
    // if the desired index is bigger than the max index, return 0
    // if the desired index is not in list, return 0 too;
    return 0;
}

void SparseVector::setElem(int idx, int val)
{
    if (val != 0)
    {
        setNonzeroElem(idx, val);
    }
    else
    {
        removeElem(idx);
    }
}

// Overloading assignment operator
SparseVector& SparseVector::operator= (const SparseVector &sv)
{
    if (this != &sv)
    {
        // Delete the sparse vector
        this->clear();
        
        // Make a copy
        this->copyList(sv);
    }
    return *this;
}


