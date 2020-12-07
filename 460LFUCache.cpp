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

class LFUCache {
    class LinkedHashSet {
    public:
        void remove(int key) {
            if (size() == 0) {
                return;
            }
            m_lstKey.erase(m_mapKeyIt.find(key)->second);
            m_mapKeyIt.erase(key);
        }

        void add(int key) {
            m_lstKey.push_front(key);
            m_mapKeyIt.insert(make_pair(key, m_lstKey.begin()));
        }

        // return removed key, if it is empty, return -1
        int removeLRU() {
            if (size() == 0) {
                return -1;
            }

            int removedKey = m_lstKey.back();
            m_mapKeyIt.erase(removedKey);
            m_lstKey.pop_back();
            return removedKey;
        }

        int size() const {
            return m_lstKey.size();
        }

    private:
        unordered_map<int, list<int>::iterator> m_mapKeyIt;
        list<int> m_lstKey;
    };

public:
    LFUCache(int capacity) : m_capacity(capacity), m_smallestFreq(0) {}

    int get(int key) {
        // not found, return -1
        auto it = m_mapKeyVal.find(key);
        if (it == m_mapKeyVal.end()) {
            return -1;
        }

        // found, return val, update freq
        addFreq(key);
        return it->second;
    }

    void put(int key, int value) {
        if (m_capacity == 0) {
            return;
        }

        // existing elemnt, update val, update freq
        auto it = m_mapKeyVal.find(key);
        if (it != m_mapKeyVal.end()) {
            it->second = value;
            addFreq(key);
            return;
        }

        // if capacity is full, remove the least frequently used element
        if (m_mapKeyVal.size() == m_capacity) {
            int removedKey =
                m_mapFreqKey.find(m_smallestFreq)->second.removeLRU();
            m_mapKeyFreq.erase(removedKey);
            m_mapKeyVal.erase(removedKey);

            // update m_smallestFreq, how?
            // actually, we don't need to update the m_smallestFreq at this
            // moment, since the m_smallestFreq must be 1 after creating a new
            // element below
        }

        // create new element, freq = 1
        m_mapKeyVal.emplace(key, value);
        m_mapKeyFreq.emplace(key, 1);
        m_mapFreqKey[1].add(key);
        m_smallestFreq = 1;
    }

private:
    void addFreq(int key) {
        int oldFreq = m_mapKeyFreq.find(key)->second;
        int newFreq = oldFreq + 1;
        m_mapFreqKey.find(oldFreq)->second.remove(key);
        m_mapFreqKey[newFreq].add(key);
        m_mapKeyFreq.find(key)->second = newFreq;

        if (m_smallestFreq == oldFreq &&
            m_mapFreqKey.find(oldFreq)->second.size() == 0) {
            m_smallestFreq = newFreq;
        }
    }

    unordered_map<int, int> m_mapKeyVal;
    unordered_map<int, int> m_mapKeyFreq;
    unordered_map<int, LinkedHashSet> m_mapFreqKey;
    int m_capacity;
    int m_smallestFreq;
};

int main() {
    LFUCache l(2);
    l.put(1, 1);
    l.put(2, 2);
    cout << l.get(1) << endl;
    l.put(3, 3);
    cout << l.get(2) << endl;
    cout << l.get(3) << endl;
    l.put(4, 4);
    cout << l.get(1) << endl;
    cout << l.get(3) << endl;
    cout << l.get(4) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
