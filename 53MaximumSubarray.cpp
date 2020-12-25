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
    int maxSubArray(vector<int>& nums) {
        // dp[i] is the max sum of the subarray ending with nums[i]
        vector<int> dp(nums.size());
        // base case
        dp[0] = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        }

        int output = numeric_limits<int>::min();
        for (auto s : dp) {
            output = max(output, s);
        }
        return output;
    }
};

int main(){
    Solution s;

    vector<int> input{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << s.maxSubArray(input) << endl;

    vector<int> input1{1};
    cout << s.maxSubArray(input1) << endl;

    vector<int> input2{0};
    cout << s.maxSubArray(input2) << endl;

    vector<int> input3{-1};
    cout << s.maxSubArray(input3) << endl;

    vector<int> input4{-2147483647};
    cout << s.maxSubArray(input4) << endl;

    vector<int> input5{-1, -2};
    cout << s.maxSubArray(input5) << endl;

    vector<int> input6{8, -19, 5, -4, 20};
    cout << s.maxSubArray(input6) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
