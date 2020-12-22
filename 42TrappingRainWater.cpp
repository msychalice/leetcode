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
    int trap(vector<int>& height) {
        if (height.size() == 0) {
            return 0;
        }

        /* memoization
        vector<int> leftMax(height.size());
        vector<int> rightMax(height.size());

        leftMax[0] = height[0];
        rightMax[height.size() - 1] = height[height.size() - 1];

        for (int i = 1; i < height.size(); i++) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }
        for (int i = height.size() - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        int output = 0;
        for (int i = 0; i < height.size(); i++) {
            int capacity = min(leftMax[i], rightMax[i]) - height[i];
            output += capacity > 0 ? capacity : 0;
        }
        return output;
        */

        // two pointers
        int left = 0;
        int right = height.size() - 1;
        int leftMaxHeight = height[left];
        int rightMaxHeight = height[right];

        int output = 0;
        while (left <= right) {
            if (leftMaxHeight < rightMaxHeight) {
                int capacity = leftMaxHeight - height[left];
                output += capacity > 0 ? capacity : 0;
                leftMaxHeight = max(leftMaxHeight, height[left]);
                left++;
            } else {
                int capacity = rightMaxHeight - height[right];
                output += capacity > 0 ? capacity : 0;
                rightMaxHeight = max(rightMaxHeight, height[right]);
                right--;
            }
        }
        return output;
    }
};

int main(){
    Solution s;

    vector<int> input{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << s.trap(input) << endl;

    vector<int> input1{4, 2, 0, 3, 2, 5};
    cout << s.trap(input1) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
