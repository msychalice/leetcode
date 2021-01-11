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
    int shortestPathAllKeys(vector<string>& grid) {
        struct Node {
            int x;
            int y;
            int acquiredkeys;  // compressed by bit operation
            int moves;         // current moves
            void acquireKey(char key) {
                acquiredkeys |= 1 << (key - 'a');
            }
            bool isKeyAcquired(int key) const {
                return acquiredkeys & (1 << key);
            }
        };

        int srcX = 0;
        int srcY = 0;
        Node dstNode{0, 0, 0, 0};  // leverage the Node::acquireKey method
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '@') {
                    srcX = i;
                    srcY = j;
                }
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                    dstNode.acquireKey(grid[i][j]);
                }
            }
        }

        queue<Node> que;
        // unordered_set contains all the visited node states
        vector<vector<unordered_set<int>>> visited(
            grid.size(), vector<unordered_set<int>>(grid[0].size()));
        que.push(Node{srcX, srcY, 0, 0});
        visited[srcX][srcY].insert(0);
        int moves = 0;
        static const vector<pair<int, int>> directions{
            {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        while (!que.empty()) {
            int queSize = que.size();
            moves++;
            while (queSize--) {
                Node curNode = que.front();
                que.pop();

                for (auto& dir : directions) {
                    int adjNodeX = curNode.x + dir.first;
                    int adjNodeY = curNode.y + dir.second;
                    if (adjNodeX < 0 || adjNodeY < 0 ||
                        adjNodeX >= grid.size() || adjNodeY >= grid[0].size()) {
                        continue;
                    }
                    char adjNodeChar = grid[adjNodeX][adjNodeY];
                    if (adjNodeChar == '#') {  // wall
                        continue;
                    }
                    if (adjNodeChar >= 'A' && adjNodeChar <= 'F' &&
                        !curNode.isKeyAcquired(adjNodeChar -
                                               'A')) {  // unlocked lock
                        continue;
                    }

                    Node adjNode{adjNodeX, adjNodeY, curNode.acquiredkeys,
                                 curNode.moves + 1};
                    if (adjNodeChar >= 'a' && adjNodeChar <= 'f') {  // key
                        adjNode.acquireKey(adjNodeChar);
                    }

                    // all keys are acquired
                    if (adjNode.acquiredkeys == dstNode.acquiredkeys) {
                        return moves;
                    }

                    // adjNode with these acquired keys is already visited
                    // we don't need to check the moves,
                    // since BFS guarantees the least moves node state will be
                    // reached first
                    if (visited[adjNodeX][adjNodeY].count(
                            adjNode.acquiredkeys)) {
                        continue;
                    }

                    que.push(adjNode);
                    visited[adjNodeX][adjNodeY].insert(adjNode.acquiredkeys);
                }
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    /*
     */
    vector<string> input{"@.a.#", "###.#", "b.A.B"};
    cout << s.shortestPathAllKeys(input) << endl;
    vector<string> input1{"@..aA", "..B#.", "....b"};
    cout << s.shortestPathAllKeys(input1) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
