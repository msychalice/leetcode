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

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        // iterative
        if (root == nullptr) {
            return nullptr;
        }

        Node* curLayerHead = root;
        while (curLayerHead != nullptr) {  // for each layer
            Node* cur = curLayerHead;
            Node* prev = nullptr;
            // for each node in the layer, connect their child nodes
            while (cur != nullptr) {
                Node* prevChild = nullptr;
                if (prev != nullptr) {
                    if (prev->right != nullptr) {
                        prevChild = prev->right;
                    } else {
                        prevChild = prev->left;
                    }
                }

                if (cur->left == nullptr && cur->right == nullptr) {
                    cur = cur->next;
                    continue;
                }

                if (cur->left != nullptr) {
                    if (prevChild != nullptr) {
                        prevChild->next = cur->left;
                    }
                    cur->left->next = cur->right;

                    prev = cur;
                    cur = cur->next;
                    continue;
                }

                if (cur->right != nullptr) {
                    if (prevChild != nullptr) {
                        prevChild->next = cur->right;
                    }
                    prev = cur;
                    cur = cur->next;
                    continue;
                }
            }

            // find the head of the next layer, and move to the next layer
            while (curLayerHead != nullptr) {
                if (curLayerHead->left != nullptr) {
                    curLayerHead = curLayerHead->left;
                    break;
                }
                if (curLayerHead->right != nullptr) {
                    curLayerHead = curLayerHead->right;
                    break;
                }
                curLayerHead = curLayerHead->next;
            }
        }

        return root;
    }
};

int main() {
    Solution s;

    Node* root =
        new Node(1, new Node(2, new Node(4), new Node(5), nullptr),
                 new Node(3, new Node(6), new Node(7), nullptr), nullptr);
    auto output = s.connect(root);

    cout << "*************output*************" << endl;

    return 0;
}
