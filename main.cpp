#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "query_generator.h"
#include "binomial_heap.h"
#include "rank_pairing_heap.h"

using namespace std;

int main() {
    // generate_test_file("silly", 4, 100, 53, 8, 35, 4);
    vector<int> sizes = {50000, 200000, 1000000};
    unordered_map<string, vector<int>> presets = {
    {"basic", {53, 8, 35, 4}},
    {"no_deletions", {54, 0, 42, 4}},
    {"only_insertions", {100, 0, 0, 0}},
    {"melding", {80, 0, 0, 20}}
    };

    for (auto s : sizes) {
        for (auto p : presets) {
            string filename = p.first + "_" + to_string(s);
            generate_test_file(filename, s / 10000, s, p.second[0], p.second[1], p.second[2], p.second[3]);
            /*
             testcases, run time, benchmarking
             */
            ifstream r(filename);
            int N, Q;
            r >> N >> Q;
            for (int i = 0; i < Q; i++) {
                
            }
        }
    }

    return 0;
}