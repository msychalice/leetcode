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
    int getMoneyAmount(int n) {
        // padding dp[0][j], dp[i][0]
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));

        // base case
        // dp[i][i] = 0
        for (int i = n - 1; i > 0; i--) {
            for (int j = i + 1; j <= n; j++) {
                dp[i][j] = numeric_limits<int>::max();

                for (int x = i; x <= j; x++) {
                    int left = x > i ? dp[i][x - 1] : 0;
                    int right = x < j ? dp[x + 1][j] : 0;
                    dp[i][j] = min(dp[i][j], max(left, right) + x);
                }
            }
        }

        return dp[1][n];
    }
};

int main(){
    Solution s;
    /*
    cout << s.getMoneyAmount(10) << endl;
    cout << s.getMoneyAmount(1) << endl;
    cout << s.getMoneyAmount(2) << endl;
    cout << s.getMoneyAmount(19) << endl;  // expected 46
     */
    cout << s.getMoneyAmount(20) << endl;  // expected 49
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
    }
