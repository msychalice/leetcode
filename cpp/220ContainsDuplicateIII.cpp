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
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (nums.size() <= 1) {
            return false;
        }
        if (k == 0) {
            return false;
        }

        multiset<int> ms;

        // insert nums[1...k] into multiset
        for (int i = 1; i <= k; i++) {
            // k is possibly larger than nums.size()
            if (i >= nums.size()) {
                break;
            }

            ms.insert(nums[i]);
        }

        // important, have to check the number before the last one
        for (int i = 0; i < nums.size() - 1; i++) {
            // check duplicate
            auto it = ms.lower_bound(nums[i]);
            // important, can not set to int::max()
            int64_t minDiff = numeric_limits<int64_t>::max();

            if (it == ms.end()) {
                // all the numbers in the multiset are smaller than nums[i]
                int64_t curDiff =
                    static_cast<int64_t>(nums[i]) -
                    static_cast<int64_t>(*ms.rbegin());  // prevent overflow
                minDiff = min(minDiff, curDiff);
            } else {
                int64_t curDiff =
                    static_cast<int64_t>(*it) - static_cast<int64_t>(nums[i]);
                minDiff = min(minDiff, curDiff);

                if (it != ms.begin()) {
                    curDiff = static_cast<int64_t>(nums[i]) -
                              static_cast<int64_t>(*prev(it));
                    minDiff = min(minDiff, curDiff);
                }
            }

            if (minDiff <= static_cast<int64_t>(t)) {
                return true;
            }

            // slide the window
            if (i + ms.size() + 1 < nums.size()) {
                ms.insert(nums[i + ms.size() + 1]);
            }
            ms.erase(ms.find(nums[i + 1]));
        }

        return false;
    }
};

int main() {
    Solution s;
    /*
     */
    vector<int> input{1, 2, 3, 1};
    cout << s.containsNearbyAlmostDuplicate(input, 3, 0) << endl;
    vector<int> input1{1, 0, 1, 1};
    cout << s.containsNearbyAlmostDuplicate(input1, 1, 2) << endl;
    vector<int> input2{0};
    cout << s.containsNearbyAlmostDuplicate(input2, 0, 0) << endl;
    vector<int> input3{1, 2, 1, 1};
    cout << s.containsNearbyAlmostDuplicate(input3, 1, 0) << endl;
    vector<int> input4{1, 5, 9, 1, 5, 9};
    cout << s.containsNearbyAlmostDuplicate(input4, 2, 3) << endl;
    vector<int> input5{-2147483648, 2147483647};
    cout << s.containsNearbyAlmostDuplicate(input5, 1, 1) << endl;
    vector<int> input6{2147483647, -1, 2147483647};
    cout << s.containsNearbyAlmostDuplicate(input6, 1, 2147483647) << endl;
    vector<int> input7{7, 1, 3};
    cout << s.containsNearbyAlmostDuplicate(input7, 2, 3) << endl;

    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
