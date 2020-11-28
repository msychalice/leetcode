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
    int rob(TreeNode* root) {
        function<tuple<int, int>(TreeNode*)> postorder =
            [&postorder](TreeNode* node) {
                if (node == nullptr) {
                    return make_tuple(0, 0);
                }

                auto [leftRob, leftNotRob] = postorder(node->left);
                auto [rightRob, rightNotRob] = postorder(node->right);

                int rob = node->val + leftNotRob + rightNotRob;
                int notRob =
                    max(leftRob, leftNotRob) + max(rightRob, rightNotRob);
                return make_tuple(rob, notRob);
            };

        auto [rootRob, rootNotRob] = postorder(root);

        return max(rootRob, rootNotRob);
    }
};

int main() {
    Solution s;

    TreeNode node01(1);
    TreeNode node02(3);
    TreeNode node03(3, nullptr, &node01);
    TreeNode node04(2, nullptr, &node02);
    TreeNode node05(3, &node04, &node03);
    auto output = s.rob(&node05);

    TreeNode node11(1);
    TreeNode node12(3);
    TreeNode node13(1);
    TreeNode node14(5, nullptr, &node11);
    TreeNode node15(4, &node13, &node12);
    TreeNode node16(3, &node15, &node14);
    auto output1 = s.rob(&node16);

    // 2,1,3,null,4
    TreeNode node21(4);
    TreeNode node22(3);
    TreeNode node23(1, nullptr, &node21);
    TreeNode node24(2, &node23, &node22);
    auto output2 = s.rob(&node24);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;

    return 0;
}
