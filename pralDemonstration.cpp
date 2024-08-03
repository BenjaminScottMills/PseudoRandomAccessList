#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <math.h>
#include <time.h>
#include "pral.hpp"

int main()
{
    std::vector<int> rng;
    std::vector<int> vec;
    std::deque<int> deq;
    Pral<int> myPral;
    std::list<int> myList;
    std::list<int>::iterator listIterator;
    PralIndexedReference<int> ref;
    int counter = 0;
    time_t timer;
    int startPoint;

    srand(time(0));

    for(int i = 0; i < 10000; i++)
    {
        rng.push_back(rand());
    }

    std::cout << "Arbitrary index insertion test. 1000000 elements, 5000 insertions:\n\n";
    
    for(int i = 5; i < 1000000; i++)
    {
        myPral.pushBack(-i);
        vec.push_back(-i);
        deq.push_back(-i);
        myList.push_back(-i);
    }

    // Vector start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(vec.size() * (float) rng[i] / RAND_MAX);

        vec.insert(vec.begin() + startPoint, i);
    }

    std::cout << "vector time: " << clock() - timer << std::endl;

    // PRAL start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(myPral.size() * (float) rng[i] / RAND_MAX);

        myPral.insert(i, startPoint);
    }

    std::cout << "pral time: " << clock() - timer << std::endl;
    
    // Deque start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(deq.size() * (float) rng[i] / RAND_MAX);

        deq.insert(deq.begin() + startPoint, i);
    }

    std::cout << "deque time: " << clock() - timer << std::endl;
    
    // List start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(myList.size() * (float) rng[i] / RAND_MAX);

        if(startPoint < myList.size() / 2)
        {
            myList.insert(next(myList.begin(), startPoint), i);
        }
        else
        {
            myList.insert(prev(myList.end(), myList.size() - startPoint), i);
        }
    }

    std::cout << "list time: " << clock() - timer << std::endl;

    std::cout << "\nArbitrary index erasure test:\n\n";

    // Vector start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(vec.size() * (float) rng[i+5000] / RAND_MAX);

        if(startPoint == vec.size()) startPoint --;

        vec.erase(vec.begin() + startPoint);
    }

    std::cout << "vector time: " << clock() - timer << std::endl;

    // PRAL start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(myPral.size() * (float) rng[i+5000] / RAND_MAX);

        if(startPoint == myPral.size()) startPoint --;

        myPral.erase(startPoint);
    }

    std::cout << "pral time: " << clock() - timer << std::endl;
    
    // Deque start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(deq.size() * (float) rng[i+5000] / RAND_MAX);

        if(startPoint == deq.size()) startPoint --;

        deq.erase(deq.begin() + startPoint);
    }

    std::cout << "deque time: " << clock() - timer << std::endl;
    
    // List start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(myList.size() * (float) rng[i+5000] / RAND_MAX);

        if(startPoint == myList.size()) startPoint --;

        if(startPoint < myList.size() / 2)
        {
            myList.erase(next(myList.begin(), startPoint));
        }
        else
        {
            myList.erase(prev(myList.end(), myList.size() - startPoint));
        }
    }

    std::cout << "list time: " << clock() - timer << std::endl;


    // Checking to ensure the PRAL matches the Vector:
    ref = myPral.getIndexedReference(0);

    for(int k = 0; k < vec.size(); k++)
    {
        if(vec[k] != ref.getValue())
        {
            std::cout << std::endl << k << " " << vec[k] << " " << ref.getValue();
        }

        ref.forward();
    }
}
