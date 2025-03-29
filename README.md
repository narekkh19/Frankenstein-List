Frankenstein List
Introduction
The Frankenstein List is a self-organizing, doubly linked list implementation inspired by the idea presented in this Medium article. While the core concept was derived from the post, the implementation and design are entirely my own. The goal of this structure is to manage a linked list that maintains a sorted order while offering efficient insertion and deletion operations.

Key Features:
Dual Sorting: The list maintains two different orders—ascending and descending. This allows for versatile traversal and efficient access to elements in both orders.

Efficient Insertions and Deletions: The list is designed to efficiently manage insertions in sorted order, as well as removals, with automatic reorganization of its internal structure.

Flexible Traversals: The list can be traversed from head to tail, tail to head, in ascending sorted order, and in descending sorted order.

Data Structure Overview
The frankenstein list is built on a doubly linked list with additional pointers to manage the ascending and descending sorted orders. The key components of the list are:

Node Structure: Each node in the list contains:

The value of the node.

Pointers to the next and previous nodes.

Pointers to the nodes in ascending and descending sorted orders.

Main List: The list maintains pointers to both the head and tail of the list, along with pointers to the head nodes of both the ascending and descending sorted sublists.

Operations:
push_back(T val): Adds a value to the end of the list and reorganizes the list to maintain sorted order.

push_front(T val): Adds a value to the beginning of the list while ensuring sorted order.

pop_back(): Removes the last element from the list and reorders the remaining elements.

pop_front(): Removes the first element from the list and reorganizes.

insert(T val, int pos): Inserts a value at a specific position in the list, reordering the list afterward.

erase(int pos): Removes the element at a specific position, ensuring that the sorted order is maintained.

printfrom_head(), printfrom_tail(), printfrom_asc(), printfrom_desc(): These functions provide different ways to traverse and print the list.
