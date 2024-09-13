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
    std::vector<int>::iterator vecIterator;
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
}