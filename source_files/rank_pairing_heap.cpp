#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <climits>
#include <set>
#include <map>
#include <queue>
using namespace std;

class RpNode {
public:
    int value, rank;
    RpNode* parent;
    RpNode* left_child;
    RpNode* right_sibling;

    RpNode(int val) : value(val), rank(0), parent(nullptr), left_child(nullptr), right_sibling(nullptr) {}
};

class RankPairingHeap {
public:
    RpNode* root;

    RankPairingHeap() : root(nullptr) {}

    void insert(int value) {
        RpNode* new_node = new RpNode(value);
        root = link(root, new_node);
    } // op_id = 1

    void delete_value(int value) {
        RpNode* node = find_node(root, value);
        if (!node) return;
        node->value = INT_MIN;
        bubble_up(node);
        extract_min();
    } // op_id = 2

    int contains(int value) const { return contains_in_subtree(root, value) ? 1 : 0; }
    // op_id = 3

    int max_leq(int x) const { return max_leq_in_subtree(root, x, INT_MIN); }
    // op_id = 4

    int min_geq(int x) const { return min_geq_in_subtree(root, x, INT_MAX); }
    // op_id = 5

    vector<int> sorted_range(int x, int y) const {
        vector<int> result;
        collect_in_range(root, x, y, result);
        sort(result.begin(), result.end());
        return result;
    } // op_id = 6

    void meld(RankPairingHeap& other) {
        root = link(root, other.root);
        other.root = nullptr;
    } // op_id = 7

    void extract_min() {
        if (!root) return;

        vector<RpNode*> children;
        RpNode* child = root->left_child;
        while (child) {
            RpNode* next = child->right_sibling;
            child->parent = nullptr;
            child->right_sibling = nullptr;
            children.push_back(child);
            child = next;
        }
        delete root;
        root = nullptr;
        for (RpNode* c : children) {
            root = link(root, c);
        }
    } // op_id = 8

private:
    static RpNode* link(RpNode* a, RpNode* b) {
        if (!a) return b;
        if (!b) return a;
        if (b->value < a->value)
            swap(a, b);

        b->right_sibling = a->left_child;
        if (b->right_sibling)
            b->right_sibling->parent = b;
        a->left_child = b;
        b->parent = a;

        return a;
    }

    static void bubble_up(RpNode* node) {
        while (node->parent && node->value < node->parent->value) {
            swap(node->value, node->parent->value);
            node = node->parent;
        }
    }

    static RpNode* find_node(RpNode* node, int value) {
        if (!node) return nullptr;
        if (node->value == value) return node;
        RpNode* found = find_node(node->left_child, value);
        if (found) return found;
        return find_node(node->right_sibling, value);
    }

    static bool contains_in_subtree(const RpNode* node, int value) {
        if (!node) return false;
        if (node->value == value) return true;
        if (contains_in_subtree(node->left_child, value)) return true;
        return contains_in_subtree(node->right_sibling, value);
    }

    static int max_leq_in_subtree(const RpNode* node, int x, int best) {
        if (!node) return best;
        if (node->value <= x && node->value > best)
            best = node->value;
        int left_best = max_leq_in_subtree(node->left_child, x, best);
        return max_leq_in_subtree(node->right_sibling, x, left_best);
    }

    static int min_geq_in_subtree(const RpNode* node, int x, int best) {
        if (!node) return best;
        if (node->value >= x && node->value < best)
            best = node->value;
        int left_best = min_geq_in_subtree(node->left_child, x, best);
        return min_geq_in_subtree(node->right_sibling, x, left_best);
    }

    static void collect_in_range(const RpNode* node, int x, int y, vector<int>& result) {
        if (!node) return;
        if (node->value >= x && node->value <= y)
            result.push_back(node->value);
        collect_in_range(node->left_child, x, y, result);
        collect_in_range(node->right_sibling, x, y, result);
    }
};