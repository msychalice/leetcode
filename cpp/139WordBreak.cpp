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
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict;
        for (auto& d : wordDict) {
            dict.insert(d);
        }

        /* recursion + memoization
        vector<vector<int>> memo(s.size(), vector<int>(s.size(), -1));

        function<bool(int, int)> dp = [&dp, &memo, &dict, &s](int i,
                                                              int j) -> bool {
            if (memo[i][j] != -1) {
                return memo[i][j];
            }

            string si = s.substr(i, (j - i) + 1);
            memo[i][j] = dict.count(si);
            if (memo[i][j]) {
                return memo[i][j];
            }

            // separate s[i,j] into two substrings [i,n-1] and [n,j]
            for (int n = i + 1; n <= j; n++) {
                memo[i][j] = dp(i, n - 1) && dp(n, j);
                if (memo[i][j]) {
                    return memo[i][j];
                }
            }

            return memo[i][j];
        };

        return dp(0, s.size() - 1);
        */

        vector<vector<bool>> dp(s.size(), vector<bool>(s.size()));

        // no base case

        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                string si = s.substr(i, (j - i) + 1);
                dp[i][j] = dict.count(si);

                if (dp[i][j]) {
                    continue;
                }

                // separate s[i,j] into two substrings [i,n-1] and [n,j]
                for (int n = i + 1; n <= j; n++) {
                    dp[i][j] = dp[i][n - 1] && dp[n][j];

                    if (dp[i][j]) {
                        break;
                    }
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
        vector<string> input{"leet", "code"};
        cout << s.wordBreak("leetcode", input) << endl;

        vector<string> input1{"apple", "pen"};
        cout << s.wordBreak("applepenapple", input1) << endl;

        vector<string> input2{"cats", "dog", "sand", "and", "cat"};
        cout << s.wordBreak("catsandog", input2) << endl;

        vector<string> input3{"a", "aa", "ba"};
        cout << s.wordBreak(
                    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                    "aaaa"
                    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                    "aaaa"
                    "aaaaaaaaaaaaaaaaaaaaaaaaaabab",
                    input3)
             << endl;
        /*
         */

        cout << "*************output*************" << endl;

        return 0;
    }
