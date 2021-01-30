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
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = -1;
        int last = -1;
        int min = 0;
        int max = nums.size();

        // find first
        while (min < max) {
            int cur = (min + max) / 2;
            if (nums[cur] == target) {
                if (cur == 0 || nums[cur - 1] < target) {
                    first = cur;
                    break;
                } else {  // move left
                    max = cur;
                }
            } else if (nums[cur] < target) {  // move right
                min = cur + 1;
            } else if (nums[cur] > target) {  // move left
                max = cur;
            }
        }

        if (first == -1) {
            return vector<int>{first, last};
        }

        min = first;  // use first to optimize the process of finding last
        max = nums.size();
        // find last
        while (min < max) {
            int cur = (min + max) / 2;
            if (nums[cur] == target) {
                if (cur == nums.size() - 1 || nums[cur + 1] > target) {
                    last = cur;
                    break;
                } else {  // move right
                    min = cur + 1;
                }
            } else if (nums[cur] < target) {  // move right
                min = cur + 1;
            } else if (nums[cur] > target) {  // move left
                max = cur;
            }
        }

        return vector<int>{first, last};
    }
};

int main() {
    Solution s;

    vector<int> input{5, 7, 7, 8, 8, 10};
    auto output = s.searchRange(input, 8);

    vector<int> input1{5, 7, 7, 8, 8, 10};
    auto output1 = s.searchRange(input1, 6);

    vector<int> input2{};
    auto output2 = s.searchRange(input2, 0);

    cout << "*************output*************" << endl;
    printContainer(output);
    printContainer(output1);
    printContainer(output2);

    return 0;
}
