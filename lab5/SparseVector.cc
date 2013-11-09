#include "SparseVector.hh"
#include <cassert>
#include <stdio.h>
#include <algorithm>    // std::min

SparseVector::SparseVector(int s)
{
    // make sure that the size of the vector is positive
    assert(s > 0);

    size = s;
    firstnon0 = 0;
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
        // curr is checkthe first node in our copy!
        else
            prev->next = curr; // Make previous node point to current
        prev = curr;
        otherCurr = otherCurr->next;
    }
    if (sv.firstnon0 == 0)
    {
        firstnon0 = 0;
    }
}

// helper method to set a nonzero value for a node with specified index
void SparseVector::setNonzeroElem(int idx, int val)
{
    assert(val != 0);
    node *curr = firstnon0;
    node *prev = 0;

    if (firstnon0 != 0)
    {
        // go through the sparse vector
        while (curr->index < idx && curr->next != 0)
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
            node *newnode = new node(idx, val, firstnon0);
            firstnon0 = newnode;
        }
        // if we can't find the index and are at the end of the list
        else if (curr->index < idx && curr->next == 0)
        {
            node *newnode = new node(idx, val);
            curr->next = newnode;
        }
        // if we can't find the index and are in the middle of the list
        else if (curr->index > idx)
        {
            node *newnode = new node(idx, val, curr);
            prev->next = newnode;
        }
    }
    else
    {
        firstnon0 = new node(idx, val);
    }
}

// helper method to delete a node from the list
void SparseVector::removeElem(int idx)
{
    node *curr = firstnon0;
    node *prev = 0;

    // go through the sparse vector
    while (curr->next != 0 && curr->index < idx)
    {
        prev = curr;
        curr = curr->next;
    }
    // if we find the index are at the beginning of the list
    if (curr->index == idx && prev == 0)
    {
        firstnon0 = curr->next;
        delete curr;
    }

    // if we find the index at the end of the list
    else if (curr->index == idx && curr->next == 0)
    {
        prev->next = 0;
        delete curr;
    }
    // if we find the index and are at the middle of the list
    else if (curr != 0 && curr->index == idx)
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
    if (curr != 0)
    {
        while(curr->index < idx && curr->next != 0)
        {
            curr = curr->next;
        }

        // if we find the desired index, return the value
        if (curr->index == idx)
        {
            return curr->value;
        }
    }
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
        if (idx < test->index)
        {
            idx = test->index;
        }
        test = test->next;
    }
}

// Overloading the Sparse Vector == operator (see if two sparse vectors are equal to each other)
bool SparseVector::operator==(const SparseVector &sv) const
{
    // if the two sparse vectors are of different size, they are not equal
    if (this->size != sv.size)
    {
        return false;
    }

    node *curr = this->firstnon0;
    node *othercurr = sv.firstnon0;
    // go through the sparse vectors and compare the values and index
    while (curr != 0)
    {
        // if the index are not the same
        if (curr->index != othercurr->index)
        {
            return false;
        }
        // if the values aren't the same
        else if (curr->value != othercurr->value)
        {
            return false;
        }

        // if one sparse vector ends before the other
        else if ((curr->next == 0 && othercurr->next != 0) || (curr->next != 0 && othercurr->next == 0))
        {
            return false;
        }
        curr = curr->next;
        othercurr = othercurr->next;
    }

    return true;
}

// Overloading the != operator
bool SparseVector::operator!=(const SparseVector &sv) const
{
    return !(*this == sv);
}

// Helper function for adding and subtracting the sparse vectors
// The bool add parameter is for determining either adding or subtracting
void SparseVector::addSubVector(const SparseVector &sv, bool add)
{
    assert(this->size == sv.size);
    node *curr = firstnon0;
    node *prev = 0;
    node *otherCurr = sv.firstnon0;
    int idx;

    // conditional operator
    int sign = (add ? 1 : -1);

    while (otherCurr != 0)
    {
        if (curr != 0)
        {
            idx = std::min(curr->index, otherCurr->index);
        }
        // if we are at the end of our sparse vector, set the index to the other index
        else
        {
            idx = otherCurr->index;
        }

        // if the minimum index is our index, instead of the other index,
        // we are essentially adding just 0
        if (idx != otherCurr->index)
        {
            prev = curr;
            curr = curr->next;
        }
        
        // if the minimum is the other index, we will have to insert it into
        // our sparse vector - this applies if we are at the end of our sparse vector
        else if (curr == 0 || idx != curr->index)
        {
            // create a new node
            node *result = new node(otherCurr->index, sign * otherCurr->value);

            // if we are at the beginning of our sparse vector
            if (prev == 0)
            {
                prev = result;
                firstnon0 = prev;
                prev->next = curr;
            }
            // if we are at the end of our sparse vector
            else if (curr == 0)
            {
                // make the last non zero element point to the new node
                prev->next = result;

                // make it the current node
                curr = result;

                // show that this is now the last nonzero node in the list
                curr->next = 0;
                prev = curr;
                curr = curr->next;
            }
            else
            {
                // set the prev next to point to result
                prev->next = result;

                // connect result to curr
                result->next = curr;
            }

            // move to the next node for the other sparse vector 
            otherCurr = otherCurr->next;
            
        }
        // if the minimum is both indices, then we add the values
        else if ((idx == curr->index) && (idx == otherCurr->index))
        {
            curr->value = curr->value + sign * otherCurr->value;
            prev = curr;
            curr = curr->next;
            otherCurr = otherCurr->next;
        }
    }
}

// helper function to clean out any elements whose values are 0's
void SparseVector::removeZeros()
{
    node* curr = firstnon0;
    node* prev = 0;
    while (curr != 0)
    {
        // if the value of current element is 0, set the previous' next to the
        // next element, delete the current element, and set the curr pointer
        // to the next element.
        if (curr->value == 0)
        {
            if (prev != 0)
            {
                prev->next = curr->next;
            }
            else
            {
                firstnon0 = curr->next;
            }
            delete curr;
            curr = curr->next;
        }
        // if value is nonzero, keep moving through the sparse vector
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

// Overloading the += operator
SparseVector& SparseVector::operator+= (const SparseVector &sv)
{
    this->addSubVector(sv, true);
    this->removeZeros();
    return *this;
}

// Overloading the -= operator
SparseVector& SparseVector::operator-= (const SparseVector &sv)
{
    this->addSubVector(sv, false);
    this->removeZeros();
    return *this;
}

// Overloading the + operator
const SparseVector SparseVector::operator+ (const SparseVector &sv) const
{
    SparseVector result = *this;
    result += sv;
    result.removeZeros();
    return result;
}

// Overloading the - operator
const SparseVector SparseVector::operator- (const SparseVector &sv) const
{
    SparseVector result = *this;
    result -= sv;
    result.removeZeros();
    return result;
}
