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
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int row = matrix.size();
        int col = matrix[0].size();
        // return how many numbers are less or equal to target in matrix
        function<int(int)> lessOrEqual = [&](int target) {
            int i = row - 1;
            int j = 0;
            int cnt = 0;
            // starting from bottom left corner
            while (i >= 0 && j < col) {
                if (matrix[i][j] <= target) {
                    // add the whole column from 0 to i
                    for (int n = 0; n <= i; n++) {
                        cnt++;
                    }
                    j++;
                } else {
                    i--;
                }
            }

            return cnt;
        };

        // binary search on the sorted matrix
        int lo = matrix[0][0];
        int hi = matrix[row - 1][col - 1] + 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int count = lessOrEqual(mid);
            if (count < k) {
                lo = mid + 1;
            } else if (count > k) {
                hi = mid;
            } else {
                lo = mid;
                break;
            }
        }

        vector<int> ans;
        // there are AT LEAST k numbers are less or equal to lo
        int i = row - 1;
        int j = 0;
        // starting from bottom left corner
        while (i >= 0 && j < col) {
            if (matrix[i][j] <= lo) {
                // add the whole column from 0 to i
                for (int n = 0; n <= i; n++) {
                    ans.push_back(matrix[i][j]);
                }
                j++;
            } else {
                i--;
            }
        }

        // sort ans and return ans[k-1]
        sort(ans.begin(), ans.end());
        return ans[k - 1];
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
