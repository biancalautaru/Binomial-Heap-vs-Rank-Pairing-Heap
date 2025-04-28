#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

#include "query_generator.h"
#include "binomial_heap.h"
#include "rank_pairing_heap.h"

using namespace std;

int main() {
    // generate_test_file("box", 4, 100, 53, 8, 35, 4);
    vector<int> sizes = {50000, 200000, 1000000};
    unordered_map<string, vector<int>> presets = {
    {"basic", {53, 8, 35, 4}},
    {"no_deletions", {54, 0, 42, 4}},
    {"only_insertions", {100, 0, 0, 0}},
    {"melding", {80, 0, 0, 20}}
    };
    chrono::time_point<chrono::system_clock> start_time, end_time;
    chrono::duration<double> time;
    vector<RankPairingHeap> rp_heaps;
    vector<BinomialHeap> bi_heaps;
    ofstream res("results");
    for (auto s : sizes) {
        for (auto p : presets) {
            string filename = p.first + "_" + to_string(s) + ".txt";
            string outputfile = "output_" + to_string(s) + "_" + p.first + ".txt";
            generate_test_file(filename, s / 10000, s, p.second[0], p.second[1], p.second[2], p.second[3]);
            ifstream r(filename);
            ofstream w(outputfile);
            int N, Q, op_id, heap_id, x, y, heap_id2;
            r >> N >> Q;

            rp_heaps.assign(N + 1, RankPairingHeap());
            bi_heaps.assign(N + 1, BinomialHeap());

            start_time = chrono::high_resolution_clock::now();
            for (int i = 0; i < Q; i++) {
                r >> op_id >> heap_id;
                switch (op_id) {
                    case 1: {
                        r >> x;
                        rp_heaps[heap_id].insert(x);
                    break;}
                    case 2: {
                        r >> x;
                        rp_heaps[heap_id].delete_value(x);
                    break;}
                    case 3: {
                        r >> x;
                        w << rp_heaps[heap_id].contains(x) << '\n';
                    break;}
                    case 4: {
                        r >> x;
                        w << rp_heaps[heap_id].max_leq(x) << '\n';
                    break;}
                    case 5: {
                        r >> x;
                        w << rp_heaps[heap_id].min_geq(x) << '\n';
                    break;}
                    case 6: {
                        r >> x >> y;
                        vector<int> result = rp_heaps[heap_id].sorted_range(x, y);
                        for (auto num : result) w << num << " ";
                        w << '\n';
                    break;}
                    case 7: {
                        r >> heap_id2;
                        rp_heaps[heap_id].meld(rp_heaps[heap_id2]);
                    break;}
                    default: break;
                }
            }
            end_time = chrono::high_resolution_clock::now();
            time = end_time - start_time;
        }
        res << '\n';
    }

    return 0;
}