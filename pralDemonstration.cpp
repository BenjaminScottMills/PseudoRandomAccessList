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

    for(int i = 5; i < 100000; i++)
    {
        myPral.insert(-i, 0);
        vec.insert(vec.begin(), -i);
        deq.push_front(-i);
        myList.push_front(-i);
    }

    std::cout << "Sample algorithm test:\n\n";

    // Vector start
    timer = clock();

    for(int i = 0; i < 10000; i += 1)
    {
        startPoint = lround(vec.size() * (float) rng[i] / RAND_MAX);

        if(startPoint == vec.size()) startPoint --;

        vec[startPoint] = i;

        for(int j = 0; j < 30; j++)
        {
            if(startPoint + j == vec.size()) break;

            if((vec[startPoint + j] % 3))
            {
                vec.insert(vec.begin() + startPoint + j + 1, i + j*100000 + 1);
            }
        }
    }

    std::cout << "vector time: " << clock() - timer << std::endl;

    // PRAL start
    timer = clock();

    for(int i = 0; i < 10000; i += 1)
    {
        startPoint = lround(myPral.size() * (float) rng[i] / RAND_MAX);

        if(startPoint == myPral.size()) startPoint --;

        ref = myPral.getIndexedReference(startPoint);

        ref.getNode()->value = i;

        for(int j = 0; j < 30; j++)
        {
            if(startPoint + j == myPral.size()) break;

            if((ref.getValue() % 3))
            {
                myPral.insertAfter(i + j*100000 + 1, ref);
            }

            ref.forward();
        }
    }

    std::cout << "pral time: " << clock() - timer << std::endl;

    // Deque start
    timer = clock();

    for(int i = 0; i < 10000; i += 1)
    {
        startPoint = lround(deq.size() * (float) rng[i] / RAND_MAX);

        if(startPoint == deq.size()) startPoint --;

        deq[startPoint] = i;

        for(int j = 0; j < 30; j++)
        {
            if(startPoint + j == deq.size()) break;

            if((deq[startPoint + j] % 3))
            {
                deq.insert(deq.begin() + startPoint + j + 1, i + j*100000 + 1);
            }
        }
    }

    std::cout << "deque time: " << clock() - timer << std::endl;

    // List start
    timer = clock();

    for(int i = 0; i < 10000; i += 1)
    {
        startPoint = lround(myList.size() * (float) rng[i] / RAND_MAX);

        if(startPoint == myList.size()) startPoint --;

        if(startPoint < myList.size() / 2)
        {
            listIterator = myList.begin();

            advance(listIterator, startPoint);
        }
        else
        {
            listIterator = myList.end();

            listIterator = prev(listIterator, myList.size() - startPoint);
        }

        *listIterator = i;

        for(int j = 0; j < 30; j++)
        {
            if(startPoint + j == myList.size()) break;

            if((*listIterator % 3))
            {
                if(listIterator == myList.end())
                {
                    myList.push_back(i + j*100000 + 1);
                    break;
                }

                myList.insert(next(listIterator), i + j*100000 + 1);
            }

            ++listIterator;
        }
    }

    std::cout << "list time: " << clock() - timer << std::endl;


    // Checking to ensure the 3 sequence containers match
    listIterator = myList.begin();
    ref = myPral.getIndexedReference(0);

    for(int k = 0; k < vec.size(); k++)// 902
    {
        if(*listIterator != vec[k] || vec[k] != ref.getValue())
        {
            std::cout << std::endl << k << " " << vec[k] << " " << ref.getValue() << " " << *listIterator;
        }

        advance(listIterator, 1);
        ref.forward();
    }

    std::cout << "\n\nArbitrary index insertion test:\n\n";
    
    for(int i = 5; i < 800000; i++)
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

        if(startPoint == vec.size()) startPoint --;

        vec.insert(vec.begin() + startPoint, i);
    }

    std::cout << "vector time: " << clock() - timer << std::endl;

    // PRAL start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(myPral.size() * (float) rng[i] / RAND_MAX);

        if(startPoint == myPral.size()) startPoint --;

        myPral.insert(i, startPoint);
    }

    std::cout << "pral time: " << clock() - timer << std::endl;
    
    // Deque start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(deq.size() * (float) rng[i] / RAND_MAX);

        if(startPoint == deq.size()) startPoint --;

        deq.insert(deq.begin() + startPoint, i);
    }

    std::cout << "deque time: " << clock() - timer << std::endl;
    
    // List start
    timer = clock();

    for(int i = 0; i < 5000; i += 1)
    {
        startPoint = lround(myList.size() * (float) rng[i] / RAND_MAX);

        if(startPoint == myList.size()) startPoint --;

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


    // Checking to ensure the 3 sequence containers match
    listIterator = myList.begin();
    ref = myPral.getIndexedReference(0);

    for(int k = 0; k < vec.size(); k++)// 902
    {
        if(*listIterator != vec[k] || vec[k] != ref.getValue())
        {
            std::cout << std::endl << k << " " << vec[k] << " " << ref.getValue() << " " << *listIterator;
        }

        advance(listIterator, 1);
        ref.forward();
    }
}