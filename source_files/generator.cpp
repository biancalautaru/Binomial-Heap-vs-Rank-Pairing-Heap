#include <fstream>
#include <random>
#include <algorithm>
#define MAX_VAL 1000000
using namespace std;

namespace rand_f {
	std::mt19937 rng(std::random_device{}());
	// random number picker

	int rand_num(int low, int high) {
		std::uniform_int_distribution<int> dist(low, high);
		return dist(rng);
	}
}

void generate_numbers(vector<int>& available) {
	for (int i = -MAX_VAL; i <= MAX_VAL; i++)
		available.push_back(i);
	shuffle(available.begin(), available.end(), rand_f::rng);
}

int get_unique_number(const vector<int>& available, int &index) {
	return available[index++];
}

void generate_test_file(const string& filename, int n, int q) {
  	vector<int> available;
    int index = 0;
  	generate_numbers(available);

  	ofstream fout(filename);
	fout << n << " " << q << "\n";

	vector<vector<int>> heaps(n + 1);
	vector<int> heap_sizes(n + 1, 0);

	for (int i = 1; i <= n; i++) {
		int size = rand_f::rand_num(1, 10);
		for (int j = 0; j < size; j++) {
			int x = get_unique_number(available, index);
			heaps[i].push_back(x);
			fout << "1 " << i << " " << x << "\n";
		}
	}

	while (q--) {
		int op = rand_f::rand_num(1, 7);
		int h = rand_f::rand_num(1, n);
		if (op == 1) { // insert
			int x = get_unique_number(available, index);
			heaps[h].push_back(x);
			fout << op << " " << h << " " << x << "\n";
		}
		else if (op == 2) { // delete
			if (!heaps[h].empty()) {
				int p = rand_f::rand_num(0, heaps[h].size() - 1);
				int x = heaps[h][p];
				swap(heaps[h][p], heaps[h].back());
				heaps[h].pop_back();
				fout << op << " " << h << " " << x << "\n";
			}
			else {
				int x = get_unique_number(available, index);
				heaps[h].push_back(x);
				fout << "1 " << h << " " << x << "\n";
			}
		}
		else if (op == 3) { // is present
			int x;
			if (!heaps[h].empty() && rand_f::rand_num(1, 3) == 1)
				x = heaps[h][rand_f::rand_num(0, heaps[h].size() - 1)];
			else
				x = get_unique_number(available, index);
			fout << op << " " << h << " " << x << "\n";
		}
		else if (op == 4 || op == 5) { // smallest greater than + largest less than
			if (!heaps[h].empty()) {
				int p = rand_f::rand_num(0, heaps[h].size() - 1);
				int x = heaps[h][p];
				int diff = rand_f::rand_num(-500, 500);
				fout << op << " " << h << " " << x + diff << "\n";
			}
			else {
				int x = rand_f::rand_num(-MAX_VAL, MAX_VAL);
				fout << op << " " << h << " " << x << "\n";
			}
		}
		else if (op == 6) { // sort interval
			if (heaps[h].size() >= 2) {
				int p1 = rand_f::rand_num(0, heaps[h].size() - 1);
				int p2 = rand_f::rand_num(0, heaps[h].size() - 1);
				int x = heaps[h][p1];
				int y = heaps[h][p2];
				int diff1 = rand_f::rand_num(-500, 0);
				int diff2 = rand_f::rand_num(0, 500);
				if (x > y)
					swap(x, y);
				fout << op << " " << h << " " << x + diff1 << " " << y + diff2 << "\n";
			}
			else {
				int x = rand_f::rand_num(-MAX_VAL, MAX_VAL);
				int y = rand_f::rand_num(x, MAX_VAL);
				fout << op << " " << h << " " << x << " " << y << "\n";
			}
		}
		else if (op == 7 && rand_f::rand_num(1, 10) == 1) { // merge
			if (n >= 2) {
				int h2 = rand_f::rand_num(1, n);
				while (h == h2)
					h2 = rand_f::rand_num(1, n);
				heaps[h].insert(heaps[h].end(), heaps[h2].begin(), heaps[h2].end());
				heaps[h2].clear();
				fout << "7 " << h << " " << h2 << "\n";
			}
			else {
				int x = get_unique_number(available, index);
				heaps[h].push_back(x);
				fout << "1 " << h << " " << x << "\n";
			}
		}
		else if (op == 8) // afisare + extragere minim
			fout << op << " " << h << "\n";
	}
}