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
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        print2DimVec(intervals);
        printContainer(newInterval);
        /*
        vector<vector<int>> ans;

        bool newIsInserted = false;
        for (int i = 0; i < intervals.size(); i++) {
            auto interval = intervals[i];
            cout << "i " << i << " : " << interval[0] << "," << interval[1]
                 << endl;
if (newIsInserted) {
                ans.push_back(interval);
                cout << "1 push " << interval[0] << "," << interval[1] << endl;
                continue;
            }

            if (newInterval[0] < interval[0]) {
                if (newInterval[1] < interval[0]) {
                    ans.push_back(newInterval);
                    cout << "2 push newInterval" << endl;
                    newIsInserted = true;
                    ans.push_back(interval);
                    cout << "3 push " << interval[0] << "," << interval[1]
                         << endl;
                } else if (newInterval[1] >= interval[0] &&
                           newInterval[1] <= interval[1]) {
                    ans.push_back({newInterval[0], interval[1]});
                    newIsInserted = true;
                    cout << "4 push " << newInterval[0] << "," << interval[1]
                         << endl;
                } else if (newInterval[1] > interval[1]) {
                    // empty
                }
            } else if (newInterval[0] >= interval[0] &&
                       newInterval[0] <= interval[1]) {
                if (newInterval[1] <= interval[1]) {
                    ans.push_back(interval);
                    newIsInserted = true;
                    cout << "6 push " << interval[0] << "," << interval[1]
                         << endl;
                    continue;
                }

                // newInterval[1] > interval[1]
                // which is the most complicated case
                // the left boundary is determined, which is interval[0]
                // we need to find the right boundary
                int index = i + 1;
                int rightBoundary = newInterval[1];
                while (index < intervals.size()) {
                    auto nextInterval = intervals[index];
                    if (newInterval[1] < nextInterval[0]) {
                        rightBoundary = newInterval[1];
                        ans.push_back({interval[0], rightBoundary});
                        cout << "7 push " << interval[0] << "," << rightBoundary
                             << endl;
                        newIsInserted = true;
                        break;
                    } else if (newInterval[1] >= nextInterval[0] &&
                               newInterval[1] <= nextInterval[1]) {
                        rightBoundary = nextInterval[1];
                        ans.push_back({interval[0], rightBoundary});
                        newIsInserted = true;
                        i = index;  // important
                        cout << "8 push " << interval[0] << "," << rightBoundary
                             << endl;
                        break;
                    } else if (newInterval[1] > nextInterval[1]) {
                        index++;
                        i = index;  // important
                    }
                }

                // which means the right boundary is newInterval[1]
                if (!newIsInserted) {
                    ans.push_back({interval[0], rightBoundary});
                    newIsInserted = true;
                    cout << "9 push " << interval[0] << "," << rightBoundary
                         << endl;
                }
            } else {
                ans.push_back(interval);
                cout << "10 push " << interval[0] << "," << interval[1] << endl;
            }
        }

        if (!newIsInserted) {
            ans.push_back(newInterval);
            cout << "11 push " << newInterval[0] << "," << newInterval[1]
                 << endl;
        }

        return ans;
        */

        vector<vector<int>> ans;
        function<void(int, bool)> mergeNewInter = [&](int index,
                                                      bool isNewInterInserted) {
            if (isNewInterInserted) {
                if (index < intervals.size()) {
                    ans.push_back(intervals[index]);
                    mergeNewInter(index + 1, isNewInterInserted);
                }
                return;
            }

            if (index == intervals.size()) {
                ans.push_back(newInterval);
                return;
            }

            auto curInter = intervals[index];

            // curInter is before newInterval
            if (newInterval[0] > curInter[1]) {
                ans.push_back(curInter);
                mergeNewInter(index + 1, isNewInterInserted);
                return;
            }

            // newInterval is before curInter
            if (newInterval[1] < curInter[0]) {
                ans.push_back(newInterval);
                isNewInterInserted = true;
                mergeNewInter(index, isNewInterInserted);
                return;
            }

            // curInter completely covers newInterval
            if (newInterval[0] >= curInter[0] &&
                newInterval[1] <= curInter[1]) {
                isNewInterInserted = true;
                mergeNewInter(index, isNewInterInserted);
                return;
            }

            // newInterval completely covers curInter
            if (newInterval[0] <= curInter[0] &&
                newInterval[1] >= curInter[1]) {
                mergeNewInter(index + 1, isNewInterInserted);
                return;
            }

            // have intersection
            // merge curInter into newInterval
            newInterval[0] = min(newInterval[0], curInter[0]);
            newInterval[1] = max(newInterval[1], curInter[1]);
            mergeNewInter(index + 1, isNewInterInserted);
        };

        mergeNewInter(0, false);

        return ans;
    }
};

int main() {
    Solution s;

    cout << "*************output*************" << endl;

    /*
    vector<vector<int>> input{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> input1{4, 8};
    print2DimVec(s.insert(input, input1));
    */
    vector<vector<int>> input2{{0, 7}, {8, 8}, {9, 11}};
    vector<int> input3{4, 13};
    print2DimVec(s.insert(input2, input3));
    /*
     */

    return 0;
}
