#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <utility>
#include <cstdlib>
#include <limits>
#include <functional>
#include <stack>
#include <unordered_set>

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

/**
 * Definition for a binary tree node.
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> output;

        /*
         * recursive solution
        function<void(TreeNode*)> traverse = [&output, &traverse](TreeNode* node) {
            if (node == nullptr) {
                return;
            }

            traverse(node->left);
            output.push_back(node->val);
            traverse(node->right);
        };

        traverse(root);
         */

        if (root == nullptr) {
            return output;
        }

        //iterative solution
        stack<TreeNode*> deferedNodes;
        unordered_set<TreeNode*> visitedNodes;

        while (true) {
            if (root->left != nullptr &&
                    visitedNodes.find(root->left) == visitedNodes.end()) {
                deferedNodes.push(root);
                visitedNodes.insert(root->left);
                root = root->left;
            } else {
                output.push_back(root->val);
                if (root->right != nullptr) {
                    root = root->right;
                } else {
                    if (deferedNodes.empty()) {
                        break;
                    } else {
                        root = deferedNodes.top();
                        deferedNodes.pop();
                    }
                }
            }
        }


        return output;
    }
};


int main(){
    Solution s;
    TreeNode t1(3);
    TreeNode t2(2, &t1, nullptr);
    TreeNode root(1, nullptr, &t2);
    auto output = s.inorderTraversal(&root);

    auto output1 = s.inorderTraversal(nullptr);

    TreeNode root2(1);
    auto output2 = s.inorderTraversal(&root2);

    TreeNode t3(2);
    TreeNode root3(1, &t3, nullptr);
    auto output3 = s.inorderTraversal(&root3);


    TreeNode t4(2);
    TreeNode root4(1, nullptr, &t4);
    auto output4 = s.inorderTraversal(&root4);

    TreeNode t5(1);
    TreeNode t6(2);
    TreeNode root5(3, &t5, &t6);
    auto output5 = s.inorderTraversal(&root5);

    cout << "*************output*************" << endl;
    printContainer(output);
    printContainer(output1);
    printContainer(output2);
    printContainer(output3);
    printContainer(output4);
    printContainer(output5);

    return 0;
}
