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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        function<int(vector<int>&, int, int, int)> getTargetNumIndex =
            [](vector<int>& order, int begin, int end, int targetNum) {
                if (begin < 0 || end >= order.size()) {
                    return -1;
                }

                for (int i = begin; i <= end; i++) {
                    if (order[i] == targetNum) {
                        return i;
                    }
                }

                return -1;
            };

        function<TreeNode*(int, int, int, int)> buildSubtree =
            [&buildSubtree, &getTargetNumIndex, &preorder, &inorder](
                int preorderBegin, int preorderEnd, int inorderBegin,
                int inorderEnd) -> TreeNode* {
            if (preorderBegin > preorderEnd) {
                return nullptr;
            }

            int rootNum = preorder[preorderBegin];
            TreeNode* subtreeRoot = new TreeNode(rootNum);

            if (preorderBegin == preorderEnd) {
                return subtreeRoot;
            }

            int inorderRootIndex =
                getTargetNumIndex(inorder, inorderBegin, inorderEnd, rootNum);
            int leftNodeCount = inorderRootIndex - inorderBegin;
            int rightNodeCount = inorderEnd - inorderRootIndex;

            if (leftNodeCount > 0) {  // left tree is not empty
                int inorderBeginLeft = inorderBegin;
                int inorderEndLeft = inorderRootIndex - 1;
                int preorderBeginLeft = preorderBegin + 1;
                int preorderEndLeft = preorderBeginLeft + leftNodeCount - 1;
                subtreeRoot->left =
                    buildSubtree(preorderBeginLeft, preorderEndLeft,
                                 inorderBeginLeft, inorderEndLeft);
            }

            if (rightNodeCount > 0) {  // right tree is not empty
                int inorderBeginRight = inorderRootIndex + 1;
                int inorderEndRight = inorderEnd;
                int preorderBeginRight = preorderBegin + leftNodeCount + 1;
                int preorderEndRight = preorderEnd;
                subtreeRoot->right =
                    buildSubtree(preorderBeginRight, preorderEndRight,
                                 inorderBeginRight, inorderEndRight);
            }

            return subtreeRoot;
        };

        return buildSubtree(0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};

int main() {
    Solution s;

    /*
    vector<int> preorder{3, 9, 20, 15, 7};
    vector<int> inorder{9, 3, 15, 20, 7};
    auto output = s.buildTree(preorder, inorder);

    vector<int> preorder1{1, 2};
    vector<int> inorder1{1, 2};
    auto output1 = s.buildTree(preorder1, inorder1);
    */

    vector<int> preorder2{1, 2, 3};
    vector<int> inorder2{3, 2, 1};
    auto output2 = s.buildTree(preorder2, inorder2);

    cout << "*************output*************" << endl;

    /*
    printTree(output);
    printTree(output1);
    */
    printTree(output2);

    return 0;
}
