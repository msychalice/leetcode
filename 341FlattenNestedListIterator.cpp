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

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "#";
        }

        stringstream ss;

        function<void(TreeNode*)> serializeTree = [&serializeTree,
                                                   &ss](TreeNode* node) {
            if (node == nullptr) {
                ss << "#,";
                return;
            }

            ss << node->val << ",";
            serializeTree(node->left);
            serializeTree(node->right);
        };

        serializeTree(root);

        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == 0) {
            return nullptr;
        }

        int curIndex = 0;
        function<TreeNode*()> deserializeTree = [&deserializeTree, &data,
                                                 &curIndex]() -> TreeNode* {
            int endIndex = data.find_first_of(',', curIndex);
            string nodeData = data.substr(curIndex, endIndex - curIndex);
            /*
            cout << "cur " << curIndex << " end " << endIndex << " data "
                 << nodeData << endl;
                 */

            curIndex = endIndex + 1;

            if (nodeData == "#") {
                return nullptr;
            }

            TreeNode* root = new TreeNode(stoi(nodeData));

            root->left = deserializeTree();
            root->right = deserializeTree();
            return root;
        };

        return deserializeTree();
    }
};

/*
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a
    // nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a
    // single integer The result is undefined if this NestedInteger holds a
    // nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a
    // nested list The result is undefined if this NestedInteger holds a single
    // integer
    const vector<NestedInteger>& getList() const;
};
*/

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger>& nestedList)
        : m_data(nestedList), m_curIndex(0) {
        for (int i = 0; i < nestedList.size(); i++) {
            auto& ni = nestedList[i];
            if (!ni.isInteger()) {
                m_iterators.emplace(i, new NestedIterator(ni.getList()));
            }
        }
        // the initial m_curIndex is 0, may be a empty list that doesn't have
        // data
        checkCurIndex();
    }

    int next() {
        auto& ni = m_data[m_curIndex];
        if (ni.isInteger()) {
            int result = ni.getInteger();
            m_curIndex++;
            checkCurIndex();
            return result;
        }

        auto it = m_iterators[m_curIndex];
        int result = it->next();
        checkCurIndex();
        return result;
    }

    bool hasNext() {
        return m_curIndex < m_data.size();
    }

private:
    // check cur index, if it doesn't have data, move it to the next element
    // that has data
    void checkCurIndex() {
        while (hasNext() && !m_data[m_curIndex].isInteger() &&
               !m_iterators[m_curIndex]->hasNext()) {
            m_curIndex++;
        }
    }

    vector<NestedInteger>& m_data;
    int m_curIndex;
    unordered_map<int, NestedIterator*> m_iterators;
};

int main() {
    NestedIterator i(nestedList);
    while (i.hasNext()) {
        cout << i.next();
    }

    cout << "*************output*************" << endl;

    return 0;
}
