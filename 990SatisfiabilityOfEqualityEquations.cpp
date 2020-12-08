#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

template<class Container>
void printContainer(const Container& container) {
//    return;

    if (container.size() == 0) {
        cout << "[]" << endl;
        return;
    }

    for (auto it = container.begin(); it != container.end(); it++) {
        if (it == container.begin()) {
            cout << "[";
        }
        cout << *it;
        if (it == prev(container.end())) {
            cout << "]" << endl;
        } else {
            cout << ", ";
        }
    }
}

template<class T>
void print2DimVec(const vector<vector<T>>& container) {
//    return;

    if (container.size() == 0) {
        cout << "[]" << endl;
        return;
    }

    for (auto it = container.begin(); it != container.end(); it++) {
        if (it == container.begin()) {
            cout << "[" << endl;
        }
        printContainer(*it);
        if (it == prev(container.end())) {
            cout << "]" << endl;
        }
    }
}

template<class T>
void printMap(const T& container) {
//    return;

    cout << "size " << container.size() << endl;
    if (container.size() == 0) {
        cout << "[]" << endl;
        return;
    }
    for (auto it = container.begin(); it != container.end(); it++) {
        if (it == container.begin()) {
            cout << "[ ";
        }

        cout << "[" << it->first << ", " << it->second << "]";

        if (next(it) == container.end()) {
            cout << " ]" << endl;
        } else {
            cout << ", ";
        }
    }
}

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

void printList(const ListNode* node) {
    while (node != nullptr) {
        cout << node->val;

        node = node->next;
        
        if (node != nullptr) {
            cout << "->";
        } else {
            cout << endl;
        }
    }
}

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

void printTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->val << endl;
    printTree(root->left);
    printTree(root->right);
}

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
    class UnionFind {
    public:
        UnionFind(int size) : m_size(size), m_root(size + 1, -1) {}

        void unionNodes(int a, int b) {
            int aRoot = findRoot(a);
            int bRoot = findRoot(b);
            if (aRoot == bRoot) {
                return;
            }

            // merge the set having less nodes into the set having more nodes
            int newRoot, mergedRoot = -1;
            if (abs(m_root[aRoot]) > abs(m_root[bRoot])) {
                newRoot = aRoot;
                mergedRoot = bRoot;
            } else {
                newRoot = bRoot;
                mergedRoot = aRoot;
            }

            m_root[newRoot] -= abs(m_root[mergedRoot]);
            m_root[mergedRoot] = newRoot;
        }

        bool isConnected(int a, int b) {
            return findRoot(a) == findRoot(b);
        }

    private:
        int findRoot(int node) {
            if (m_root[node] < 0) {
                // it's a root node, return itself
                return node;
            }

            int root = findRoot(m_root[node]);
            m_root[node] = root;  // update root, path compression
            return root;
        }

        // 1 <= i <= m_size
        // m_root[i] = -1 initially
        // m_root[i] < 0 means node i is a root node,
        // node count of this set is abs(m_root[i])
        // m_root[i] > 0 means m_root[i] is the root of i
        vector<int> m_root;
        int m_size;
    };

public:
    bool equationsPossible(vector<string>& equations) {
        UnionFind uf(26);
        // check == equations first, UF
        for (auto& e : equations) {
            if (e[1] == '!') {
                continue;
            }

            uf.unionNodes(e[0] - 'a', e[3] - 'a');
        }

        // check != equations later, see if it breaks the current unions or not
        for (auto& e : equations) {
            if (e[1] == '=') {
                continue;
            }

            if (uf.isConnected(e[0] - 'a', e[3] - 'a')) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<string> input{"a==b", "b!=a"};
    cout << s.equationsPossible(input) << endl;

    vector<string> input1{"b==a", "a==b"};
    cout << s.equationsPossible(input1) << endl;

    vector<string> input2{"a==b", "b==c", "a==c"};
    cout << s.equationsPossible(input2) << endl;

    vector<string> input3{"a==b", "b!=c", "c==a"};
    cout << s.equationsPossible(input3) << endl;

    vector<string> input4{"c==c", "b==d", "x!=z"};
    cout << s.equationsPossible(input4) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
