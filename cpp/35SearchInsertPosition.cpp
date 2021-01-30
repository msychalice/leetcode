#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <utility>
#include <cstdlib>
#include <limits>
#include <functional>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <queue>

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
    int searchInsert(vector<int>& nums, int target) {
        int min = 0;
        int max = nums.size();
        while (min < max) {
            int cur = (min + max) / 2;

            if (target <= nums[cur]) {
                max = cur;
            } else {
                min = cur + 1;
            }
        }
        return min;
    }
};

int main(){
    Solution s;
    vector<int> input{1, 3, 5, 6};
	auto output = s.searchInsert(input, 5);
    vector<int> input1{1, 3, 5, 6};
	auto output1 = s.searchInsert(input1, 2);
    vector<int> input2{1, 3, 5, 6};
	auto output2 = s.searchInsert(input2, 7);
    vector<int> input3{1, 3, 5, 6};
	auto output3 = s.searchInsert(input3, 0);
    vector<int> input4{1};
	auto output4 = s.searchInsert(input4, 0);
    vector<int> input5{1, 3};
	auto output5 = s.searchInsert(input5, 0);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;
    cout << output5 << endl;

    return 0;
}
