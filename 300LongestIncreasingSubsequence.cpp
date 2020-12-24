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
    int lengthOfLIS(vector<int>& nums) {
        /*
        vector<int> dp(nums.size(), 1);

        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        int output = 0;
        for (auto l : dp) {
            output = max(output, l);
        }
        return output;
        */

        if (nums.size() == 0) {
            return 0;
        }
        vector<int> dp(nums.size());
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

        dp[0] = nums[0];
        int len = 1;
        for (int i = 1; i < nums.size(); i++) {
            int index = bs(nums[i], 0, len);
            dp[index] = nums[i];

            if (index == len) {
                len++;
            }
        }

        return len;
    }
};

int main(){
    Solution s;

    vector<int> input{1, 3, 6, 7, 9, 4, 10, 5, 6};
    cout << s.lengthOfLIS(input) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
