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
    vector<int> findAnagrams(string s, string p) {
        vector<int> output;

        unordered_map<char, int> target;
        for (auto c : p) {
            target[c]++;
        }

        int left = -1;
        int right = 0;
        int validCharCount = 0;
        unordered_map<char, int> window;

        while (right < s.size()) {
            char rChar = s[right];
            if (target.find(rChar) != target.end()) {
                if (left == -1) {  // create a new window
                    left = right;
                }

                window[rChar]++;
                if (window[rChar] == target[rChar]) {
                    validCharCount++;
                }

                if (right - left == p.size()) {  // exceed the length of p,
                                                 // update the left index
                    int lChar = s[left];
                    if (window[lChar] == target[lChar]) {
                        validCharCount--;
                    }
                    window[lChar]--;
                    left++;
                }

                if (validCharCount == target.size()) {
                    output.push_back(left);
                }

            } else {  // clear the window
                left = -1;
                window.clear();
                validCharCount = 0;
            }
            right++;
        }

        return output;
    }
};

int main() {
    Solution s;

    auto output = s.findAnagrams("cbaebabacd", "abc");

    auto output1 = s.findAnagrams("abab", "ab");

    cout << "*************output*************" << endl;
    printContainer(output);
    printContainer(output1);

    return 0;
}
