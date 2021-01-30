#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
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
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (K == 0) {
            vector<int>{target->val};
        }

        // node value is unique and 0 <= node.value <= 500
        vector<TreeNode*> parents(501);
        // preorder tree traversal
        function<void(TreeNode*)> preorder = [&](TreeNode* node) {
            if (node == nullptr) {
                return;
            }

            if (node->left != nullptr) {
                parents[node->left->val] = node;
            }
            if (node->right != nullptr) {
                parents[node->right->val] = node;
            }
            preorder(node->left);
            preorder(node->right);
        };
        preorder(root);

        queue<TreeNode*> neighbors;
        vector<bool> visited(501);
        vector<int> res;

        neighbors.push(target);
        visited[target->val] = true;
        int dist = 0;

        while (!neighbors.empty()) {
            int queSize = neighbors.size();

            while (queSize--) {
                TreeNode* curNode = neighbors.front();
                neighbors.pop();
                if (dist == K) {
                    // reach the target distance layer,
                    // stop searching for the next layer,
                    // and all the nodes in the queue are the result
                    res.push_back(curNode->val);
                    continue;
                }

                // the next layer contains all the child nodes and the parent
                // node
                vector<TreeNode*> nextLayer;
                if (curNode->left != nullptr) {
                    nextLayer.push_back(curNode->left);
                }
                if (curNode->right != nullptr) {
                    nextLayer.push_back(curNode->right);
                }
                if (parents[curNode->val] != nullptr) {
                    nextLayer.push_back(parents[curNode->val]);
                }
                for (auto node : nextLayer) {
                    if (visited[node->val]) {
                        continue;
                    }

                    visited[node->val] = true;
                    neighbors.push(node);
                }
            }

            if (dist == K) {
                return res;
            }

            dist++;
        }

        return res;
    }
};

int main() {
    Solution s;
    /*
     */
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
