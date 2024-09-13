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
    time_t timer, longTimer;
    int accessPoint;

    srand(time(0));

    for(int i = 0; i < 2000; i++)
    {
        rng.push_back(rand());
    }

    // VECTOR START:
    std::cout << "vector tests\n\nCreating\n";

    for(int i = 0; i < 20000000; i++)
    {
        vec.push_back(-i);

        if(i % 1000000 == 0)
        {
            std::cout << i / 1000000 << "/20" << std::endl;
        }
    }

    // Iteration start
    timer = clock();
    longTimer = timer;

    for(int k = 0; k < 20; k++)
    {
        vecIterator = vec.begin();

        for(int i = 0; i < vec.size(); i++)
        {
            (*vecIterator) ++;

            vecIterator ++;
        }
    }

    std::cout << "Iteration time: " << clock() - timer << std::endl;

    // Arbitrary index insertion start
    timer = clock();    

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(vec.size() * (float) rng[i] / RAND_MAX);

        vec.insert(vec.begin() + accessPoint, i);
    }

    std::cout << "Insertion time: " << clock() - timer << std::endl;

    // Arbitrary index erasure start
    timer = clock();    

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(vec.size() * (float) rng[i+1000] / RAND_MAX);

        if(accessPoint == vec.size()) accessPoint --;

        vec.erase(vec.begin() + accessPoint);
    }

    std::cout << "Erasure time: " << clock() - timer << std::endl;

    std::cout << "Total time: " << clock() - longTimer << std::endl;

    timer = clock();
    vec.clear();
    std::cout << "Clear time: " << clock() - timer << std::endl;

    // LIST START:
    std::cout << "\n\nlist tests\n\nCreating\n";

    for(int i = 0; i < 20000000; i++)
    {
        myList.push_back(-i);

        if(i % 1000000 == 0)
        {
            std::cout << i / 1000000 << "/20" << std::endl;
        }
    }

    // Iteration start
    timer = clock();
    longTimer = timer;

    for(int k = 0; k < 20; k++)
    {
        listIterator = myList.begin();

        for(int i = 0; i < myList.size(); i++)
        {
            (*listIterator) ++;

            listIterator ++;
        }
    }

    std::cout << "Iteration time: " << clock() - timer << std::endl;

    // Arbitrary index insertion start
    timer = clock();

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

    std::cout << "Insertion time: " << clock() - timer << std::endl;

    // Arbitrary index erasure start
    timer = clock();    

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

    std::cout << "Erasure time: " << clock() - timer << std::endl;
    std::cout << "Total time: " << clock() - longTimer << std::endl;

    timer = clock();
    myList.clear();
    std::cout << "Clear time: " << clock() - timer << std::endl;

    // PRAL START:
    std::cout << "\n\npral tests\n\nCreating\n";

    for(int i = 0; i < 20000000; i++)
    {
        myPral.pushBack(-i);

        if(i % 1000000 == 0)
        {
            std::cout << i / 1000000 << "/20" << std::endl;
        }
    }

    // Iteration start
    timer = clock();
    longTimer = timer;

    for(int k = 0; k < 20; k++)
    {
        pralIterator = myPral.getIndexedIterator(0);

        for(int i = 0; i < myPral.size(); i++)
        {
            pralIterator.setValue(pralIterator.getValue() + 1);

            pralIterator.forward();
        }
    }

    std::cout << "Iteration time: " << clock() - timer << std::endl;

    // Arbitrary index insertion start
    timer = clock();

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myPral.size() * (float) rng[i] / RAND_MAX);

        myPral.insert(accessPoint, i);
    }

    std::cout << "Insertion time: " << clock() - timer << std::endl;

    // Arbitrary index erasure start
    timer = clock();

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myPral.size() * (float) rng[i+1000] / RAND_MAX);

        if(accessPoint == myPral.size()) accessPoint --;

        myPral.erase(accessPoint);
    }

    std::cout << "Erasure time: " << clock() - timer << std::endl;

    std::cout << "Total time: " << clock() - longTimer << std::endl;

    timer = clock();
    myPral.clear();
    std::cout << "Clear time: " << clock() - timer << std::endl;

    // TREE START:
    std::cout << "\n\nbalanced binary tree tests\n\nCreating\n";

    for(int i = 0; i < 20000000; i++)
    {
        myTree.insert(myTree.size(), -i);

        if(i % 1000000 == 0)
        {
            std::cout << i / 1000000 << "/20" << std::endl;
        }
    }

    // Iteration start
    timer = clock();
    longTimer = timer;

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

    std::cout << "Iteration time: " << clock() - timer << std::endl;

    // Arbitrary index insertion start
    timer = clock();

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myTree.size() * (float) rng[i] / RAND_MAX);

        myTree.insert(accessPoint, i);
    }

    std::cout << "Insertion time: " << clock() - timer << std::endl;

    // Arbitrary index erasure start
    timer = clock();

    for(int i = 0; i < 1000; i += 1)
    {
        accessPoint = lround(myTree.size() * (float) rng[i+1000] / RAND_MAX);

        if(accessPoint == myTree.size()) accessPoint --;

        myTree.erase(accessPoint);
    }

    std::cout << "Erasure time: " << clock() - timer << std::endl;

    std::cout << "Total time: " << clock() - longTimer << std::endl;
}