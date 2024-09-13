#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include <time.h>
#include "pral.hpp"
#include "SBBTree.hpp"

int main()
{
    std::vector<int> rng;
    std::vector<int> vec;
    Pral<int> myPral;
    SBBTree<int> myTree;
    std::list<int> myList;
    std::list<int>::iterator listIterator;
    std::vector<int>::iterator vecIterator;
    PralIndexedIterator<int> pralIterator;
    SBBTreeNode<int> * treeItr;
    int accessPoint;

    srand(time(0));

    for(int i = 0; i < 2000; i++)
    {
        rng.push_back(rand());
    }

    // VECTOR START:
    std::cout << "vector tests\n\nCreating\n";

    for(int i = 0; i < 200000; i++)
    {
        vec.push_back(-i);
    }

    // Iteration start

    for(int k = 0; k < 20; k++)
    {
        vecIterator = vec.begin();

        for(int i = 0; i < vec.size(); i++)
        {
            (*vecIterator) ++;

            vecIterator ++;
        }
    }

    // Arbitrary index insertion start  

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(vec.size() * (float) rng[i] / RAND_MAX);

        vec.insert(vec.begin() + accessPoint, i);
    }


    // Arbitrary index erasure start

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(vec.size() * (float) rng[i+1000] / RAND_MAX);

        if(accessPoint == vec.size()) accessPoint --;

        vec.erase(vec.begin() + accessPoint);
    }

    // LIST START:
    std::cout << "\n\nlist tests\n\nCreating\n";

    for(int i = 0; i < 200000; i++)
    {
        myList.push_back(-i);
    }

    // Iteration start

    for(int k = 0; k < 20; k++)
    {
        listIterator = myList.begin();

        for(int i = 0; i < myList.size(); i++)
        {
            (*listIterator) ++;

            listIterator ++;
        }
    }

    // Arbitrary index insertion start

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myList.size() * (float) rng[i] / RAND_MAX);

        if(accessPoint < myList.size() / 2)
        {
            myList.insert(next(myList.begin(), accessPoint), i);
        }
        else
        {
            myList.insert(prev(myList.end(), myList.size() - accessPoint), i);
        }
    }

    // Arbitrary index erasure start  

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myList.size() * (float) rng[i+1000] / RAND_MAX);

        if(accessPoint == myList.size()) accessPoint --;

        if(accessPoint < myList.size() / 2)
        {
            myList.erase(next(myList.begin(), accessPoint));
        }
        else
        {
            myList.erase(prev(myList.end(), myList.size() - accessPoint));
        }
    }

    // PRAL START:
    std::cout << "\n\npral tests\n\nCreating\n";

    for(int i = 0; i < 200000; i++)
    {
        myPral.pushBack(-i);
    }

    // Iteration start

    for(int k = 0; k < 20; k++)
    {
        pralIterator = myPral.getIndexedIterator(0);

        for(int i = 0; i < myPral.size(); i++)
        {
            pralIterator.setValue(pralIterator.getValue() + 1);

            pralIterator.forward();
        }
    }

    // Arbitrary index insertion start

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myPral.size() * (float) rng[i] / RAND_MAX);

        myPral.insert(accessPoint, i);
    }

    // Arbitrary index erasure start

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myPral.size() * (float) rng[i+1000] / RAND_MAX);

        if(accessPoint == myPral.size()) accessPoint --;

        myPral.erase(accessPoint);
    }

    // TREE START:
    std::cout << "\n\nbalanced binary tree tests\n\nCreating\n";

    for(int i = 0; i < 200000; i++)
    {
        myTree.insert(myTree.size(), -i);
    }

    // Iteration start

    for(int k = 0; k < 20; k++)
    {
        treeItr = myTree.root->accessAtIndex(0);

        for(int i = 0; i < myTree.size() - 1; i++)
        {
            treeItr->value ++;

            treeItr = treeItr->next();
        }

        treeItr->value ++;
    }

    // Arbitrary index insertion start

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myTree.size() * (float) rng[i] / RAND_MAX);

        myTree.insert(accessPoint, i);
    }

    // Arbitrary index erasure start

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myTree.size() * (float) rng[i+1000] / RAND_MAX);

        if(accessPoint == myTree.size()) accessPoint --;

        myTree.erase(accessPoint);
    }

    std::cout << "\nChecking for differences between the pral, tree, vector, and list:\n";
    
    pralIterator = myPral.getIndexedIterator(0);
    listIterator = myList.begin();
    treeItr = myTree.root->accessAtIndex(0);
    vecIterator = vec.begin();
    
    for(int k = 0; k < vec.size(); k++)
    {
        if(*vecIterator != pralIterator.getValue() || *vecIterator != *listIterator || *vecIterator != treeItr->value)
        {
            std::cout << "Mismatch\n";
        }

        pralIterator.forward();
        listIterator ++;
        vecIterator ++;
        if(k+1 < vec.size()) treeItr = treeItr->next();
    }
}