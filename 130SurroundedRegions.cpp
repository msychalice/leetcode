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
    void solve(vector<vector<char>>& board) {
        int rowSize = board.size();
        if (rowSize == 0) {
            return;
        }
        int colSize = board[0].size();
        if (colSize == 0) {
            return;
        }

        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false));

        function<void(int, int)> checkLinkedGrid =
            [&checkLinkedGrid, &board, &visited, &rowSize, &colSize](int row,
                                                                     int col) {
                if (row < 0 || col < 0 || row >= rowSize || col >= colSize) {
                    return;
                }
                char curGrid = board[row][col];
                if (curGrid == 'X') {
                    return;
                }

                if (visited[row][col]) {
                    return;
                }

                visited[row][col] = true;

                checkLinkedGrid(row, col + 1);
                checkLinkedGrid(row, col - 1);
                checkLinkedGrid(row + 1, col);
                checkLinkedGrid(row - 1, col);
            };

        // check all grids at border
        for (int row = 0; row < rowSize; row++) {
            // first col
            char curGrid = board[row][0];
            if (curGrid == 'O') {
                checkLinkedGrid(row, 0);
            }

            // last col
            curGrid = board[row][colSize - 1];
            if (curGrid == 'O') {
                checkLinkedGrid(row, colSize - 1);
            }
        }
        for (int col = 0; col < board[0].size(); col++) {
            // first row
            char curGrid = board[0][col];
            if (curGrid == 'O') {
                checkLinkedGrid(0, col);
            }

            // last row
            curGrid = board[rowSize - 1][col];
            if (curGrid == 'O') {
                checkLinkedGrid(rowSize - 1, col);
            }
        }

        // change all the unvisited 'O', which is not linked to any 'O' at
        // border, to 'X'
        for (int row = 0; row < board.size(); row++) {
            for (int col = 0; col < board[0].size(); col++) {
                if (!visited[row][col] && board[row][col] == 'O') {
                    board[row][col] = 'X';
                }
            }
        }
    }
};

int main() {
    Solution s;

    vector<vector<char>> input{
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'},
    };
    s.solve(input);

    cout << "*************output*************" << endl;

    print2DimVec(input);

    return 0;
}
