#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include "header_files/generator.h"
#include "header_files/binomial_heap.h"
#include "header_files/rank_pairing_heap.h"

using namespace std;

int main() {
    generate_test_file("tests/test1.txt", 10, 1000);
	// generate_test_file("tests/test2.txt", 100, 1000000);
	// generate_test_file("tests/test3.txt", 1000, 1000000);

    // vector<int> sizes = {50000, 200000, 1000000};
    // unordered_map<string, vector<int>> presets = {
    // {"basic", {53, 8, 35, 4}},
    // {"no_deletions", {54, 0, 42, 4}},
    // {"only_insertions", {100, 0, 0, 0}},
    // {"melding", {80, 0, 0, 20}}
    // };

    chrono::time_point<chrono::system_clock> start_time, end_time;
    chrono::duration<double> time;
    vector<RankPairingHeap> rp_heaps;
    vector<BinomialHeap> bi_heaps;
    vector<int> result;
    ofstream res("results/results.txt");
    res << fixed << setprecision(10);

    for (int t = 1; t <= 1; t++) {
        string filename = "tests/test" + to_string(t) + ".txt";
        string outputfile = "results/output_" + filename.substr(6);
        ifstream r(filename);
        ofstream w(outputfile);
        int N, Q, op_id, heap_id, x, y, heap_id2;
        r >> N >> Q;

        bi_heaps.assign(N + 1, BinomialHeap());
        start_time = chrono::high_resolution_clock::now();
        for (int i = 0; i < Q; i++) {
            r >> op_id >> heap_id;
            switch (op_id) {
                case 1: {
                    r >> x;
                    bi_heaps[heap_id].insert(x);
                    break;}
                case 2: {
                    r >> x;
                    bi_heaps[heap_id].delete_value(x);
                    break;}
                case 3: {
                    r >> x;
                    if (bi_heaps[heap_id].find_value(x))
                        w << "1\n";
                    else
                        w << "0\n";
                    break;}
                case 4: {
                    r >> x;
                    w << bi_heaps[heap_id].max_less_than(x) << '\n';
                    break;}
                case 5: {
                    r >> x;
                    w << bi_heaps[heap_id].min_more_than(x) << '\n';
                    break;}
                case 6: {
                    r >> x >> y;
                    result = bi_heaps[heap_id].get_sorted_in_range(x, y);
                    for (auto num : result) w << num << " ";
                    w << '\n';
                    break;}
                case 7: {
                    r >> heap_id2;
                    bi_heaps[heap_id].merge(bi_heaps[heap_id2]);
                    break;}
                case 8: {
                    bi_heaps[heap_id].extract_min();
                    break;}
                default: break;
            }
        }
        end_time = chrono::high_resolution_clock::now();
        time = end_time - start_time;
        res << filename.substr(6) << " | N = " << N << " | Q = " << Q << " | Binomial | " << time.count() << " secunde\n";
        cout << filename.substr(6) << " | Binomial | Done!\n";

        rp_heaps.assign(N + 1, RankPairingHeap());
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
                    result = rp_heaps[heap_id].sorted_range(x, y);
                    for (auto num : result) w << num << " ";
                    w << '\n';
                    break;}
                case 7: {
                    r >> heap_id2;
                    rp_heaps[heap_id].meld(rp_heaps[heap_id2]);
                    break;}
                case 8: {
                    w << rp_heaps[heap_id].ext_min() << '\n';
                    break;}
                default: break;
            }
        }
        end_time = chrono::high_resolution_clock::now();
        time = end_time - start_time;
        res << filename.substr(6) << " | N = " << N << " | Q = " << Q << " | Binomial | " << time.count() << " secunde\n";
        cout << filename.substr(6) << " | Rank-Pairing | Done!\n";
    }
    return 0;
}