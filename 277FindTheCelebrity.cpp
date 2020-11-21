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
    int findCelebrity(const vector<vector<int>> &matrix) {
        auto knows = [&matrix](int a, int b) {
            return matrix[a][b] == 1;
        };

        int celebrityIndex = 0;

        for (int i = 1; i < matrix.size(); i++) {
            if (knows(celebrityIndex, i)) {
                celebrityIndex = i;
            } else {
                // i is not a celebrity, because someone doesn't know i
                // empty
            }
        }

        for (int i = 0; i < matrix.size(); i++) {
            if (i == celebrityIndex) {
                continue;
            }

            if (!knows(i, celebrityIndex) || knows(celebrityIndex, i)) {
                return -1;
            }
        }

        return celebrityIndex;
    }
};

int main() {
    Solution s;

    vector<vector<int>> input = {
        {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}};
    auto output = s.findCelebrity(input);

    vector<vector<int>> input1 = {
        {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};
    auto output1 = s.findCelebrity(input1);

    vector<vector<int>> input2 = {{0, 1, 0}, {0, 0, 0}, {0, 1, 0}};
    auto output2 = s.findCelebrity(input2);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;

    return 0;
}
