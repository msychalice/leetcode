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
    vector<vector<int>> criticalConnections(int n,
                                            vector<vector<int>>& connections) {
        /*
        // Time limit exceeded
        vector<unordered_set<int>> adjSet(n);
        for (auto& e : connections) {
            adjSet[e[0]].insert(e[1]);
            adjSet[e[1]].insert(e[0]);
        }

        function<bool(int, int, unordered_set<int>&)> dfs =
            [&](int src, int dst, unordered_set<int>& visited) {
                //          cout << "dfs " << src << "," << dst << endl;
                bool found = false;
                for (auto adjNode : adjSet[src]) {
                    if (adjNode == dst) {
                        //                 cout << "found " << endl;
                        return true;
                    }

                    if (visited.count(adjNode)) {
                        continue;
                    }

                    visited.insert(adjNode);
                    found = dfs(adjNode, dst, visited);
                    visited.erase(adjNode);
                    if (found) {
                        break;
                    }
                }

                return found;
            };

        vector<vector<int>> ans;
        // for each edge e(v1, v2),
        // if there is another path that can connect v1 and v2 other than
        // e(v1,v2), it is not a critical connection, otherwise it is.
        for (auto& e : connections) {
            int src = e[0];
            int dst = e[1];
            //      cout << "connection " << src << "," << dst << endl;

            // remove the edge
            adjSet[src].erase(dst);
            adjSet[dst].erase(src);

            unordered_set<int> visited;
            visited.insert(src);
            if (!dfs(src, dst, visited)) {
                //           cout << "critical " << endl;
                ans.push_back({src, dst});
            }

            // restore the edge
            adjSet[src].insert(dst);
            adjSet[dst].insert(src);
        }

        return ans;
        */

        vector<vector<int>> adjList(n);
        for (auto& e : connections) {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
        }

        int time = 0;
        vector<int> disc(n, -1);
        vector<int> parent(n, -1);
        vector<int> low(n, -1);
        vector<vector<int>> ans;

        function<void(int)> dfs = [&](int curNode) {
            if (disc[curNode] != -1) {
                return;
            }

            disc[curNode] = low[curNode] = time++;

            for (auto adjNode : adjList[curNode]) {
                if (disc[adjNode] == -1) {
                    // not visited
                    parent[adjNode] = curNode;
                    dfs(adjNode);
                    low[curNode] = min(low[curNode], low[adjNode]);

                    if (low[adjNode] > disc[curNode]) {
                        // found a critical connection / bridge edge
                        ans.push_back({curNode, adjNode});
                    }
                } else if (disc[adjNode] != -1 && adjNode != parent[curNode]) {
                    // found a back edge
                    low[curNode] = min(low[curNode], disc[adjNode]);
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (disc[i] != -1) {
                continue;
            }

            dfs(i);
        }

        return ans;
    }
};

int main() {
    Solution s;
    /*
     */
    vector<vector<int>> input{{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    print2DimVec(s.criticalConnections(4, input));
    vector<vector<int>> input1{{1, 0}, {2, 0}, {3, 2}, {4, 2},
                               {4, 3}, {3, 0}, {4, 0}};
    print2DimVec(s.criticalConnections(5, input1));
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
