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
    string minWindow(string s, string t) {
        int left = 0;   // left index of window, inclusive
        int right = 0;  // right index of window, exclusive
        int start = 0;  // start index of minimum substring
        int len = numeric_limits<int>::max();  // length of minimum substring

        unordered_map<char, int> target;
        unordered_map<char, int> window;
        int validCount = 0;  // how many chars are covered

        for (auto c : t) {
            target[c]++;
        }

        while (right < s.size()) {
            char rChar = s[right];
            if (target.find(rChar) != target.end()) {
                window[rChar]++;
                if (window[rChar] == target[rChar]) {
                    validCount++;
                }
            }
            right++;

            while (validCount == target.size()) {  // found a substring
                if (right - left < len) {
                    start = left;
                    len = right - left;
                }

                char lChar = s[left];
                if (target.find(lChar) != target.end()) {
                    if (window[lChar] == target[lChar]) {
                        validCount--;
                    }
                    window[lChar]--;
                }

                left++;
            }
        }

        return len == numeric_limits<int>::max() ? "" : s.substr(start, len);
    }
};

int main() {
    Solution s;

    auto output = s.minWindow("ADOBECODEBANC", "ABC");

    auto output1 = s.minWindow("a", "a");

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}
