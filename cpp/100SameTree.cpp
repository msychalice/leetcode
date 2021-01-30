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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        } else if (p == nullptr && q != nullptr) {
            return false;
        } else if (p != nullptr && q == nullptr) {
            return false;
        } else if (p != nullptr && q != nullptr) {
            if (p->val == q->val) {
                return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
            } else {
                return false;
            }
        }

        return true;
    }
};

int main(){
    Solution s;
    TreeNode node002(2);
    TreeNode node003(3);
    TreeNode node001(1, &node002, &node003);
    TreeNode node012(2);
    TreeNode node013(3);
    TreeNode node011(1, &node012, &node013);
    auto output = s.isSameTree(&node001, &node011);

    TreeNode node102(2);
    TreeNode node101(1, &node102, nullptr);
    TreeNode node112(2);
    TreeNode node111(1, nullptr, &node102);
    auto output1 = s.isSameTree(&node101, &node111);

    TreeNode node203(1);
    TreeNode node202(2);
    TreeNode node201(1, &node202, &node203);
    TreeNode node213(1);
    TreeNode node212(2);
    TreeNode node211(1, &node213, &node212);
    auto output2 = s.isSameTree(&node201, &node211);


    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;

    return 0;
}
