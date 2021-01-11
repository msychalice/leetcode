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
#include <tuple>
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
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        auto bfs = [&](int src) {
            // tuple(node, coveredNodes, pathLen)
            // since N is less than 12,
            // coveredNodes can be compressed in an int by bit operations
            queue<tuple<int, int, int>> que;
            vector<unordered_set<int>> visited(graph.size());
            que.push({src, 1 << src, 0});
            visited[src].insert(1 << src);

            while (!que.empty()) {
                auto [curNode, curCoveredNodes, curPathLen] = que.front();
                que.pop();

                for (auto& adjNode : graph[curNode]) {
                    int nextCoveredNodes = curCoveredNodes | 1 << adjNode;

                    // all nodes are covered
                    if (nextCoveredNodes == (1 << graph.size()) - 1) {
                        return curPathLen + 1;
                    }

                    if (visited[adjNode].count(nextCoveredNodes)) {
                        continue;
                    }

                    visited[adjNode].insert(nextCoveredNodes);
                    que.push({adjNode, nextCoveredNodes, curPathLen + 1});
                }
            }
            return 0;
        };

        int ans = numeric_limits<int>::max();
        for (int i = 0; i < graph.size(); i++) {
            ans = min(ans, bfs(i));
        }
        return ans;
    }
};

int main() {
    Solution s;
    /*
     */
    vector<vector<int>> input{{1, 2, 3}, {0}, {0}, {0}};
    cout << s.shortestPathLength(input) << endl;
    vector<vector<int>> input1{
        {2, 3, 5, 7}, {2, 3, 7},        {0, 1}, {0, 1}, {7},   {0},
        {10},         {9, 10, 0, 1, 4}, {9},    {7, 8}, {7, 6}};
    cout << s.shortestPathLength(input1) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
