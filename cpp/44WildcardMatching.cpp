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
    bool isMatch(string s, string p) {
        vector<vector<int>> memo(s.size() + 1, vector<int>(p.size() + 1, -1));

        // dp(i,j) returns whether the substring starting at ith character of s
        // matches the substring starting at jth character of p
        // i == 0 means s[0...s.size()-1]
        // i == s.size() means reaching the end of s
        function<bool(int, int)> dp = [&dp, &memo, &s, &p](int i,
                                                           int j) -> bool {
            if (memo[i][j] != -1) {
                return memo[i][j];
            }
            // both reach the end
            if (i == s.size() && j == p.size()) {
                memo[i][j] = true;
                return memo[i][j];
            }
            if (i == s.size() && j < p.size()) {
                if (p[j] == '*') {
                    memo[i][j] = dp(i, j + 1);
                } else {
                    memo[i][j] = false;
                }
                return memo[i][j];
            }
            if (i < s.size() && j == p.size()) {
                memo[i][j] = false;
                return memo[i][j];
            }

            if (s[i] == p[j] || (s[i] != p[j] && p[j] == '?')) {
                memo[i][j] = dp(i + 1, j + 1);
            } else {
                if (p[j] == '*') {
                    // match 0 or 1 s[i]
                    memo[i][j] = dp(i, j + 1) || dp(i + 1, j);
                } else {
                    memo[i][j] = false;
                }
            }
            return memo[i][j];
        };

        return dp(0, 0);
    }
};

int main(){
    Solution s;
    /*
    */
    cout << s.isMatch("aa", "a") << endl;
    cout << s.isMatch("aa", "*") << endl;
    cout << s.isMatch("cb", "?a") << endl;
    cout << s.isMatch("adceb", "*a*b") << endl;
    cout << s.isMatch("acdcb", "a*c?b") << endl;
    cout << s.isMatch("", "") << endl;
    cout << s.isMatch("ab", "") << endl;
    cout << s.isMatch("", "*") << endl;
    cout << s.isMatch("", "?") << endl;
    cout << s.isMatch("", "**") << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
