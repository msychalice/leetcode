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
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }
        sort(nums.begin(), nums.end());

        function<vector<vector<int>>(int, int)> twoSum = [&nums](int start,
                                                                 int target) {
            vector<vector<int>> output;
            int low = start;
            int high = nums.size() - 1;

            while (low < high) {
                if (nums[low] + nums[high] == target) {  // found an answer
                    output.emplace_back(vector<int>{nums[low], nums[high]});
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
            return output;
        };

        function<vector<vector<int>>(int, int, int)> kSum =
            [&nums, &twoSum, &kSum](int start, int k, int target) {
                vector<vector<int>> output;
                if (nums.size() - start < k) {
                    return output;
                }

                if (k == 2) {
                    return twoSum(start, target);
                }

                for (int i = start; i < nums.size() - k + 1; i++) {
                    auto outputK_1 = kSum(i + 1, k - 1, target - nums[i]);
                    for (auto& n : outputK_1) {
                        n.push_back(nums[i]);
                        output.push_back(n);
                    }

                    // skip all the duplicate answers
                    while (i < nums.size() - k + 1 && nums[i] == nums[i + 1]) {
                        i++;
                    }
                }

                return output;
            };

        return kSum(0, 4, target);
    }
};

int main() {
    Solution s;

    vector<int> input{1, 0, -1, 0, -2, 2};
    auto output = s.fourSum(input, 0);

    vector<int> input1;
    auto output1 = s.fourSum(input1, 0);

    cout << "*************output*************" << endl;
    print2DimVec(output);
    print2DimVec(output1);

    return 0;
}
