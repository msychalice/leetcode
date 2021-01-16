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
        vector<int> visited(n, numeric_limits<int>::max());
        visited[src] = 0;

        while (!que.empty()) {
            int queSize = que.size();
            while (queSize--) {
                auto [curVertex, curCost] = que.front();
                que.pop();


                for (auto& p : adjList[curVertex]) {
                    int nextVertex = p.first;
                    int nextVertexWeight = p.second;

                    // alternative pruning
                    // if (curCost + nextVertexWeight > res) {
                    //    // important pruning
                    //    continue;
                    // }
                    if (curCost + nextVertexWeight > visited[nextVertex]) {
                        continue;
                    }
                    visited[nextVertex] = curCost + nextVertexWeight;

                    if (nextVertex == dst) {
                        res = min(res, curCost + nextVertexWeight);
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

        /*
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
        */

        // Dijkstra
        struct Node {
            int vertex;
            int cost;
            int steps;
        };

        using GreaterFunc = function<bool(const Node&, const Node&)>;
        GreaterFunc greaterFunc = [](const Node& n1, const Node& n2) {
            return n1.cost > n2.cost;
        };

        if (src == dst) {
            return 0;
        }

        priority_queue<Node, vector<Node>, GreaterFunc> que(greaterFunc);
        int res = numeric_limits<int>::max();

        // minimum cost for (vertex, steps)
        // cannot use a 1D array for each vertex like the one used in the above
        // BFS approach.
        // because a smaller cost path may have larger steps which
        // might exceed the K+1 limit.
        vector<vector<int>> visited(
            n, vector<int>(K + 2, numeric_limits<int>::max()));

        que.push(Node{src, 0, 0});
        visited[src][0] = 0;
        while (!que.empty()) {
            auto [curVertex, curCost, curSteps] = que.top();
            que.pop();

            // Alternative pruning which is slower than current one.
            // When the final answer is found very late, the pruning will also
            // take effect very late.
            // if (curCost > res) {
            //    continue;
            // }

            for (auto& e : adjList[curVertex]) {
                int nextVertex = e.first;
                int nextVertexCost = e.second + curCost;
                int nextVertexSteps = curSteps + 1;

                if (nextVertex == dst) {
                    res = min(res, nextVertexCost);
                    continue;
                }
                if (nextVertexSteps == K + 1) {
                    continue;
                }
                if (nextVertexCost > visited[nextVertex][nextVertexSteps]) {
                    continue;
                }
                visited[nextVertex][nextVertexSteps] = nextVertexCost;

                que.push(Node{nextVertex, nextVertexCost, nextVertexSteps});
            }
        }

        return res == numeric_limits<int>::max() ? -1 : res;
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
    vector<vector<int>> input2{
        {0, 12, 28},  {5, 6, 39},    {8, 6, 59},   {13, 15, 7},  {13, 12, 38},
        {10, 12, 35}, {15, 3, 23},   {7, 11, 26},  {9, 4, 65},   {10, 2, 38},
        {4, 7, 7},    {14, 15, 31},  {2, 12, 44},  {8, 10, 34},  {13, 6, 29},
        {5, 14, 89},  {11, 16, 13},  {7, 3, 46},   {10, 15, 19}, {12, 4, 58},
        {13, 16, 11}, {16, 4, 76},   {2, 0, 12},   {15, 0, 22},  {16, 12, 13},
        {7, 1, 29},   {7, 14, 100},  {16, 1, 14},  {9, 6, 74},   {11, 1, 73},
        {2, 11, 60},  {10, 11, 85},  {2, 5, 49},   {3, 4, 17},   {4, 9, 77},
        {16, 3, 47},  {15, 6, 78},   {14, 1, 90},  {10, 5, 95},  {1, 11, 30},
        {11, 0, 37},  {10, 4, 86},   {0, 8, 57},   {6, 14, 68},  {16, 8, 3},
        {13, 0, 65},  {2, 13, 6},    {5, 13, 5},   {8, 11, 31},  {6, 10, 20},
        {6, 2, 33},   {9, 1, 3},     {14, 9, 58},  {12, 3, 19},  {11, 2, 74},
        {12, 14, 48}, {16, 11, 100}, {3, 12, 38},  {12, 13, 77}, {10, 9, 99},
        {15, 13, 98}, {15, 12, 71},  {1, 4, 28},   {7, 0, 83},   {3, 5, 100},
        {8, 9, 14},   {15, 11, 57},  {3, 6, 65},   {1, 3, 45},   {14, 7, 74},
        {2, 10, 39},  {4, 8, 73},    {13, 5, 77},  {10, 0, 43},  {12, 9, 92},
        {8, 2, 26},   {1, 7, 7},     {9, 12, 10},  {13, 11, 64}, {8, 13, 80},
        {6, 12, 74},  {9, 7, 35},    {0, 15, 48},  {3, 7, 87},   {16, 9, 42},
        {5, 16, 64},  {4, 5, 65},    {15, 14, 70}, {12, 0, 13},  {16, 14, 52},
        {3, 10, 80},  {14, 11, 85},  {15, 2, 77},  {4, 11, 19},  {2, 7, 49},
        {10, 7, 78},  {14, 6, 84},   {13, 7, 50},  {11, 6, 75},  {5, 10, 46},
        {13, 8, 43},  {9, 10, 49},   {7, 12, 64},  {0, 10, 76},  {5, 9, 77},
        {8, 3, 28},   {11, 9, 28},   {12, 16, 87}, {12, 6, 24},  {9, 15, 94},
        {5, 7, 77},   {4, 10, 18},   {7, 2, 11},   {9, 5, 41}};
    cout << s.findCheapestPrice(17, input2, 13, 4, 13) << endl;
    vector<vector<int>> input3{{0, 3, 3},   {3, 4, 3},  {4, 1, 3},   {0, 5, 1},
                               {5, 1, 100}, {0, 6, 2},  {6, 1, 100}, {0, 7, 1},
                               {7, 8, 1},   {8, 9, 1},  {9, 1, 1},   {1, 10, 1},
                               {10, 2, 1},  {1, 2, 100}};
    cout << s.findCheapestPrice(11, input3, 0, 2, 4) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
