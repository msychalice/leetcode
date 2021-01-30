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
    int maxProfit(vector<int>& prices, int fee) {
        // 1 <= i <= prices.size()
        // k is infinity

        int dp_i_nostock = 0;                            // i = 0
        int dp_i_hasstock = numeric_limits<int>::min();  // i = 0

        int dp_i_nostock_pre = dp_i_nostock;
        int dp_i_hasstock_pre = dp_i_hasstock;

        for (int i = 1; i <= prices.size(); i++) {
            dp_i_nostock = max(dp_i_nostock_pre,
                               dp_i_hasstock_pre == numeric_limits<int>::min()
                                   ? numeric_limits<int>::min()
                                   : dp_i_hasstock_pre + prices[i - 1] - fee);
            dp_i_hasstock =
                max(dp_i_hasstock_pre, dp_i_nostock_pre - prices[i - 1]);

            dp_i_nostock_pre = dp_i_nostock;
            dp_i_hasstock_pre = dp_i_hasstock;
        }

        return dp_i_nostock;
    }
};

int main() {
    Solution s;

    vector<int> input{1, 3, 2, 8, 4, 9};
    auto output = s.maxProfit(input, 2);

    cout << "*************output*************" << endl;
    cout << output << endl;

    return 0;
}
