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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {
    }
};

class Solution {
public:
    bool canPartition(vector<int> &nums) {
        int sum = 0;

        for (auto i : nums) {
            sum += i;
        }

        if (sum % 2 != 0) {
            return false;
        }

        sum = sum / 2;

        /*
        vector<vector<bool>> cachedResult(nums.size() + 1,
                                          vector<bool>(sum + 1, false));

        for (int i = 1; i <= nums.size(); i++) {
            int curNum = nums[i - 1];
            for (int j = 1; j <= sum; j++) {
                if (j < curNum) {
                    cachedResult[i][j] = cachedResult[i - 1][j];
                } else if (j == curNum) {
                    cachedResult[i][j] = true;
                } else {
                    cachedResult[i][j] = cachedResult[i - 1][j] ||
                                         cachedResult[i - 1][j - curNum];
                }
            }
        }

        return cachedResult[nums.size()][sum];
        */

        // optimized version: using 1D vector
        vector<bool> cachedResult(sum + 1, false);
        for (int i = 1; i <= nums.size(); i++) {
            int curNum = nums[i - 1];
            for (int j = sum; j >= curNum; j--) {
                if (j == curNum) {
                    cachedResult[j] = true;
                } else {
                    cachedResult[j] =
                        cachedResult[j] || cachedResult[j - curNum];
                }
            }
        }

        return cachedResult[sum];
    }
};

int main() {
    Solution s;

    vector<int> input{1, 5, 11, 5};
    auto output = s.canPartition(input);

    vector<int> input1{1, 2, 3, 5};
    auto output1 = s.canPartition(input1);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}
