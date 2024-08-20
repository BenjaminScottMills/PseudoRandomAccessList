# PseudoRandomAccessList

The pseudo-random-access list (pral) is a sequential container consisting of a binary tree overlayed on the nodes of a doubly-linked list.

Prals can store elements in any order. They also support iterators which take a constant time to move forward or backward by one element.

It is optimised for a combination of accessing elements by index (O(sqrt(n)) time complexity) and mutation at beginning, end, or middle (O(sqrt(n)) time complexity). While this is inferior to a self-balancing binary tree (which has O(Log(n)) time complexity for both of those operations), a pral allows for faster iteration. A key weakness of the pral is that only one element can be inserted or erased at a time.

pralDemonstration.cpp compares a pral with a vector, list, and deque as they perform modification at arbitrary indices (a combination of access and mutation operations).
