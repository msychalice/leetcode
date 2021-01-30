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
    string removeDuplicateLetters(string s) {
        unordered_map<char, int> mapCharCount;

        for (auto c : s) {
            auto it = mapCharCount.find(c);
            if (it != mapCharCount.end()) {
                it->second++;
            } else {
                mapCharCount.emplace(c, 1);
            }
        }

        unordered_set<char> setIncluded;
        deque<char> deqChar;
        for (auto c : s) {
            if (deqChar.empty()) {
                deqChar.push_back(c);
                mapCharCount[c]--;
                setIncluded.insert(c);
                continue;
            }

            if (setIncluded.find(c) != setIncluded.end()) {
                mapCharCount[c]--;
                continue;
            }

            // remove the character that is larger than c and has the count
            // larger than 0
            while (!deqChar.empty() && deqChar.back() > c &&
                   mapCharCount[deqChar.back()] > 0) {
                setIncluded.erase(deqChar.back());
                deqChar.pop_back();
            }

            deqChar.push_back(c);
            mapCharCount[c]--;
            setIncluded.insert(c);
        }

        return string(deqChar.begin(), deqChar.end());
    }
};

int main() {
    Solution s;
    /*
    cout << s.removeDuplicateLetters("bcabc") << endl;
    cout << s.removeDuplicateLetters("cbacdcbc") << endl;
    */
    cout << s.removeDuplicateLetters("bbcaac") << endl;

    cout << "*************output*************" << endl;

    return 0;
}
