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
    int shipWithinDays(vector<int>& weights, int D) {
        int sumWeight = 0;
        int maxWeight = 0;
        for (auto w : weights) {
            sumWeight += w;
            maxWeight = max(maxWeight, w);
        }

        function<int(int)> getDays = [&weights](int weight) {
            int days = 0;
            int groupWeight = 0;  // total weight of a group of items
            for (int i = 0; i < weights.size(); i++) {
                groupWeight += weights[i];

                // call it a day
                if (groupWeight <= weight &&
                    (i == weights.size() - 1 ||
                     (groupWeight + weights[i + 1] > weight))) {
                    days++;
                    groupWeight = 0;
                }
            }
            return days;
        };

        // binary search at [maxWeight, sumWeight]
        int lo = maxWeight;
        int hi = sumWeight + 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;

            int days = getDays(mid);

            if (days <= D && (mid == maxWeight || getDays(mid - 1) > D)) {
                return mid;
            }

            if (days <= D) {  // move left to decrease weight
                hi = mid;
            } else {                 // move right
                lo = mid + 1;
            }
        }

        return 0;
    }
};

int main() {
    Solution s;

    vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << s.shipWithinDays(input, 5) << endl;

    vector<int> input1{3, 2, 2, 4, 1, 4};
    cout << s.shipWithinDays(input1, 3) << endl;

    vector<int> input2{1, 2, 3, 1, 1};
    cout << s.shipWithinDays(input2, 4) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
