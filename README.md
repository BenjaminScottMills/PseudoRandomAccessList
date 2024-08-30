# PseudoRandomAccessList

The pseudo-random-access list (pral) is a sequence container consisting of a binary tree overlaid on the nodes of a doubly-linked list.

Prals can store elements in any order. They also support iterators which take a constant time to move forward or backward by one element.

It is optimised for a combination of accessing elements by index (O(sqrt(n)) time complexity) and mutation (insert/erase) at beginning, end, or middle (O(sqrt(n)) time complexity). While this is inferior to a self-balancing binary tree modified to store unsorted elements in a linear arrangement (which has O(Log(n)) time complexity for both of those operations), iteration through a pral is faster (as the number of elements increaces, the time it takes to iterate through a pral approaches half the time it takes to iterate through a balanced binary tree). All in all, this means that a pral is mostly inferior to some other sequence container; since vectors allow for faster iteration than prals due to storing elements in a contiguous block, a pral can only be the most efficient sequence container for a hypothetical algorithm involving element access, mutation at the middle, and iteration (occuring sufficently infrequently relative to mutation that a vector doesn't become the best choice).

pralDemonstration.cpp compares a pral with a vector, list, and deque as they perform modification at arbitrary indices (a combination of access and mutation operations).
