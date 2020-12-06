#include <algorithm>
#include <cmath>
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

class LRUCache {
    /**
     * Definition for double-linked list.
     */
    struct DoubleLinkedListNode {
        int key;
        int val;
        DoubleLinkedListNode* prev;
        DoubleLinkedListNode* next;
        DoubleLinkedListNode(int key, int value)
            : key(key), val(value), prev(nullptr), next(nullptr) {}
        DoubleLinkedListNode(int key, int value, DoubleLinkedListNode* prev,
                             DoubleLinkedListNode* next)
            : key(key), val(value), prev(prev), next(next) {}
    };

public:
    LRUCache(int capacity)
        : m_capacity(capacity), m_front(nullptr), m_back(nullptr) {}

    int get(int key) {
        auto it = m_mapListNode.find(key);
        if (it == m_mapListNode.end()) {
            // not found, return -1
            return -1;
        } else {
            // found, return val, move it to the front of the list
            moveToFront(it->second);
            return it->second->val;
        }
    }

    void put(int key, int value) {
        auto it = m_mapListNode.find(key);
        if (it != m_mapListNode.end()) {
            // update the value and move the element to the front
            it->second->val = value;
            moveToFront(it->second);
        } else {
            // create a new element and add it to the front
            DoubleLinkedListNode* oldFront = m_front;
            m_front = new DoubleLinkedListNode(key, value, nullptr, oldFront);
            m_mapListNode.emplace(key, m_front);
            if (oldFront == nullptr) {  // it is the first added element
                m_back = m_front;
            } else {
                oldFront->prev = m_front;
            }

            // remove the back
            if (m_mapListNode.size() > m_capacity) {
                m_mapListNode.erase(m_back->key);
                m_back = m_back->prev;
                delete m_back->next;
                m_back->next = nullptr;
            }
        }
    }

private:
    void moveToFront(DoubleLinkedListNode* node) {
        if (node == m_front) {
            return;
        }

        if (node == m_back) {
            m_back = m_back->prev;
            m_back->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        node->next = m_front;
        m_front->prev = node;
        m_front = node;
    }

    unordered_map<int, DoubleLinkedListNode*> m_mapListNode;
    DoubleLinkedListNode* m_front;
    DoubleLinkedListNode* m_back;

    int m_capacity;
};

int main() {

    cout << "*************output*************" << endl;

    return 0;
}
