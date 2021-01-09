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
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<pair<int, int>>> adjList(N + 1);  // pair(vertex, weight)
        for (auto& e : times) {
            adjList[e[0]].push_back(make_pair(e[1], e[2]));
        }

        /*
        // Dijkstra
        vector<int> visited(N + 1, -1);  // weight is >=0 if it is visited
        using GreaterFunc =
            function<bool(const pair<int, int>&, const pair<int, int>&)>;
        GreaterFunc greaterFunc = [](const pair<int, int>& v1,
                                     const pair<int, int>& v2) {
            return v1.second > v2.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, GreaterFunc>
            queNeighbor(greaterFunc);

        queNeighbor.push(make_pair(K, 0));

        while (!queNeighbor.empty()) {
            auto [vertex, weight] = queNeighbor.top();
            queNeighbor.pop();

            if (visited[vertex] >= 0) {
                continue;
            }

            visited[vertex] = weight;

            for (auto& e : adjList[vertex]) {
                int nextVertex = e.first;
                int nextVertexCost = e.second;
                if (visited[nextVertex] >= 0) {
                    continue;
                }

                queNeighbor.push(
                    make_pair(nextVertex, weight + nextVertexCost));
            }
        }

        int reachableCount = 0;
        int res = 0;
        for (auto& v : visited) {
            if (v >= 0) {
                reachableCount++;
            }
            res = max(res, v);
        };

        return reachableCount == N ? res : -1;
        */

        // Bellman-Ford
        vector<int> dist(N + 1, numeric_limits<int>::max());
        dist[K] = 0;
        for (int i = 1; i < N; i++) {
            bool isChanged = false;
            for (auto& e : times) {
                int from = e[0];
                int to = e[1];
                int w = e[2];
                if (dist[from] != numeric_limits<int>::max()) {
                    dist[to] = min(dist[to], dist[from] + w);
                    isChanged = true;
                }
            }

            if (!isChanged) {
                break;
            }
        }
        // since all the cost are non-negative value,
        // don't check the N time for negative weight circle

        int res = 0;
        for (int i = 1; i <= N; i++) {
            res = max(res, dist[i]);
        }
        return res == numeric_limits<int>::max() ? -1 : res;
    }
};

int main() {
    Solution s;
    /*
     */
    vector<vector<int>> input{{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    cout << s.networkDelayTime(input, 4, 2) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
