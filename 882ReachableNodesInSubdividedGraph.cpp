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
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        vector<unordered_map<int, int>> adjMap(N);
        for (auto& e : edges) {
            adjMap[e[0]][e[1]] = e[2];
            adjMap[e[1]][e[0]] = e[2];
        }

        /*
        // BFS
        queue<pair<int, int>> que;        // pair(vertex, leftSteps)
        unordered_map<int, int> visited;  // map(vertex, leftSteps)
        que.push({0, M});
        visited[0] = M;

        while (!que.empty()) {
            int curVertex = que.front().first;
            int curVertexLeftSteps = que.front().second;
            que.pop();

            if (visited.count(curVertex) &&
                curVertexLeftSteps < visited[curVertex]) {
                continue;
            }

            for (auto& e : adjMap[curVertex]) {
                int nextVertex = e.first;
                int nextVertexLeftSteps = curVertexLeftSteps - e.second - 1;

                if (nextVertexLeftSteps >= 0) {  // nextVertex is reachable
                    if (visited.count(nextVertex)) {
                        visited[nextVertex] =
                            max(visited[nextVertex], nextVertexLeftSteps);
                    } else {
                        visited[nextVertex] = nextVertexLeftSteps;
                    }
                    que.push({nextVertex, nextVertexLeftSteps});
                } else {
                    // empty
                }
            }
        }

        int ans = visited.size();  // the reachable nodes in original graph
        for (auto& e : edges) {
            int v1 = e[0];
            int v2 = e[1];
            int w = e[2];
            int fromV1 = visited.count(v1) ? visited[v1] : 0;
            int fromV2 = visited.count(v2) ? visited[v2] : 0;
            ans += min(w, fromV1 + fromV2);
        }

        return ans;
        */

        // Dijkstra
        // pair(vertex, leftSteps)
        // if we define pair as (leftSteps, vertex), we can spare defining the
        // compare function
        using LessFunc =
            function<bool(const pair<int, int>&, const pair<int, int>&)>;
        LessFunc lessFunc = [](const pair<int, int>& p1,
                               const pair<int, int>& p2) {
            return p1.second < p2.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, LessFunc> que(
            lessFunc);
        unordered_map<int, int> visited;     // map(vertex, leftSteps)
        que.push({0, M});

        while (!que.empty()) {
            auto [curVertex, curVertexLeftSteps] = que.top();
            que.pop();

            if (visited.count(curVertex)) {
                continue;
            }

            visited[curVertex] = curVertexLeftSteps;

            for (auto& e : adjMap[curVertex]) {
                int nextVertex = e.first;
                int nextVertexLeftSteps = curVertexLeftSteps - e.second - 1;

                // nextVertex is not reachable or is visited
                if (nextVertexLeftSteps < 0 || visited.count(nextVertex)) {
                    continue;
                }

                que.push({nextVertex, nextVertexLeftSteps});
            }
        }

        int ans = visited.size();  // the reachable nodes in original graph
        for (auto& e : edges) {
            int v1 = e[0];
            int v2 = e[1];
            int w = e[2];
            int fromV1 = visited.count(v1) ? visited[v1] : 0;
            int fromV2 = visited.count(v2) ? visited[v2] : 0;
            ans += min(w, fromV1 + fromV2);
        }

        return ans;
    }
};

int main() {
    Solution s;
    /*
     */
    vector<vector<int>> input{{0, 1, 10}, {0, 2, 1}, {1, 2, 2}};
    cout << s.reachableNodes(input, 6, 3) << endl;
    vector<vector<int>> input1{{0, 1, 4}, {1, 2, 6}, {0, 2, 8}, {1, 3, 1}};
    cout << s.reachableNodes(input1, 10, 4) << endl;
    vector<vector<int>> input2{{0, 3, 8}, {0, 1, 4}, {2, 4, 3}, {1, 2, 0},
                               {1, 3, 9}, {0, 4, 7}, {3, 4, 9}, {1, 4, 4},
                               {0, 2, 7}, {2, 3, 1}};
    cout << s.reachableNodes(input2, 8, 5) << endl;
    vector<vector<int>> input3{
        {4, 6, 11}, {5, 6, 2}, {2, 6, 11}, {0, 3, 19}, {1, 7, 21},
        {5, 7, 1},  {1, 5, 4}, {0, 7, 12}, {6, 7, 3},  {3, 6, 22},
        {0, 5, 24}, {1, 2, 8}, {3, 7, 11}, {1, 3, 14}, {4, 5, 7},
        {4, 7, 14}, {0, 4, 5}, {2, 4, 7},  {3, 4, 11}, {3, 5, 15},
        {2, 5, 13}, {2, 3, 6}, {1, 4, 6},  {0, 2, 3},  {1, 6, 20}};
    cout << s.reachableNodes(input3, 18, 8) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
