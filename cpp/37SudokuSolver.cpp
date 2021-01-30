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
    void solveSudoku(vector<vector<char>>& board) {
        int boardSize = board.size();
        int gridSize = boardSize / 3;

        vector<unordered_set<char>> vecSubboards(boardSize);
        vector<unordered_set<char>> vecColumns(boardSize);
        vector<unordered_set<char>> vecRows(boardSize);

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                char c = board[i][j];
                if (c == '.') {
                    continue;
                }
                vecRows[i].insert(c);
                vecColumns[j].insert(c);
                int subboardIndex = (j / 3) * 3 + i / 3;
                vecSubboards[subboardIndex].insert(c);
            }
        }

        function<bool(int)> backtrack = [&](int gridIndex) {
            if (gridIndex == boardSize * boardSize) {
                return true;
            }

            int rowIndex = gridIndex / boardSize;
            int colIndex = gridIndex % boardSize;
            // find the next empty grid
            while (board[rowIndex][colIndex] != '.') {
                gridIndex++;
                if (gridIndex == boardSize * boardSize) {
                    return true;
                }

                rowIndex = gridIndex / boardSize;
                colIndex = gridIndex % boardSize;
            }
            int subboardIndex = (colIndex / 3) * 3 + rowIndex / 3;

            // check grid
            for (char c = '1'; c <= '9'; c++) {
                // c doesn't appear in the current row, column and subboard
                if (vecSubboards[subboardIndex].count(c) == 0 &&
                    vecRows[rowIndex].count(c) == 0 &&
                    vecColumns[colIndex].count(c) == 0) {
                    // select c and continue backtracking
                    vecSubboards[subboardIndex].insert(c);
                    vecRows[rowIndex].insert(c);
                    vecColumns[colIndex].insert(c);
                    board[rowIndex][colIndex] = c;
                    bool result = backtrack(gridIndex + 1);
                    if (result) {
                        return true;
                    } else {
                        // unselect c and continue the for loop
                        board[rowIndex][colIndex] = '.';
                        vecSubboards[subboardIndex].erase(c);
                        vecRows[rowIndex].erase(c);
                        vecColumns[colIndex].erase(c);
                    }
                }
            }

            return false;
        };

        backtrack(0);
    }
};

int main() {

    cout << "*************output*************" << endl;

    return 0;
}
