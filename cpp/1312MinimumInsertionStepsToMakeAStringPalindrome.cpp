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
    int minInsertions(string s) {
        vector<vector<int>> dp(2, vector<int>(s.size()));

        // base case
        // dp[i][i] = 0

        for (int i = s.size() - 2; i >= 0; i--) {
            for (int j = i + 1; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    dp[i % 2][j] = dp[(i + 1) % 2][j - 1];
                } else {
                    dp[i % 2][j] =
                        min(dp[(i + 1) % 2][j], dp[i % 2][j - 1]) + 1;
                }
            }
        }

        return dp[0][s.size() - 1];
    }
};

int main(){
    Solution s;
    /*
     */
    cout << s.minInsertions("zzazz") << endl;
    cout << s.minInsertions("mbadm") << endl;
    cout << s.minInsertions("leetcode") << endl;
    cout << s.minInsertions("g") << endl;
    cout << s.minInsertions("no") << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
