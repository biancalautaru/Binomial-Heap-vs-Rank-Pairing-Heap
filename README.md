# Heap Efficiency Comparison
*(project by Cocu Matei-Iulian & Lăutaru Bianca-Maria)*

This project goes over the comparison between the Binomial Heap and the Rank-Pairing Heap, in terms of efficiency in various different contexts and the importance of operation-optimizations.

## Table of Contents
1. [Introduction](#1-introduction)
2. [Query Generator](#2-query-generator)
3. [Binomial Heap](#3-binomial-heap)
    - [3.1. Description](#31-description)
    - [3.2. Complexities](#32-complexities)
    - [3.3. Implementation](#33-implementation)
        - [3.3.1. Structure](#331-structure)
        - [3.3.2. Operations](#332-operations)
4. [Rank-Pairing Heap](#4-rank-pairing-heap)
    - [4.1. Description](#41-description)
    - [4.2. Complexities](#42-complexities)
    - [4.3. Implementation](#43-implementation)
        - [4.3.1. Structure](#431-structure)
        - [4.3.2. Operations](#432-operations)
5. [Comparison](#5-comparison)
6. [Resources](#6-resources)

## 1. Introduction

This documentation will go through the actual implementations of all components of this project and the ideas behind them; the classes used in the heap applications are kept separate, each having its header file (`binomial_heap.h` and `rank_pairing_heap.h`), while the query generator is defined in the `query_generator.h` file.

## 2. Query Generator

The generator's primary aim is to have a *weighted decision based system* so that the numbers printed could correlate with each other in necessary circumstances. This outlines the seven arguments required for `generate_test_file`, the *main function* that is in charge of query creation.

To put it another way, the last four arguments indicate the percentage of a **type** of operation to be called for, while the first three arguments are intended for the *name of the generated file*, the number of *maximum possible heaps that can be built* from the queries, and the *actual number of queries* contained by the file.

For the *randomness* effect of the numbers selected to be written, the implementation utilises the `<random>` library, available after **C++11**, by importing the **Mersenne Twister 19937** generator `(mt19937)`, an instantiation of `mersenne_twister_engine`; function `int rand_num(int low, int high)` is defined, taking as arguments both (lower and upper) bounds of the number that is to be "picked".

Diving into the functionality of the main loop of this main function for query generation, the *maximum number of heaps that can be reached* and the *number of queries to be generated* are passed from the parameters and written on the first line of the file to be generated; after that, the values of weights for the decision of frequency of some operations is determined based on the last four values passed as parameters (as explained earlier).

The algorithm keeps track of all the numbers generated for the heaps in a vector of sets, for quick access; if the program just started writing out queries, obviously, the first operation should be an **insert type** operation. If not, the program picks a random heap to perform the chosen operation on, and, obviously, the operation itself; if the operation is of **insert type**, there is a slight *(10%)* chance of creating a new heap to be used in further queries from that point on.

After the function determines a heap and an operation to be performed, we calculate the arguments that have to be written for that specific operation: in case of an **insertion**, a new number that hasn't been used in the current heap is picked; in case of a **deletion**, there is a small chance of picking a completely random number that may or may not be part of the current heap, but at most times we look for a number that has already been inserted before in the current heap (here's where the `void heap_num_picker(const std::set<int>& heap_set, int &x)` comes in handy, a function that randomly picks a numerical value that is already contained in the given heap). For **search type** operations, the algorithm picks a random number that already exists in the heap and outputs a value accordingly. Finally, if the operation is a **merge type**, the function will randomly pick a secondary heap (that is not the same as the firstly picked heap, and after that it deletes its existence from the vector of sets).

## 3. Binomial Heap

### 3.1. Description

A *binomial heap* is a data structure that acts as a priority queue. It is an example of a mergeable / meldable heap, as it supports merging two heaps in logarithmic time.

A binomial heap is implemented as a set of *binomial trees*, which are defined recursively as follows:
- A binomial tree of order `0` is a single node
- A binomial tree of order `k` has a root node whose children are roots of binomial trees of orders `k-1`, `k-2`, ..., `2`, `1`, `0` (in this order).

A *binomial tree* of order `k` has the following properties:
- It has exactly `2`<sup>`k`</sup> nodes.
- It has a depth of `k`.
- Each binomial tree in a heap obeys the minimum-heap property: the key of a node is greater than or equal to the key of its parent.
- There can be at most one binomial tree for each order, including zero order.

A binomial heap with `n` nodes has the number of binomial trees equal to the number of set bits in the *binary representation* of `n`. We can relate the degree of these binomial trees with the positions of set bits. With this relation, we can conclude that there are `O(log n)` Binomial Trees in a Binomial Heap with `n` nodes.

![binomial tree](https://github.com/user-attachments/assets/2ba2c1a6-736f-4044-a113-0a631513f65c)

### 3.2 Complexities

|     Operation     | find-min |  insert   |  delete  | find |   meld   | largest less than | smallest greater than | sort interval |
|:-----------------:|:--------:|:---------:|:--------:|:----:|:--------:|:-----------------:|:---------------------:|:-------------:|
| **Binomial Heap** |   O(1)   | O(1) (am) | O(log n) | O(n) | O(log n) |       O(n)        |         O(n)          |  O(n log k)   |

*where n is the number of nodes and k is the length of the interval*

### 3.3. Implementation

#### 3.3.1. Structure

The implementation of the Binomial Heap is encapsulated in two classes:

**`BiNode`** - represents a node in a binomial tree:
- `value`: The key or value of the node.
- `parent`: A pointer to its parent.
- `children`: A list of pointers to its child nodes.
- `degree`: The order of the node.

**`BinomialHeap`** - represents the heap as a collection of binomial trees:  
- `trees`: A vector of roots of binomial trees.
- `min_node`: Pointer to the node with the minimum value.
- `total`: Count of total elements in the heap.

#### 3.3.2. Operations:

- ***find-min*** - `heap.min_node`: a pointer to the node with the minimum value is stored in the heap at all times.

- ***insert*** - `insert(value)`: inserts a new value by creating a single-node heap and merging it into the current heap.

- ***delete*** - `delete_value(value)`: locates a node with the given value, assigns it the lowest possible value, bubbles it up to the root and then removes the root using the `extract_min` function.

- ***find*** - `find_value(value)`: iterates through the roots of all binomial trees and performs a recursive depth-first search with the helper function `find_in_tree`.

- ***meld*** - `merge(other)`: combines another binomial heap into the current one by appending all trees from the other heap into the current heap's tree list. It then updates the total node count and calls `consolidate()` to ensure that the binomial heap properties are maintained.

- ***largest less than*** - `max_less_than(value)` and ***smallest greater than*** - `min_more_than(value)`: traverse all nodes to find the values.

- ***sort interval*** - `get_sorted_in_range(x, y)`: collects all values in the specified range and sorts them.

## 4. Rank-Pairing Heap

### 4.1. Description

A **rank-pairing heap** is an advanced priority queue data structure that combines the asymptotic efficiency of *Fibonacci heaps* with much of the simplicty of *pairing heaps*. Unlike all other heap implementations that match the bounds of *Fibonacci heaps*, our structure needs only one cut and no other *structural changes* per `key decrease`; the trees representing the heap can therefore evolve to have arbitrary structure.

Rank-pairing heaps consist of a collection of trees that satisfy the heap property:
- Each node has a key and the key of the node is less than or equal to the keys of its children *(basic property of a min-heap)*.
- The trees are arranged in a *linked list*, with each tree's root participating in this list.

Each node has a **rank** that helps maintain the structural integrity of the heap during operations.

Key properties:
- A rank-pairing heap with `n` nodes has `O(log n)` trees.
- The trees in a rank-pairing heap can be either **type-1** or **type-2** trees.
- **Type-1 trees** have the property that the rank of a node is 1 more than the rank of its right child; simpler but harder to analyze and has larger constant factors in the time bounds.
- **Type-2 trees** have the property that the rank of a node equals the rank of its right child; a relaxed version that is easier to analyze and has smaller constant factors in the time bounds.
- Each tree satistfies the **rank rule**: the rank of a node is at least the rank of *its left child*.

### 4.2. Complexities

|     Operation     | find-min |  insert   |  delete  | find |   meld   | largest less than | smallest greater than | sort interval |
|:-----------------:|:--------:|:---------:|:--------:|:----:|:--------:|:-----------------:|:---------------------:|:-------------:|
| **Rank-Pairing Heap** |   Θ(1)   | Θ(1) | O(log n) (am.) | O(n) | Θ(1) |       O(n)        |         O(n)          |  O(n log k)   |

*where n is the number of nodes and k is the length of the interval*

### 4.3. Implementation

#### 4.3.1. Structure

The implementation of the Binomial Heap is encapsulated in two classes:

**`RpNode`** - represents a node in a rank-pairing heap:
- `value`: The key or value of the node.
- `rank`: Rank of the node.
- `parent`: A pointer to its parent.
- `left_child`:
- `right_sibling`: 

**`BinomialHeap`** - represents the heap as a ranked-collection of its nodes:  
- `root`: Current root the of the heap (can be changed at any time).

#### 4.3.2. Operations

- ***find-min*** - `heap.root`: a pointer to the node with the minimum value is stored in the heap at all times.

- ***insert*** - `insert(value)`: creates a new node with the given value, linking this node with the existing root using the `link(h1, h2)` function (also ensures that the node with the smaller value becomes the root).

- ***delete*** - `delete_value(value)`: locates a node with the given value, assigns it the lowest possible value, bubbles it up to the root and then removes the root using the `extract_min` function. This operation requires finding the node *(O(n) in this implementation)*, followed by bubble-up *(O(log n))* and extract-min *(O(log n))*. The overall complexity is dominated by the find operation which requires traversing the entire heap in the worst case.

- ***find*** - `find_value(value)`: iterates through the roots of all binomial trees and performs a recursive depth-first search with the helper function `contains_in_subtree(root, value)`.

- ***largest less than*** - `max_leq(value)` and ***smallest greater than*** - `min_geq(value)`: traverse all nodes to find the values.

- ***sort interval*** - `sorted_in_range(x, y)`: collects all values in the specified range (using the helper function `collect_in_range(root, x, y, result)`) and sorts the values returned as a vector (from `result`).

- ***meld*** - `meld(other)`: combines another rank-pairing heap into the current one by linking the two roots of the heaps (using the helper function `link(h1, h2)`).

## 5. Comparison

![n=5,q=5000](https://github.com/user-attachments/assets/3f46ca4a-9b46-4639-b483-ccdc82fba4bb)
![n=20,q=200000](https://github.com/user-attachments/assets/2d8a05a7-7fd5-4709-8808-f75d2f679195)
![n=100,q=1000000](https://github.com/user-attachments/assets/dbd92c01-d6b4-4d7e-a588-97f2109b1925)


## 6. Resources

*Binomial Heap:*
[Wikipedia](https://en.wikipedia.org/wiki/Binomial_heap),
[GeeksforGeeks](https://www.geeksforgeeks.org/binomial-heap-2)

*Rank-Pairing Heap:*
[Wikipedia - Comparison of theoretic bounds](https://en.wikipedia.org/wiki/Heap_(data_structure)), [Princeton University](https://www.cs.princeton.edu/courses/archive/spr10/cos423/handouts/rankpairingheaps.pdf)