#include <fstream>
#include <random>
#include <set>
#include <vector>
#include <algorithm>
#include "query_generator.h"

#define MAX_VAL 1000000000

namespace rand_f {
    std::mt19937 rng(std::random_device{}());
    // random number picker

    int rand_num(int low, int high) {
        std::uniform_int_distribution<int> dist(low, high);
        return dist(rng);
    }
}

void heap_num_picker(std::set<int> heap_set, int &x) {
    auto it = heap_set.begin();
    std::advance(it, rand_f::rand_num(0, heap_set.size() - 1));
    x = *it;
}

void generate_test_file(const std::string& filename, int num_of_heaps, int queries,
    int ins_w, int del_w, int see_w, int mer_w) {
    const int N = num_of_heaps; // number of heaps
    const int Q = queries; // number of queries
    std::ofstream out(filename); // open the text file
    out << N << ' ' << Q << std::endl; // display the number of queries

    int heap_count = 0;
    std::vector<std::set<int>> heaps;

    for (int i = 0; i < Q; i++) {
        int op_id, h1; // operation number
        if (!heap_count) {
            op_id = 1; // only insert if empty
        } else {
            h1 = rand_f::rand_num(0, heap_count - 1);
            int q1 = ins_w, q2 = q1 + del_w, q3 = q2 + see_w, q4 = q3 + mer_w;
            int c = rand_f::rand_num(1, q4); // weighted choice
            if (c <= q1) op_id = 1;      // insert
            else if (c <= q2) op_id = 2; // delete
            else if (c <= q3 || heaps[h1].size() < 2) op_id = rand_f::rand_num(3, 6);
            else op_id = 7; // meld
        }

        if ((op_id == 1 && heap_count < N && rand_f::rand_num(1, 100) <= 10)
            || !heap_count) {
            heaps.emplace_back();
            h1 = heap_count++; // create a new heap
        }

        switch (op_id) {
            case 1: {  // insert
                int x; // a number that
                do {   // isn't already in the heap
                    x = rand_f::rand_num(-MAX_VAL, MAX_VAL);
                } while (heaps[h1].count(x));

                heaps[h1].insert(x); // insert into heap
                out << "1 " << h1 + 1 << ' ' << x << std::endl;
                break;
            }
            case 2: { // delete
                int pick = rand_f::rand_num(1, 100), x;
                if (pick <= 70 && !heaps[h1].empty()) {
                    heap_num_picker(heaps[h1], x);
                    heaps[h1].erase(x);
                } else x = rand_f::rand_num(-MAX_VAL, MAX_VAL);
                out << "2 " << h1 + 1 << ' ' << x << std::endl;
                break;
            }
            case 3: { // appartenance
                int pick = rand_f::rand_num(1, 100), x;
                if (pick <= 70) heap_num_picker(heaps[h1], x);
                else x = rand_f::rand_num(-MAX_VAL, MAX_VAL);
                out << "3 " << h1 + 1 << ' ' << x << std::endl;
                break;
            }
            case 4: { // biggest small
                if (!heaps[h1].empty()) {
                    int val;
                    heap_num_picker(heaps[h1], val);
                    int x = rand_f::rand_num(val, val + 1234);
                    out << "4 " << h1 + 1 << ' ' << x << std::endl;
                }
                break;
            }
            case 5: { // smallest big
                if (!heaps[h1].empty()) {
                    int val;
                    heap_num_picker(heaps[h1], val);
                    int x = rand_f::rand_num(val - 1234, val);
                    out << "5 " << h1 + 1 << ' ' << x << std::endl;
                }
                break;
            }
            case 6: { // sorted interval
                int v1, v2;
                heap_num_picker(heaps[h1], v1);
                heap_num_picker(heaps[h1], v2);
                if (v1 > v2) std::swap(v1, v2);
                int x = v1 - rand_f::rand_num(0, 1234);
                int y = v2 + rand_f::rand_num(0, 1234);
                out << "6 " << h1 + 1 << ' ' << x << ' ' << y << std::endl;
                break;
            }
            case 7: { // meld
                int h2;
                do {
                    h2 = rand_f::rand_num(0, heap_count - 1);
                } while (h2 == h1);

                for (int val : heaps[h2]) heaps[h1].insert(val);
                heaps[h2].clear();
                out << "7 " << h1 + 1 << ' ' << h2 + 1<< std::endl;
                break;
            }
            default: break;
        }
    }
}