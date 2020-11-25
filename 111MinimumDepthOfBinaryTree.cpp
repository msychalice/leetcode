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
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int depth = 1;
        queue<TreeNode*> que;
        que.push(root);

        while (!que.empty()) {
            int queSize = que.size();
            for (int i = 0; i < queSize; i++) {
                TreeNode* curNode = que.front();
                que.pop();

                if (curNode->left == nullptr && curNode->right == nullptr) {
                    return depth;
                }

                if (curNode->left != nullptr) {
                    que.push(curNode->left);
                }
                if (curNode->right != nullptr) {
                    que.push(curNode->right);
                }
            }

            depth++;
        }

        return depth;
    }
};

int main() {
    Solution s;

    TreeNode node015(15);
    TreeNode node007(7);
    TreeNode node020(20, &node015, &node007);
    TreeNode node009(9);
    TreeNode node003(3, &node009, &node020);
    auto output = s.minDepth(&node003);

    TreeNode node106(6);
    TreeNode node105(5, nullptr, &node106);
    TreeNode node104(4, nullptr, &node105);
    TreeNode node103(3, nullptr, &node104);
    TreeNode node102(2, nullptr, &node103);
    auto output1 = s.minDepth(&node102);

    TreeNode node205(5);
    TreeNode node204(4);
    TreeNode node203(3);
    TreeNode node202(2, &node204, &node205);
    TreeNode node201(1, &node202, &node203);
    auto output2 = s.minDepth(&node201);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;

    return 0;
}
