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
    int maxProfit(vector<int>& prices) {
        // 1 <= i <= prices.size()
        // k is infinity

        int dp_i_in_cool_down = numeric_limits<int>::min();  // i = 0
        int dp_i_no_stock = 0;                               // i = 0
        int dp_i_has_stock = numeric_limits<int>::min();     // i = 0

        int dp_i_in_cool_down_pre = dp_i_in_cool_down;
        int dp_i_no_stock_pre = dp_i_no_stock;
        int dp_i_has_stock_pre = dp_i_has_stock;
        for (int i = 1; i <= prices.size(); i++) {
            dp_i_in_cool_down = dp_i_has_stock_pre + prices[i - 1];
            dp_i_no_stock = max(dp_i_no_stock_pre, dp_i_in_cool_down_pre);
            dp_i_has_stock =
                max(dp_i_has_stock_pre, dp_i_no_stock_pre - prices[i - 1]);

            dp_i_in_cool_down_pre = dp_i_in_cool_down;
            dp_i_no_stock_pre = dp_i_no_stock;
            dp_i_has_stock_pre = dp_i_has_stock;
        }

        return max(dp_i_no_stock, dp_i_in_cool_down);
    }
};

int main() {
    Solution s;

    vector<int> input{1, 2, 3, 0, 2};
    auto output = s.maxProfit(input);

    cout << "*************output*************" << endl;
    cout << output << endl;

    return 0;
}
