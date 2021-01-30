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
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> output;
        if (nums.size() < 3) {
            return output;
        }
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 2; i++) {
            int target = -nums[i];

            // convert the 3sum problem to 2sum problem
            int low = i + 1;
            int high = nums.size() - 1;

            while (low < high) {
                if (nums[low] + nums[high] == target) {  // found an answer
                    output.emplace_back(
                        vector<int>{nums[i], nums[low], nums[high]});
                    // skip all the duplicate answers
                    while (low < nums.size() - 1 &&
                           nums[low] == nums[low + 1]) {
                        low++;
                    }
                    low++;
                    while (high > 0 && nums[high] == nums[high - 1]) {
                        high--;
                    }
                    high--;
                } else if (nums[low] + nums[high] < target) {
                    low++;
                } else if (nums[low] + nums[high] > target) {
                    high--;
                }
            }

            // skip all the duplicate answers
            while (i < nums.size() - 2 && nums[i] == nums[i + 1]) {
                i++;
            }
        }

        return output;
    }
};

int main() {
    Solution s;

    vector<int> input{-1, 0, 1, 2, -1, -4};
    auto output = s.threeSum(input);

    vector<int> input1;
    auto output1 = s.threeSum(input1);

    vector<int> input2{0};
    auto output2 = s.threeSum(input2);

    cout << "*************output*************" << endl;
    print2DimVec(output);
    print2DimVec(output1);
    print2DimVec(output2);

    return 0;
}
