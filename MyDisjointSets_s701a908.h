#ifndef _MY_DISJOINTSETS_H_
#define _MY_DISJOINTSETS_H_

#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "MyVector_s701a908.h"

class MyDisjointSets 
{
  public:
    // constructor
	explicit MyDisjointSets(const size_t size)
	{
        // code begins
        theSize = size;
        numSets = size;
        parents.resize(size);
        for (size_t i = 0; i < size; ++i) {
            parents[i] = -1; 
        }

        // code ends
	}

    // destructor
    ~MyDisjointSets(void)
    {
        // code begins

        // code ends
    }
	
    // finds the ID of the set that contains x
    // implements path compression
    int find(const int x)
    {
        // code begins
        if (parents[x] < 0) {
            return x;
        }
        parents[x] = find(parents[x]); 
        return parents[x];

        // code ends
    }

    // unions the two sets represented by r1 and r2, respectively
    // (r1 and r2 should be roots)
    // implements the union-by-size approach
	void unionSets(const int r1, const int r2)
	{
        // code begins
        if (r1 == r2) return; 

        int root1 = find(r1);
        int root2 = find(r2);

        if (root1 == root2) return; 

        if (parents[root1] > parents[root2]) {
            std::swap(root1, root2);
        }

        parents[root1] += parents[root2];
        parents[root2] = root1;           

        --numSets; 

        // code ends
	}

    // returns the size of the set that contains x
    size_t setSize(const int x)
    {
        // code begins
        int root = find(x);
        return static_cast<size_t>(-parents[root]);

        // code ends
    }

    // returns the total number of elements in the disjoint set
    size_t size()
    {
        // code begins
        return theSize;

        // code ends
    }

    // returns the number of disjoint sets
    size_t numDisjointSets()
    {
        // code begins
        return numSets;

        // code ends
    }

  private:
	size_t theSize;             // the number of elements in the disjoint sets
    size_t numSets;             // the number of disjoint sets maintained
    MyVector<int> parents;      // the info array; if the index is not the root, it contains the ID of its parent; otherwise it contains the size of the set as a negative number

};

#endif  // _MY_DISJOINTSETS_H_