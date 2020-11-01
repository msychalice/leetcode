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
#include <algorithm>

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

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, vector<int>> mapNums;
        for (int i = 0; i < nums.size(); i++) {
            auto it = mapNums.find(nums[i]);
            if (it != mapNums.end()) {
                (it->second).push_back(i);
            } else {
                mapNums.emplace(nums[i], vector<int>{i});
            }
        }

        vector<int> output;

        for (const auto& n : nums) {
            auto it = mapNums.find(n);
            auto itTarget = mapNums.find(target-n);
            if (it != mapNums.end() && itTarget != mapNums.end()) {
                const auto& vecIndex = it->second;
                const auto& vecTargetIndex = itTarget->second;
                if (it == itTarget && vecIndex.size() > 1) {
                    output.push_back(vecIndex[0]);
                    output.push_back(vecIndex[1]);
                    break;
                }

                if (it != itTarget) {
                    output.push_back(vecIndex[0]);
                    output.push_back(vecTargetIndex[0]);
                    break;
                }
            }
        }

        return output;
    }
};

int main(){
    Solution s;

    vector<int> input{3, 2, 4};
	auto output = s.twoSum(input, 6);

    cout << "*************output*************" << endl;
    printContainer(output);

    return 0;
}
