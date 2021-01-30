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
    int longestCommonSubsequence(string text1, string text2) {
        auto lcs = [](string& text1, string& text2) {
            vector<vector<int>> dp(2, vector<int>(text2.size() + 1));

            // base case
            for (int i = 0; i < 2; i++) {
                dp[i][0] = 0;
            }
            for (int i = 0; i <= text2.size(); i++) {
                dp[0][i] = 0;
            }

            for (int i = 1; i <= text1.size(); i++) {
                for (int j = 1; j <= text2.size(); j++) {
                    if (text2[j - 1] == text1[i - 1]) {
                        dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1;
                    } else {
                        dp[i % 2][j] =
                            max(dp[(i - 1) % 2][j], dp[i % 2][j - 1]);
                    }
                }
            }

            print2DimVec(dp);

            return dp[text1.size() % 2][text2.size()];
        };

        if (text1.size() < text2.size()) {
            return lcs(text2, text1);
        }
        return lcs(text1, text2);
    }
};

int main(){
    Solution s;

    cout << s.longestCommonSubsequence("abcde", "ace") << endl;

    cout << "*************output*************" << endl;

    return 0;
}
