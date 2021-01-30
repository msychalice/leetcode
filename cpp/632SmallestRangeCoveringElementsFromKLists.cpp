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
    vector<int> smallestRange(vector<vector<int>>& nums) {
        using GreaterFunc = function<bool(pair<int, int>&, pair<int, int>&)>;
        GreaterFunc greaterFunc = [&](pair<int, int>& p1, pair<int, int>& p2) {
            auto& vec1 = nums[p1.first];
            auto& vec2 = nums[p2.first];
            int value1 = vec1[p1.second];
            int value2 = vec2[p2.second];
            if (value1 > value2) {
                return true;
            } else if (value1 == value2) {
                int diff1 = p1.second < vec1.size() - 1
                                ? vec1[p1.second + 1] - value1
                                : 0;
                int diff2 = p2.second < vec2.size() - 1
                                ? vec2[p2.second + 1] - value2
                                : 0;
                return diff1 > diff2;
            }

            return false;
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, GreaterFunc> pq(
            greaterFunc);  // pair(vectorIndex, valueIndex)
        int curMax = numeric_limits<int>::min();
        for (int i = 0; i < nums.size(); i++) {
            pq.push({i, 0});
            curMax = max(curMax, nums[i][0]);
        }

        int ansMax = numeric_limits<int>::max();
        int ansMin = 0;
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            int curMin = nums[cur.first][cur.second];

            // update ans
            if (curMax - curMin < ansMax - ansMin) {
                ansMax = curMax;
                ansMin = curMin;
            }

            // hit the end, break
            // because if we move any other pointers, we will not find a better
            // result, and we cannot move current pointer neither, so end the
            // whole procedure
            if (cur.second == nums[cur.first].size() - 1) {
                break;
            }

            // push next
            // update curMax
            pq.push({cur.first, cur.second + 1});
            curMax = max(curMax, nums[cur.first][cur.second + 1]);
        }

        return vector<int>{ansMin, ansMax};
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
