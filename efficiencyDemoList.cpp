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
    std::list<int> myList;
    std::list<int>::iterator listIterator;
    time_t timer, longTimer;
    int accessPoint;

    srand(time(0));

    for(int i = 0; i < 2000; i++)
    {
        rng.push_back(rand());
    }

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
}