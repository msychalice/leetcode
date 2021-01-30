#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
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

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> output;
        vector<int> curPath;  // column indices for each row
        vector<int> curChoices;  // column index choices
        for (int i = 0; i < n; i++) {
            curChoices.push_back(i);
        }

        function<void()> backtrack = [&]() {
            if (curChoices.size() == 0) {
                vector<string> solution;
                for (int i = 0; i < n; i++) {
                    string row(n, '.');
                    row[curPath[i]] = 'Q';
                    solution.emplace_back(move(row));
                }
                output.emplace_back(move(solution));

                return;
            }

            for (int i = 0; i < curChoices.size(); i++) {
                int selectedCol = curChoices[i];
                bool inSameDiagonal = false;
                // check if there are queens in the same diagonal
                for (int j = 0; j < curPath.size(); j++) {
                    if (abs(selectedCol - curPath[j]) == curPath.size() - j) {
                        inSameDiagonal = true;
                        break;
                    }
                }

                if (inSameDiagonal) {
                    continue;
                }

                curPath.push_back(selectedCol);
                curChoices.erase(curChoices.begin() + i);
                backtrack();
                curChoices.insert(curChoices.begin() + i, selectedCol);
                curPath.pop_back();
            }
        };

        backtrack();

        return output;
    }
};

int main() {
    Solution s;

    auto output = s.solveNQueens(4);

    auto output1 = s.solveNQueens(1);

    cout << "*************output*************" << endl;
    print2DimVec(output);
    print2DimVec(output1);

    return 0;
}
