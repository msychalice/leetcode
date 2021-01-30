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
#include <queue>

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> output;

        if (root == nullptr) {
            return output;
        }

        function<void(int, TreeNode*)> levelTraverse =
            [&output, &levelTraverse](int parentHeight, TreeNode* node) {
                if (node == nullptr) {
                    return;
                }

                int height = parentHeight + 1;
                if (height < output.size()) {
                    output[height].push_back(node->val);
                } else if (height == output.size()) {
                    output.push_back(vector<int>{node->val});
                }

                if (node->left != nullptr) {
                    levelTraverse(height, node->left);
                }
                if (node->right != nullptr) {
                    levelTraverse(height, node->right);
                }
        };

        levelTraverse(-1, root);

        return output;
    }
};


int main(){
    Solution s;
    TreeNode t7(7);
    TreeNode t15(15);
    TreeNode t20(20, &t15, &t7);
    TreeNode t9(9);
    TreeNode root(3, &t9, &t20);
    auto output = s.levelOrder(&root);

    auto output1 = s.levelOrder(nullptr);

    TreeNode root2(1);
    auto output2 = s.levelOrder(&root2);

    TreeNode t3(2);
    TreeNode root3(1, &t3, nullptr);
    auto output3 = s.levelOrder(&root3);


    TreeNode t4(2);
    TreeNode root4(1, nullptr, &t4);
    auto output4 = s.levelOrder(&root4);

    TreeNode t5(1);
    TreeNode t6(2);
    TreeNode root5(3, &t5, &t6);
    auto output5 = s.levelOrder(&root5);

    cout << "*************output*************" << endl;
    print2DimVec(output);
    print2DimVec(output1);
    print2DimVec(output2);
    print2DimVec(output3);
    print2DimVec(output4);
    print2DimVec(output5);

    return 0;
}
