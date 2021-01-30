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
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.size() == 0) {
            return {};
        }

        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<bool>> canReachP(row, vector<bool>(col));
        vector<vector<bool>> canReachA(row, vector<bool>(col));

        function<void(int, int, int, vector<vector<bool>>&)> dfs =
            [&](int x, int y, int prevH, vector<vector<bool>>& v) {
                // invalid grid
                if (x < 0 || y < 0 || x >= row || y >= col) {
                    return;
                }

                int curH = matrix[x][y];
                // visited or it's height is smaller than the previous grid
                if (v[x][y] || curH < prevH) {
                    return;
                }

                v[x][y] = true;

                dfs(x, y + 1, curH, v);
                dfs(x + 1, y, curH, v);
                dfs(x, y - 1, curH, v);
                dfs(x - 1, y, curH, v);
            };

        for (int i = 0; i < row; i++) {
            // origin grid in at left edge
            dfs(i, 0, -1, canReachP);
            // origin grid in at right edge
            dfs(i, col - 1, -1, canReachA);
        }
        for (int i = 0; i < col; i++) {
            // origin grid in at top edge
            dfs(0, i, -1, canReachP);
            // origin grid in at bottom edge
            dfs(row - 1, i, -1, canReachA);
        }

        vector<vector<int>> ans;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (canReachA[i][j] && canReachP[i][j]) {
                    ans.push_back({i, j});
                }
            }
        }

        return ans;
    }
};

int main() {
    Solution s;
    /*
     */
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
