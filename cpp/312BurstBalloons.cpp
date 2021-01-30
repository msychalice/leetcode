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
    int maxCoins(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> dp(len + 2, vector<int>(len + 2));

        auto getCoin = [&nums](int i) {
            if (i == 0 || i == nums.size() + 1) {  // two virtual balloon
                return 1;
            }
            return nums[i - 1];
        };

        // base case
        // dp[i][i+1] = 0,  0 <= i <= len

        for (int i = len - 1; i >= 0; i--) {
            for (int j = i + 2; j < len + 2; j++) {
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] =
                        max(dp[i][j], dp[i][k] + dp[k][j] +
                                          getCoin(i) * getCoin(k) * getCoin(j));
                }
            }
        }

        return dp[0][len + 1];
    }
};

int main(){
    Solution s;
    /*
     */
    vector<int> input{3, 1, 5, 8};
    cout << s.maxCoins(input) << endl;
    vector<int> input1{1, 5};
    cout << s.maxCoins(input1) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
