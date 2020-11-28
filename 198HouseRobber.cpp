#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
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

template<class T>
void printMap(const T& container) {
//    return;

    cout << "size " << container.size() << endl;
    if (container.size() == 0) {
        cout << "[]" << endl;
        return;
    }
    for (auto it = container.begin(); it != container.end(); it++) {
        if (it == container.begin()) {
            cout << "[ ";
        }

        cout << "[" << it->first << ", " << it->second << "]";

        if (next(it) == container.end()) {
            cout << " ]" << endl;
        } else {
            cout << ", ";
        }
    }
}

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    int rob(vector<int>& nums) {
        // 1 <= i <= nums.size()

        int dp_i_rob = numeric_limits<int>::min();  // i = 0, impossible to rob,
                                                    // set it to minus infinity.
        int dp_i_notrob = 0;  // i = 0, do not rob, value is 0

        int dp_i_rob_pre = dp_i_rob;
        int dp_i_notrob_pre = dp_i_notrob;

        for (int i = 1; i <= nums.size(); i++) {
            dp_i_rob = dp_i_notrob_pre + nums[i - 1];
            dp_i_notrob = max(dp_i_notrob_pre, dp_i_rob_pre);

            dp_i_rob_pre = dp_i_rob;
            dp_i_notrob_pre = dp_i_notrob;
        }

        return max(dp_i_rob, dp_i_notrob);
    }
};

int main() {
    Solution s;

    vector<int> input{1, 2, 3, 1};
    auto output = s.rob(input);

    vector<int> input1{2, 7, 9, 3, 1};
    auto output1 = s.rob(input1);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}
