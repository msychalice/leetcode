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
    int lastStoneWeightII(vector<int>& stones) {
        if (stones.size() == 0) {
            return 0;
        }
        if (stones.size() == 1) {
            return stones[0];
        }
        if (stones.size() == 2) {
            return abs(stones[1] - stones[0]);
        }

        int sum = 0;
        for (auto s : stones) {
            sum += s;
        }

        int target = sum / 2;
        vector<vector<bool>> dp(stones.size() + 1,
                                vector<bool>(target + 1, false));

        // base case
        // dp[0][i] = false
        // dp[i][0] = true
        for (int i = 0; i <= stones.size(); i++) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= stones.size(); i++) {
            for (int j = 1; j <= target; j++) {
                dp[i][j] = dp[i - 1][j] ||
                           (j >= stones[i - 1] ? (dp[i - 1][j - stones[i - 1]])
                                               : false);
            }
        }

        int output = 0;
        for (int i = target; i >= 0; i--) {
            if (dp[stones.size()][i]) {
                output = sum - 2 * i;
                break;
            }
        }
        return output;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<int> input{2, 7, 4, 1, 8, 1};
    cout << s.lastStoneWeightII(input) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
