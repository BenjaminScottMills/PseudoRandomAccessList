# PseudoRandomAccessList

The pseudo-random-access list (pral) is a sequential container consisting of a binary tree overlayed on the nodes of a doubly-linked list.

Prals can store elements in any order like a vector, as opposed to only storing sorted elements like a binary search tree. They also support iterators which take a constant time to move forward or backward by one element.

It is optimised for a combination of accessing elements by index (O(log(n)) time complexity) and mutation at beginning, end, or middle (O(n) time complexity, but with a slope that can be arbitrarily decreased at the cost of aditional constant time for element access (via altering the inefficiency modifier properties upon creation)). A key weakness of the pral is that only one element can be inserted or erased at a time.

pralDemonstration.cpp compares a pral with a vector, list, and deque as they perform modification at arbitrary indices (a combination of access and mutation operations).
