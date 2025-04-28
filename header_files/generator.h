#include <vector>
#include <string>
using namespace std;

namespace rand_f {int rand_num(int low, int high);}

void generate_numbers(vector<int>& available);

int get_unique_number(const vector<int>& available, int index);

void generate_test_file(const string& filename, int n, int q);