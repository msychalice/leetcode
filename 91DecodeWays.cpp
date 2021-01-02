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
    int numDecodings(string s) {
        if (s.size() == 0) {
            return 0;
        }
        if (s[0] == '0') {
            return 0;
        }
        if (s.size() == 1) {
            return 1;
        }

        vector<int> dp(s.size());

        // base case
        dp[0] = s[0] == '0' ? 0 : 1;
        if (s[1] == '0') {
            // edge case which is an invalid input
            if (s[0] > '2' || s[0] == '0') {
                return 0;
            }
            dp[1] = dp[0];
        } else {
            dp[1] = s[0] == '1' || (s[0] == '2' && s[1] >= '1' && s[1] <= '6')
                        ? 2
                        : 1;
        }

        for (int i = 2; i < s.size(); ++i) {
            if (s[i] == '0') {
                // edge case which is an invalid input
                if (s[i - 1] > '2' || s[i - 1] == '0') {
                    return 0;
                }

                dp[i] = dp[i - 2];
            } else {
                dp[i] = dp[i - 1];
                if (s[i - 1] == '1' ||
                    (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6')) {
                    dp[i] += dp[i - 2];
                }
            }
        }

        return dp[s.size() - 1];
    }
};

int main(){
    Solution s;
    /*
    cout << s.numDecodings("12") << endl;
    cout << s.numDecodings("226") << endl;
    cout << s.numDecodings("0") << endl;
    cout << s.numDecodings("1") << endl;
    cout << s.numDecodings("01") << endl;
    cout << s.numDecodings("00") << endl;
    cout << s.numDecodings("000") << endl;
    cout << s.numDecodings("301") << endl;
    */
    cout << s.numDecodings("2101") << endl;
    /*
    cout << s.numDecodings("10011") << endl;
    cout << s.numDecodings("2611055971756562") << endl;
     */

    cout << "*************output*************" << endl;

    return 0;
}
