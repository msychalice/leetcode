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
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) {
            return true;
        }
        int len = 0;
        ListNode* cur = head;
        while (cur != nullptr) {
            len++;
            cur = cur->next;
        }

        // reverse the first len/2 nodes
        ListNode* prev = nullptr;
        cur = head;
        ListNode* next = cur->next;
        for (int i = 1; i <= len / 2; i++) {
            cur->next = prev;
            prev = cur;
            cur = next;
            next = cur->next;  // cur can not be nullptr
        }

        // compare the reversed first len/2 nodes with the last len/2
        ListNode* firstRoot = prev;
        ListNode* secondRoot = len % 2 == 0 ? cur : cur->next;
        for (int i = 1; i <= len / 2; i++) {
            if (firstRoot->val != secondRoot->val) {
                return false;
            }
            firstRoot = firstRoot->next;
            secondRoot = secondRoot->next;
        }

        return true;
    }
};

int main() {
    Solution s;

    ListNode* root = new ListNode(1, new ListNode(2));
    auto output = s.isPalindrome(root);

    ListNode* root1 =
        new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(1))));
    auto output1 = s.isPalindrome(root1);

    ListNode* root2 = new ListNode(1);
    auto output2 = s.isPalindrome(root2);

    cout << "*************output*************" << endl;

    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;

    return 0;
}
