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
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges,
                                         vector<vector<int>>& blue_edges) {
        // 1 <= n <= 100 use vector to build adjacency list
        vector<vector<int>> adjListRed(n);
        vector<vector<int>> adjListBlue(n);
        for (auto& e : red_edges) {
            adjListRed[e[0]].push_back(e[1]);
        }
        for (auto& e : blue_edges) {
            adjListBlue[e[0]].push_back(e[1]);
        }

        queue<int> redNeighbors;
        queue<int> blueNeighbors;
        vector<bool> visitedRed(n);
        vector<bool> visitedBlue(n);
        redNeighbors.push(0);
        blueNeighbors.push(0);
        visitedRed[0] = true;
        visitedBlue[0] = true;

        vector<int> res(n, -1);
        res[0] = 0;

        int steps = 0;

        while (!redNeighbors.empty() || !blueNeighbors.empty()) {
            int queSizeRed = redNeighbors.size();
            int queSizeBlue = blueNeighbors.size();

            steps++;

            while (queSizeRed--) {
                int curVertex = redNeighbors.front();
                redNeighbors.pop();

                // find it's blue neighbors that are connected by blue edges
                for (auto& blueNeighbor : adjListBlue[curVertex]) {
                    if (visitedBlue[blueNeighbor]) {
                        continue;
                    }

                    visitedBlue[blueNeighbor] = true;

                    res[blueNeighbor] = res[blueNeighbor] == -1
                                            ? steps
                                            : min(steps, res[blueNeighbor]);

                    // add it into blue queue
                    blueNeighbors.push(blueNeighbor);
                }
            }

            while (queSizeBlue--) {
                int curVertex = blueNeighbors.front();
                blueNeighbors.pop();

                // find it's red neighbors that are connected by red edges
                for (auto& redNeighbor : adjListRed[curVertex]) {
                    if (visitedRed[redNeighbor]) {
                        continue;
                    }

                    visitedRed[redNeighbor] = true;

                    res[redNeighbor] = res[redNeighbor] == -1
                                           ? steps
                                           : min(steps, res[redNeighbor]);

                    // add it into red queue
                    redNeighbors.push(redNeighbor);
                }
            }
        }

        return res;
    }
};

int main() {
    Solution s;
    /*
     */
    vector<vector<int>> input{{0, 1}, {1, 2}};
    vector<vector<int>> input1{};
    printContainer(s.shortestAlternatingPaths(3, input, input1));
    vector<vector<int>> input2{{0, 1}};
    vector<vector<int>> input3{{2, 1}};
    printContainer(s.shortestAlternatingPaths(3, input2, input3));
    vector<vector<int>> input4{{1, 0}};
    vector<vector<int>> input5{{2, 1}};
    printContainer(s.shortestAlternatingPaths(3, input4, input5));
    vector<vector<int>> input6{{0, 1}};
    vector<vector<int>> input7{{1, 2}};
    printContainer(s.shortestAlternatingPaths(3, input6, input7));
    vector<vector<int>> input8{{0, 1}, {0, 2}};
    vector<vector<int>> input9{{1, 0}};
    printContainer(s.shortestAlternatingPaths(3, input8, input9));
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
