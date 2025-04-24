#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class BiNode {
public:
	int value;
	BiNode* parent;
	vector<BiNode*> children;
	int degree;

	BiNode(int value) {
		this->value = value;
		parent = nullptr;
		degree = 0;
		children.clear();
	}
};

class BinomialHeap {
public:
	vector<BiNode*> trees;
	BiNode* min_node;
	int total;

	BinomialHeap() {
		min_node = nullptr;
		total = 0;
		trees.clear();
	}

	bool is_empty() {
		return min_node == nullptr;
	}

	void find_min() {
		min_node = nullptr;
		for (BiNode* tree : trees)
			if (min_node == nullptr || tree->value < min_node->value)
				min_node = tree;
	}

	void merge(BinomialHeap& other) {
		trees.insert(trees.end(), other.trees.begin(), other.trees.end());
		total += other.total;
		other.trees.clear();
		other.total = 0;
		consolidate();
	} // op_id = 7

	void insert(int value) {
		BiNode* nod = new BiNode(value);
		BinomialHeap heap;
		heap.trees.push_back(nod);
		heap.total++;
		merge(heap);
	} // op_id = 1

	int extract_min() {
		BiNode* minNode = min_node;
		for (auto it = trees.begin(); it != trees.end(); it++)
			if (*it == minNode) {
				trees.erase(it);
				break;
			}
		BinomialHeap heap;
		heap.trees = minNode->children;
		merge(heap);
		find_min();
		total--;
		return minNode->value;
	}

	void link(BiNode* tree1, BiNode* tree2) {
		if (tree2->value < tree1->value)
			swap(tree1, tree2);
		tree2->parent = tree1;
		tree1->children.push_back(tree2);
		tree1->degree++;
	}

	void consolidate() {
		int max_degree = static_cast<int>(floor(log2(total))) + 1;
		vector<BiNode*> degree_to_tree(max_degree + 1, nullptr);
		while (!trees.empty()) {
			BiNode* crt = trees[0];
			trees.erase(trees.begin());
			int degree = crt->degree;
			while (degree_to_tree[degree] != nullptr) {
				BiNode* other = degree_to_tree[degree];
				degree_to_tree[degree] = nullptr;
				if (crt->value < other->value)
					link(crt, other);
				else {
					link(other, crt);
					crt = other;
				}
				degree++;
			}
			degree_to_tree[degree] = crt;
		}
		min_node = nullptr;
		trees.clear();
		for (BiNode* tree : degree_to_tree)
			if (tree != nullptr) {
				trees.push_back(tree);
				if (min_node == nullptr || tree->value < min_node->value)
					min_node = tree;
			}
	}

	void bubble_up(BiNode* node) {
		BiNode* parent = node->parent;
		while (parent != nullptr && node->value < parent->value) {
			swap(node->value, parent->value);
			node = parent;
			parent = node->parent;
		}
	}

	void delete_node(BiNode* node) {
		node->value = INT_MIN;
		bubble_up(node);
		consolidate();
		extract_min();
	}

	BiNode* find_in_tree(BiNode* node, int value) {
		if (node == nullptr)
			return nullptr;
		if (node->value == value)
			return node;
		for (BiNode* child : node->children) {
			BiNode* result = find_in_tree(child, value);
			if (result != nullptr)
				return result;
		}
		return nullptr;
	}

	BiNode* find_value(int value) {
		for (BiNode* tree : trees) {
			BiNode* found = find_in_tree(tree, value);
			if (found != nullptr)
				return found;
		}
		return nullptr;
	}

	void delete_value(int value) {
		BiNode* node = find_value(value);
		if (node != nullptr)
			delete_node(node);
	} // op_id = 2

	int max_less_than_in_tree(BiNode* node, int value, int maxValue) {
		if (node == nullptr)
			return maxValue;
		if (node->value <= value && node->value > maxValue)
			maxValue = node->value;
		for (BiNode* child : node->children)
			maxValue = max_less_than_in_tree(child, value, maxValue);
		return maxValue;
	}

	int max_less_than(int value) {
		int maxValue = INT_MIN;
		for (BiNode* tree : trees)
			maxValue = max_less_than_in_tree(tree, value, maxValue);
		if (maxValue == INT_MIN)
			return -1;
		return maxValue;
	}

	int min_more_than_in_tree(BiNode* node, int value, int minValue) {
		if (node == nullptr)
			return minValue;
		if (node->value >= value && node->value < minValue)
			minValue = node->value;
		for (BiNode* child : node->children)
			minValue = min_more_than_in_tree(child, value, minValue);
		return minValue;
	}

	int min_more_than(int value) {
		int minValue = INT_MAX;
		for (BiNode* tree : trees)
			minValue = min_more_than_in_tree(tree, value, minValue);
		if (minValue == INT_MAX)
			return -1;
		return minValue;
	}

	void collect_in_range(BiNode* node, int x, int y, vector<int>& result) {
		if (node == nullptr)
			return;
		if (node->value >= x && node->value <= y)
			result.push_back(node->value);
		for (BiNode* child : node->children)
			collect_in_range(child, x, y, result);
	}

	vector<int> get_sorted_in_range(int x, int y) {
		vector<int> result;
		for (BiNode* tree : trees)
			collect_in_range(tree, x, y, result);
		sort(result.begin(), result.end());
		return result;
	}
};

int main() {

  return 0;
}