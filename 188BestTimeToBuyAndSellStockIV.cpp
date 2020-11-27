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
    int maxProfit(int k, vector<int>& prices) {
        // 1 <= i <= prices.size()
        // if k is greater or equal to prices.size()/2, treat k as infinity

        if (k >= prices.size() / 2) {
            int dp_i_0 = 0;                           // i = 0
            int dp_i_1 = numeric_limits<int>::min();  // i = 0

            int dp_i_0_pre = dp_i_0;
            int dp_i_1_pre = dp_i_1;

            for (int i = 1; i <= prices.size(); i++) {
                dp_i_0 = max(dp_i_0_pre, dp_i_1_pre + prices[i - 1]);
                dp_i_1 = max(dp_i_1_pre, dp_i_0_pre - prices[i - 1]);
                dp_i_0_pre = dp_i_0;
                dp_i_1_pre = dp_i_1;
            }

            return dp_i_0;
        }

        vector<vector<vector<int>>> dp(
            prices.size() + 1, vector<vector<int>>(k + 1, vector<int>(2)));

        for (int i = 1; i <= prices.size(); i++) {
            for (int j = 1; j <= k; j++) {
                if (i == 1) {
                    dp[i - 1][j][0] = 0;
                    dp[i - 1][j][1] = numeric_limits<int>::min();
                }
                if (j == 1) {
                    dp[i][j - 1][0] = 0;
                    dp[i][j - 1][1] = numeric_limits<int>::min();
                }

                dp[i][j][0] =
                    max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
                dp[i][j][1] =
                    max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i - 1]);
            }
        }

        return dp[prices.size()][k][0];
    }
};

int main() {
    Solution s;

    vector<int> input{2, 4, 1};
    auto output = s.maxProfit(2, input);

    vector<int> input1{3, 2, 6, 5, 0, 3};
    auto output1 = s.maxProfit(2, input1);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}
