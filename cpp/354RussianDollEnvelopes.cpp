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
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.size() == 0) {
            return 0;
        }

        sort(envelopes.begin(), envelopes.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 // sort by width in ascending order and
                 // by height in descending order
                 if (a[0] < b[0]) {
                     return true;
                 } else if (a[0] == b[0]) {
                     return a[1] > b[1];
                 } else {
                     return false;
                 }
             });

        // find LIS of the sequence of heights
        vector<int> dp(envelopes.size());
        // binary search [lo, hi)
        // if target is in dp, return the index of target,
        // otherwise return index that target is supposed to be inserted into
        function<int(int, int, int)> bs = [&dp](int target, int lo, int hi) {
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (dp[mid] == target) {
                    return mid;
                } else if (dp[mid] < target) {
                    lo = mid + 1;
                } else if (dp[mid] > target) {
                    hi = mid;
                }
            }
            return lo;
        };

        // base case
        dp[0] = envelopes[0][1];
        int len = 1;

        for (int i = 1; i < envelopes.size(); i++) {
            int lastIndex = bs(envelopes[i][1], 0, len);
            dp[lastIndex] = envelopes[i][1];

            if (lastIndex == len) {
                len++;
            }
        }

        return len;
    }
};

int main(){
    Solution s;

    vector<vector<int>> input{{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    cout << s.maxEnvelopes(input) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
