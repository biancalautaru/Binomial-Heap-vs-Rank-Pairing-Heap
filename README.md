# Heap Efficiency Comparison
*(project by Cocu Matei-Iulian & Lăutaru Bianca-Maria)*

This project goes over the comparison between the Binomial Heap and the Rank-Pairing Heap, in terms of efficiency in various different contexts and the importance of operation-optimizations.

## Table of Contents
1. [Introduction](#1-introduction)
2. [Query Generator](#2-query-generator)
3. [Binomial Heap](#3-binomial-heap)
    - [3.1. Description, Complexities](#31-description-complexities)
    - [3.2. Implementation](#32-implementation)
4. [Rank-Pairing Heap](#4-rank-pairing-heap)
    - [4.1. Description, Complexities](#41-description-complexities)
    - [4.2. Implementation](#42-implementation)
5. [Comparison](#5-comparison)
6. [Conclusions, References](#6-conclusions-references)

## 1. Introduction

This documentation will go through the actual implementations of all components of this project and the ideas behind them; the classes used in the heap applications are kept separate, each having its header file (`binomial_heap.h` and `rank_pairing_heap.h`), while the query generator has its pair of source (`query_generator.cpp`) and header (`query_generator.h`) files.

## 2. Query Generator

The generator's primary aim is to have a *weighted decision based system* so that the numbers printed could correlate with each other in necessary circumstances. This outlines the seven arguments required for `generate_test_file`, the *main function* that is in charge of query creation.

To put it another way, the last four arguments indicate the percentage of a **type** of operation to be called for, while the first three arguments are intended for the *name of the generated file*, the number of *maximum possible heaps that can be built* from the queries, and the *actual number of queries* contained by the file.

Since there are multiple queries that can be made *(seven in total)*, they can be ultimately divided into four categories:
* Insertion 
* Deletion
* Search 
* Meld

For the *randomness* effect of the numbers selected to be written, the implementation utilises the `<random>` library, available after **C++11**, by importing the **Mersenne Twister 19937** generator `(mt19937)`, an instantiation of `mersenne_twister_engine`; function `int rand_num(int low, int high)` is defined, taking as arguments both (lower and upper) bounds of the number that is to be "picked".

Diving into the functionality of the main loop of this main function for query generation,  

| Operation  | find-max | delete-max | increase-key | insert    | meld      | make-heap |
|------------|----------|------------|---------------|-----------|-----------|-----------|
| **Binary** | Θ(1)     | Θ(log n)   | Θ(log n)      | Θ(log n)  | Θ(n)      | Θ(n)      |
| **Skew**   | Θ(1)     | O(log n) *(am.)* | O(log n) *(am.)* | O(log n) *(am.)* | O(log n) *(am.)* | Θ(n) *(am.)* |


## 3. Binomial Heap
### 3.1. Description, Complexities
### 3.2. Implementation

## 4. Rank-Pairing Heap
### 4.1. Description, Complexities
### 4.2. Implementation

## 5. Comparison

## 6. Conclusions, References

