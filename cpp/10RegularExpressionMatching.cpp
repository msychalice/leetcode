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

        function<bool(int, int)> dp = [&dp, &memo, &s, &p](int i,
                                                           int j) -> bool {
            // reach the end of both strings
            if (i == s.size() && j == p.size()) {
                memo[i][j] = true;
                return true;
            }

            // s is empty and p is not
            if (i == s.size() && j < p.size()) {
                // return true only if p contains '*'
                if (p.size() - j >= 2 && p[j + 1] == '*') {
                    memo[i][j] = dp(i, j + 2);
                    return memo[i][j];
                } else {
                    memo[i][j] = false;
                    return memo[i][j];
                }
            }

            // p is empty and s is not, return false
            if (i < s.size() && j == p.size()) {
                memo[i][j] = false;
                return false;
            }

            // both of s and p are not empty
            if (p.size() - j >= 2 && p[j + 1] == '*') {  // p has '*'
                if (s[i] == p[j] || (s[i] != p[j] && p[j] == '.')) {
                    // s[i] can be matched for 0, 1, 2 ...
                    // here we only need to take care of 0 and 1,
                    // use recursion to get the answer for the rest cases

                    // this is the case where deep recursion will occur
                    if (memo[i][j] != -1) {
                        return memo[i][j];
                    }

                    memo[i][j] =
                        dp(i, j + 2) || dp(i + 1, j);  // match 0 or 1 character
                } else {
                    memo[i][j] = dp(i, j + 2);  // match 0 character
                }
                return memo[i][j];
            } else {
                if (s[i] == p[j] || (s[i] != p[j] && p[j] == '.')) {
                    memo[i][j] = dp(i + 1, j + 1);
                    return memo[i][j];
                } else {
                    memo[i][j] = false;
                    return false;
                }
            }

            return false;
        };

        return dp(0, 0);
    }
};

int main(){
    Solution s;
    /*
     */
    cout << s.isMatch("aa", "a") << endl;
    cout << s.isMatch("aa", "a*") << endl;
    cout << s.isMatch("ab", ".*") << endl;
    cout << s.isMatch("aab", "c*a*b") << endl;
    cout << s.isMatch("mississippi", "mis*is*p*.") << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
