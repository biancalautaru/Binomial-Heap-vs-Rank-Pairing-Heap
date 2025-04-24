#ifndef QUERY_GENERATOR_H
#define QUERY_GENERATOR_H
#include <string>
#include <set>

namespace rand_f{
    template<typename T>
    T rand_num(T low, T high);
}

template<typename T>
void heap_num_picker(std::set<T> heap_set, T &x);

template<typename T>
void generate_test_file(const std::string& filename, int num_of_heaps,
    int queries, int ins_w, int del_w, int see_w, int mer_w);
#endif
/*
    ** elaborarea tipurilor de teste - masuri**
    1 - insert --------> [1, ins_w]
    2 - delete --------> [ins_w + 1, del_w]
    3, 4, 5, 6 - seek -> [del_w + 1, see_w]
    7 - merge ---------> [see_w + 1, mer_w]
    # marimi de teste
        - 100.000
        - 1.000.000
    # tipuri de teste ("pre-built")
        - basic (53, 8, 35, 4)
        - no_deletions (54, 0, 42, 4)
        - only_insertions (100, 0, 0, 0)
        - melding (80, 0, 0, 20)
*/