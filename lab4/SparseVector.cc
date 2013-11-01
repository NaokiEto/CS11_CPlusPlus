#include "SparseVector.hh"
#include <cassert>
#include <stdio.h>

SparseVector::SparseVector(int s)
{
    // make sure that the size of the vector is positive
    assert(s > 0);

    size = s;
    firstnon0 = 0;
    //checkListOrder();
}

// Helper function to delete sparse vector
void SparseVector::clear()
{
    node *curr = firstnon0;
    // keep deleting the nodes until the first node pointer is 0
    while (curr != 0) 
    {
        // Get what is next, before deleting curr.
        node *nxt = curr->next;
        // debug
        printf("the index and value are: %d, %d \n", curr->index, curr->value);
        // Delete this node.
        delete curr;
        // Go to next node in list
        curr = nxt;
    }
    firstnon0 = 0;
    size = 0;
}

// Helper function to copy sparse vector
void SparseVector::copyList(const SparseVector &sv)
{
    size = sv.getSize();
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
    if (sv.firstnon0 == 0)
    {
        firstnon0 = 0;
    }
    //checkListOrder();
}

// helper method to set a nonzero value for a node with specified index
void SparseVector::setNonzeroElem(int idx, int val)
{
    assert(val != 0);
    node *curr = firstnon0;
    node *prev = 0;

    //checkListOrder();

    if (firstnon0 != 0)
    {
        // go through the sparse vector
        while (curr->index < idx && curr->next != 0)
        {
            prev = curr;
            curr = curr->next;
        }

        //checkListOrder();
        // if we find the index
        if (curr->index == idx)
        {
            curr->value = val;
        }
        // if we can't find the index and are at the beginning of the list
        else if (firstnon0->index > idx)
        {
            node *newnode = new node(idx, val, firstnon0);
            firstnon0 = newnode;
        }
        // if we can't find the index and are at the end of the list
        else if (curr->next == 0)
        {
            node *newnode = new node(idx, val);
            curr->next = newnode;
        }
        // if we can't find the index and are in the middle of the list
        else if (curr->index > idx)
        {
            node *newnode = new node(idx, val);
            prev->next = newnode;
            newnode->next = curr;
        }
    }
    else
    {
        firstnon0 = new node(idx, val);
    }
    //checkListOrder();
}

// helper method to delete a node from the list
void SparseVector::removeElem(int idx)
{
    node *curr = firstnon0;
    node *prev;

    // go through the sparse vector
    while (curr != 0 && curr->index < idx)
    {
        prev = curr;
        curr = curr->next;
    }

    // if we find the index and are at the middle of the list
    if (curr != 0 && curr->index == idx)
    {
        prev->next = curr->next;
        delete curr;
    }
    // if we don't find the index, nothing needs to be done!

    //checkListOrder();
}

// Copy-constructor
SparseVector::SparseVector(const SparseVector &sv)
{
    this->copyList(sv);
    //checkListOrder();
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
    //checkListOrder();
    if (curr != 0)
    {
        while(curr->index < idx && curr->next != 0)
        {
            curr = curr->next;
        }

        // if we find the desired index, return the value
        if (curr->index == idx)
        {
            //checkListOrder();
            return curr->value;
        }
    }
    //checkListOrder();
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

void SparseVector::checkListOrder() const
{
    node *test = firstnon0;
    int idx = -1;
    while (test != 0)
    {
        //printf("apparently so \n");

        if (idx < test->index)
        {
            idx = test->index;
        }
        else
        {
            printf("Error in index progression from index %d to index %d \n", idx, test->index);
        }
        test = test->next;
    }
}


