#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include "SBBTree.hpp"

int main()
{
    std::vector<int> rng;
    SBBTree<int> myTree;
    SBBTreeNode<int> * treeItr;
    time_t timer, longTimer;
    int accessPoint;

    srand(time(0));

    for(int i = 0; i < 2000; i++)
    {
        rng.push_back(rand());
    }

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