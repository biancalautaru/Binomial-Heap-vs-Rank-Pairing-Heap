#include <fstream>
#include <random>
#include <set>
#include <vector>
#include <algorithm>

#define MAX_VAL 1000000000

namespace rand_f {
    std::mt19937 rng(std::random_device{}());

    int rand_num(int low, int high) {
        std::uniform_int_distribution<int> dist(low, high);
        return dist(rng);
    }
}

void heap_num_picker(const std::set<int>& heap_set, int &x) {
    if (heap_set.empty()) return;
    auto it = heap_set.begin();
    std::advance(it, rand_f::rand_num(0, heap_set.size() - 1));
    x = *it;
}

void generate_test_file(const std::string& filename, int num_of_heaps, int queries,
    int ins_w, int del_w, int see_w, int mer_w) {

    const int N = num_of_heaps;
    const int Q = queries;
    std::ofstream out(filename);
    out << N << ' ' << Q << '\n';

    int heap_count = 0;
    std::vector<std::set<int>> heaps;

    for (int i = 0; i < Q; i++) {
        int op_id, h1;
        if (!heap_count) {
            op_id = 1;
        } else {
            h1 = rand_f::rand_num(0, heap_count - 1);
            int q1 = ins_w, q2 = q1 + del_w, q3 = q2 + see_w, q4 = q3 + mer_w;
            int c = rand_f::rand_num(1, q4);
            if (c <= q1) op_id = 1;
            else if (c <= q2) op_id = 2;
            else if (c <= q3 || heaps[h1].size() < 2) op_id = rand_f::rand_num(3, 6);
            else op_id = 7;
        }

        if ((op_id == 1 && heap_count < N && rand_f::rand_num(1, 100) <= 10) || !heap_count) {
            heaps.emplace_back();
            h1 = heap_count++;
        }

        switch (op_id) {
            case 1: {  // insert
                int x;
                do {
                    x = rand_f::rand_num(-MAX_VAL, MAX_VAL);
                } while (heaps[h1].count(x));
                heaps[h1].insert(x);
                out << "1 " << h1 + 1 << ' ' << x << '\n';
                break;
            }
            case 2: { // delete
                int pick = rand_f::rand_num(1, 100), x;
                if (pick <= 70 && !heaps[h1].empty()) {
                    heap_num_picker(heaps[h1], x);
                    heaps[h1].erase(x);
                } else {
                    x = rand_f::rand_num(-MAX_VAL, MAX_VAL);
                }
                out << "2 " << h1 + 1 << ' ' << x << '\n';
                break;
            }
            case 3: { // contains
                int pick = rand_f::rand_num(1, 100), x;
                if (pick <= 70 && !heaps[h1].empty()) {
                    heap_num_picker(heaps[h1], x);
                } else {
                    x = rand_f::rand_num(-MAX_VAL, MAX_VAL);
                }
                out << "3 " << h1 + 1 << ' ' << x << '\n';
                break;
            }
            case 4: { // max ≤ x
                if (!heaps[h1].empty()) {
                    int val;
                    heap_num_picker(heaps[h1], val);
                    int x = rand_f::rand_num(val, val + 1234);
                    out << "4 " << h1 + 1 << ' ' << x << '\n';
                }
                break;
            }
            case 5: { // min ≥ x
                if (!heaps[h1].empty()) {
                    int val;
                    heap_num_picker(heaps[h1], val);
                    int x = rand_f::rand_num(val - 1234, val);
                    out << "5 " << h1 + 1 << ' ' << x << '\n';
                }
                break;
            }
            case 6: { // sorted interval
                if (heaps[h1].size() >= 2) {
                    int v1, v2;
                    heap_num_picker(heaps[h1], v1);
                    heap_num_picker(heaps[h1], v2);
                    if (v1 > v2) std::swap(v1, v2);
                    int x = v1 - rand_f::rand_num(0, 1234);
                    int y = v2 + rand_f::rand_num(0, 1234);
                    out << "6 " << h1 + 1 << ' ' << x << ' ' << y << '\n';
                }
                break;
            }
            case 7: { // meld
                if (heap_count > 1) {
                    int h2;
                    do {
                        h2 = rand_f::rand_num(0, heap_count - 1);
                    } while (h2 == h1);

                    for (int val : heaps[h2])
                        heaps[h1].insert(val);
                    heaps[h2].clear();
                    out << "7 " << h1 + 1 << ' ' << h2 + 1 << '\n';
                }
                break;
            }
            default: break;
        }
    }
}