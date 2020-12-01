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
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A,
                                             vector<vector<int>>& B) {
        vector<vector<int>> output;
        if (A.size() == 0 || B.size() == 0) {
            return output;
        }

        vector<vector<int>> total(A.size() + B.size());
        copy(A.begin(), A.end(), total.begin());
        copy(B.begin(), B.end(), next(total.begin(), A.size()));

        sort(total.begin(), total.end(), [](vector<int> a, vector<int> b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });


        int prevBegin = total[0][0];
        int prevEnd = total[0][1];

        for (int i = 1; i < total.size(); i++) {
            int curBegin = total[i][0];
            int curEnd = total[i][1];

            if (curBegin <= prevEnd) {  // found intersection
                output.emplace_back(
                    vector<int>{curBegin, min(prevEnd, curEnd)});
            }

            prevBegin =
                curBegin;  // curBegin is always greater or equal than prevBegin
            prevEnd = max(prevEnd, curEnd);
        }

        return output;
    }
};

int main() {
    Solution s;

    vector<vector<int>> inputA{{0, 2}, {5, 10}, {13, 23}, {24, 25}};
    vector<vector<int>> inputB{{1, 5}, {8, 12}, {15, 24}, {25, 26}};
    auto output = s.intervalIntersection(inputA, inputB);

    vector<vector<int>> inputA1;
    vector<vector<int>> inputB1;
    auto output1 = s.intervalIntersection(inputA1, inputB1);

    vector<vector<int>> inputA2{{5, 10}};
    vector<vector<int>> inputB2{{5, 6}};
    auto output2 = s.intervalIntersection(inputA2, inputB2);

    cout << "*************output*************" << endl;
    print2DimVec(output);
    print2DimVec(output1);
    print2DimVec(output2);

    return 0;
}
