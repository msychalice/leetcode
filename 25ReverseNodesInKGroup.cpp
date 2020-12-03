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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr) {
            return nullptr;
        }
        if (k == 1) {
            return head;
        }

        ListNode* post = head;
        for (int i = 1; i <= k; i++) {
            if (post == nullptr) {  // k is greater than list length
                return head;
            }
            post = post->next;
        }

        // reverse k nodes
        ListNode* prev = nullptr;
        ListNode* cur = head;
        ListNode* next = cur->next;
        for (int i = 1; i <= k; i++) {
            cur->next = prev;
            prev = cur;
            cur = next;
            next = cur == nullptr ? nullptr : cur->next;
        }

        // recursively reverse the next k nodes
        head->next = reverseKGroup(post, k);

        return prev;
    }
};

int main() {
    Solution s;

    ListNode* root = new ListNode(
        1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    auto output = s.reverseKGroup(root, 2);

    ListNode* root1 = new ListNode(
        1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    auto output1 = s.reverseKGroup(root1, 3);

    ListNode* root2 = new ListNode(
        1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    auto output2 = s.reverseKGroup(root2, 1);

    ListNode* root3 = new ListNode(1);
    auto output3 = s.reverseKGroup(root3, 1);

    ListNode* root4 = new ListNode(1, new ListNode(2));
    auto output4 = s.reverseKGroup(root4, 2);

    cout << "*************output*************" << endl;

    printList(output);
    printList(output1);
    printList(output2);
    printList(output3);
    printList(output4);

    return 0;
}
