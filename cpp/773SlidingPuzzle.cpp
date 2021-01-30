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
    int slidingPuzzle(vector<vector<int>>& board) {
        stringstream ss;
        for (auto& row : board) {
            for (auto i : row) {
                ss << i;
            }
        }
        string start = ss.str();
        constexpr auto target = "123450";

        queue<string> queStates;
        unordered_set<string> setVisited;
        int step = 0;

        queStates.push(start);
        setVisited.insert(start);

        while (!queStates.empty()) {
            int curQueSize = queStates.size();
            for (int i = 0; i < curQueSize; i++) {
                string curState = queStates.front();
                queStates.pop();

                if (curState == target) {
                    return step;
                }

                // visit all the unvisited next states and insert into que
                static unordered_map<int, vector<int>> mapNextStates = {
                    {0, {1, 3}}, {1, {0, 2, 4}}, {2, {1, 5}},
                    {3, {0, 4}}, {4, {1, 3, 5}}, {5, {2, 4}}};

                int zeroPosition = curState.find('0');
                for (auto& pos : mapNextStates[zeroPosition]) {
                    string nextState = curState;
                    swap(nextState[zeroPosition], nextState[pos]);
                    if (setVisited.count(nextState) != 0) {
                        continue;
                    }

                    queStates.push(nextState);
                    setVisited.emplace(move(nextState));
                }
            }

            step++;
        }

        return -1;
    }
};

int main() {
    Solution s;

    vector<vector<int>> input1{{1, 2, 3}, {4, 0, 5}};
    cout << s.slidingPuzzle(input1) << endl;

    vector<vector<int>> input2{{1, 2, 3}, {5, 4, 0}};
    cout << s.slidingPuzzle(input2) << endl;

    vector<vector<int>> input3{{4, 1, 2}, {5, 0, 3}};
    cout << s.slidingPuzzle(input3) << endl;

    vector<vector<int>> input4{{3, 2, 4}, {1, 5, 0}};
    cout << s.slidingPuzzle(input4) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
