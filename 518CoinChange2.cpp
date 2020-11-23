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
    int change(int amount, vector<int> &coins) {
        if (amount == 0) {
            return 1;
        }
        if (coins.size() == 0) {
            return 0;
        }

        sort(coins.begin(), coins.end());

        vector<int> cachedResult(amount + 1, 0);

        // only has the smallest coin
        int curCoin = coins[0];
        for (int i = 1; i <= amount; i++) {
            cachedResult[i] = i % curCoin == 0 ? 1 : 0;
        }

        for (int i = 1; i <= coins.size() - 1; i++) {
            curCoin = coins[i];
            for (int j = amount; j >= 1; j--) {
                if (j < curCoin) {
                    // empty
                } else if (j == curCoin) {
                    cachedResult[j]++;
                } else {
                    for (int n = 1; n * curCoin <= j; n++) {
                        if (n * curCoin == j) {
                            cachedResult[j]++;
                        } else {
                            cachedResult[j] += cachedResult[j - n * curCoin];
                        }
                    }
                }
            }
        }

        return cachedResult[amount];
    }
};

int main() {
    Solution s;

    vector<int> input = {1, 2, 5};
    auto output = s.change(5, input);

    vector<int> input1 = {2};
    auto output1 = s.change(3, input1);

    vector<int> input2 = {10};
    auto output2 = s.change(10, input2);

    vector<int> input3 = {};
    auto output3 = s.change(0, input3);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;

    return 0;
}
