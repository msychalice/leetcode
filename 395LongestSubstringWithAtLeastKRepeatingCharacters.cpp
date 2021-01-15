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
#include <tuple>
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
    int longestSubstring(string s, int k) {
        int len = s.size();
        if (k == 1) {
            return len;
        }
        if (k > len) {
            return 0;
        }

        int ans = 0;

        // run sliding window for 26 times.
        // each time, there are at most m different characters in window
        for (int m = 1; m <= 26; m++) {
            int j = 0;
            unordered_map<char, int> charCount;
            // how many different characters that appear at least k times
            int qualifiedCharCount = 0;

            for (int i = 0; i < len; i++) {
                // move right pointer as far as possible
                while (j < len && charCount.size() <= m) {
                    charCount[s[j]]++;
                    if (charCount[s[j]] == k) {
                        qualifiedCharCount++;
                    }

                    if (charCount.size() == m && qualifiedCharCount == m) {
                        ans = max(ans, j - i + 1);
                    }

                    j++;
                }

                // is about to move left pointer
                // need to do some clear up
                charCount[s[i]]--;
                if (charCount[s[i]] == k - 1) {
                    qualifiedCharCount--;
                }
                if (charCount[s[i]] == 0) {
                    charCount.erase(s[i]);
                }
            }
        }

        return ans;
    }
};

int main() {
    Solution s;
    /*
     */
    cout << s.longestSubstring("aaabb", 3) << endl;
    cout << s.longestSubstring("ababbc", 2) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
