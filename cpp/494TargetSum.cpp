#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
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

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = 0;
        for (auto n : nums) {
            sum += n;
        }

        // nums[i] is non-negative, and S can be negative
        if (S > sum || S < -sum) {
            return 0;
        }

        /* recursion with memoization

        // all the possible sums are within [-sum, sum]
        vector<vector<int>> memo(nums.size(), vector<int>(2 * sum + 1, -1));

        function<int(int, int)> dp = [&dp, &nums, &sum, &memo](int i, int j) {
            if (memo[i][j] != -1) {
                return memo[i][j];
            }

            // initialize memo[i][j]
            memo[i][j] = 0;

            // base case
            if (i == 0) {
                if (j == sum - abs(nums[i])) {
                    memo[i][j] += 1;
                }
                if (j == sum + abs(nums[i])) {
                    memo[i][j] += 1;
                }

                // nums[i] == 0, memo[i][j] will be set to 2,
                // '+0' and '-0' are two valid cases
                // otherwise memo[i][j] is 1
                return memo[i][j];
            }

            if (j - nums[i] >= 0 && j - nums[i] <= 2 * sum) {
                // put '-' in front of nums[i]
                memo[i][j] += dp(i - 1, j - nums[i]);
            }
            if (j + nums[i] >= 0 && j + nums[i] <= 2 * sum) {
                // put '+' in front of nums[i]
                memo[i][j] += dp(i - 1, j + nums[i]);
            }

            return memo[i][j];
        };

        return dp(nums.size() - 1, S + sum);
        */

        vector<vector<int>> dp(2, vector<int>(2 * sum + 1));

        // base case
        // can not use =, have to use +=
        // in case nums[0] == 0, dp[0][sum] needs to be set to 2
        // the rest of dp[0][i]s are set to 0 by default
        dp[0][sum - abs(nums[0])] += 1;
        dp[0][sum + abs(nums[0])] += 1;

        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j <= 2 * sum; j++) {
                // following operations are +=, hence it needs to be reset to 0
                dp[i % 2][j] = 0;

                if (j - nums[i] >= 0 && j - nums[i] <= 2 * sum) {
                    // put '-' in front of nums[i]
                    dp[i % 2][j] += dp[(i - 1) % 2][j - nums[i]];
                }
                if (j + nums[i] >= 0 && j + nums[i] <= 2 * sum) {
                    // put '+' in front of nums[i]
                    dp[i % 2][j] += dp[(i - 1) % 2][j + nums[i]];
                }
            }
        }

        return dp[(nums.size() - 1) % 2][S + sum];
    }
};

int main(){
    Solution s;
    /*
     */
    vector<int> input{1, 1, 1, 1, 1};
    cout << s.findTargetSumWays(input, 3) << endl;
    /*
    vector<int> input1{1, 0};
    cout << s.findTargetSumWays(input1, 1) << endl;
    vector<int> input2{0, 0, 0, 0, 0, 0, 0, 0, 1};
    cout << s.findTargetSumWays(input2, 1) << endl;
     */

    cout << "*************output*************" << endl;

    return 0;
}
