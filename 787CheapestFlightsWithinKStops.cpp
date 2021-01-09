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
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst,
                          int K) {
        vector<vector<pair<int, int>>> adjList(n);
        for (auto& e : flights) {
            adjList[e[0]].push_back(make_pair(e[1], e[2]));
        }

        /*
        // DFS
        vector<bool> visited(n);
        visited[src] = true;
        int res = numeric_limits<int>::max();

        function<void(int, int, int)> dfs = [&](int cur, int cost, int k) {
            if (cur == dst) {
                res = cost;
                return;
            }

            if (k == 0) {
                return;
            }

            for (auto& p : adjList[cur]) {
                if (visited[p.first]) {
                    continue;
                }
                if (cost + p.second > res) {
                    // important pruning
                    continue;
                }

                visited[p.first] = true;
                dfs(p.first, cost + p.second, k - 1);
                visited[p.first] = false;
            }
        };

        dfs(src, 0, K + 1);

        return res == numeric_limits<int>::max() ? -1 : res;
        */

        /*
        // BFS
        queue<pair<int, int>> que;  // pair(vertex, cost)
        que.push(make_pair(src, 0));
        int steps = 0;
        int res = numeric_limits<int>::max();

        while (!que.empty()) {
            int queSize = que.size();
            while (queSize--) {
                auto [curVertex, curCost] = que.front();
                que.pop();

                for (auto& p : adjList[curVertex]) {
                    int nextVertex = p.first;
                    int nextVertexWeight = p.second;
                    if (curCost + nextVertexWeight > res) {
                        // important pruning
                        continue;
                    }
                    if (nextVertex == dst) {
                        res = curCost + nextVertexWeight;
                        continue;
                    }

                    que.push(make_pair(nextVertex, curCost + nextVertexWeight));
                }
            }

            if (steps++ == K) {
                break;
            }
        }

        return res == numeric_limits<int>::max() ? -1 : res;
        */

        // Bellman-Ford
        // dp[k][v] represents the minimum cost from src to v within k steps
        vector<vector<int>> dp(2, vector<int>(n, numeric_limits<int>::max()));
        // base case
        // dp[0...K+1][src] = 0
        for (int i = 0; i < 2; i++) {
            dp[i][src] = 0;
        }

        for (int i = 1; i <= K + 1; i++) {
            for (auto& e : flights) {
                int from = e[0];
                int to = e[1];
                int weight = e[2];

                if (dp[(i - 1) % 2][from] != numeric_limits<int>::max()) {
                    dp[i % 2][to] =
                        min(dp[i % 2][to], min(dp[(i - 1) % 2][to],
                                               dp[(i - 1) % 2][from] + weight));
                }
            }
        }

        return dp[(K + 1) % 2][dst] == numeric_limits<int>::max()
                   ? -1
                   : dp[(K + 1) % 2][dst];
    }
};

int main() {
    Solution s;
    /*
     */
    vector<vector<int>> input{{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    cout << s.findCheapestPrice(3, input, 0, 2, 1) << endl;
    vector<vector<int>> input1{{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    cout << s.findCheapestPrice(3, input1, 0, 2, 0) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
