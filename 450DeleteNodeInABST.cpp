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

void printTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->val << endl;
    printTree(root->left);
    printTree(root->right);
}

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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }

        // if the node is found and deleted, return the deleted node and the new
        // root, otherwise return [nullptr, node]
        function<pair<TreeNode*, TreeNode*>(TreeNode*)> findAndDelete =
            [&findAndDelete,
             &key](TreeNode* node) -> pair<TreeNode*, TreeNode*> {
            if (node == nullptr) {
                return make_pair(nullptr, nullptr);
            }

            if (key == node->val) {
                // delete the largest node in a subtree
                // return the deleted node and the new root for the subtree
                function<pair<TreeNode*, TreeNode*>(TreeNode*)> deleteLargest =
                    [&deleteLargest](
                        TreeNode* node) -> pair<TreeNode*, TreeNode*> {
                    if (node == nullptr) {
                        return make_pair(nullptr, nullptr);
                    }

                    auto [deletedNode, newRightSubtree] =
                        deleteLargest(node->right);
                    if (deletedNode != nullptr) {
                        node->right = newRightSubtree;
                        return make_pair(deletedNode, node);
                    }

                    // no right subtree, have to delete itself
                    return make_pair(node, node->left);
                };

                // delete the smallest node in a subtree
                // return the deleted node and the new root for the subtree
                function<pair<TreeNode*, TreeNode*>(TreeNode*)> deleteSmallest =
                    [&deleteSmallest](
                        TreeNode* node) -> pair<TreeNode*, TreeNode*> {
                    if (node == nullptr) {
                        return make_pair(nullptr, nullptr);
                    }

                    auto [deletedNode, newLeftSubtree] =
                        deleteSmallest(node->left);
                    if (deletedNode != nullptr) {
                        node->left = newLeftSubtree;
                        return make_pair(deletedNode, node);
                    }

                    // no left subtree, have to delete itself
                    return make_pair(node, node->right);
                };

                TreeNode* newRoot = nullptr;

                auto [deletedNodeLeft, newLeftSubtree] =
                    deleteLargest(node->left);
                if (deletedNodeLeft != nullptr) {
                    newRoot = deletedNodeLeft;
                    newRoot->left = newLeftSubtree;
                    newRoot->right = node->right;
                    return make_pair(node, newRoot);
                }

                auto [deletedNodeRight, newRightSubtree] =
                    deleteSmallest(node->right);
                if (deletedNodeRight != nullptr) {
                    newRoot = deletedNodeRight;
                    newRoot->right = newRightSubtree;
                    newRoot->left = node->left;
                    return make_pair(node, newRoot);
                }

                return make_pair(node, nullptr);
            }

            if (key < node->val) {
                auto [deletedNode, newLeftSubtree] = findAndDelete(node->left);
                if (deletedNode != nullptr) {
                    node->left = newLeftSubtree;
                    return make_pair(deletedNode, node);
                }
            }

            if (key > node->val) {
                auto [deletedNode, newRightSubtree] =
                    findAndDelete(node->right);
                if (deletedNode != nullptr) {
                    node->right = newRightSubtree;
                    return make_pair(deletedNode, node);
                }
            }

            return make_pair(nullptr, node);
        };

        auto [deletedNode, newRoot] = findAndDelete(root);

        return newRoot;
    }
};

int main() {
    Solution s;

    /*
    auto output = s.deleteNode(
        new TreeNode(5, new TreeNode(3, new TreeNode(2), new TreeNode(4)),
                     new TreeNode(6, nullptr, new TreeNode(7))),
        3);

    auto output1 = s.deleteNode(
        new TreeNode(5, new TreeNode(3, new TreeNode(2), new TreeNode(4)),
                     new TreeNode(6, nullptr, new TreeNode(7))),
        0);

    auto output2 = s.deleteNode(nullptr, 0);
    */

    auto output3 = s.deleteNode(
        new TreeNode(5, new TreeNode(3, new TreeNode(2), new TreeNode(4)),
                     new TreeNode(6, nullptr, new TreeNode(7))),
        5);

    cout << "*************output*************" << endl;

    /*
    printTree(output);
    printTree(output1);
    printTree(output2);
    */
    printTree(output3);

    return 0;
}
