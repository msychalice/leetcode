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
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cstdint>

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
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr && l2 == nullptr) {
            return nullptr;
        }
        ListNode* root = new ListNode;
        ListNode* cur = root;

        while (l1 != nullptr || l2 != nullptr) {
            if (l1 != nullptr && l2 != nullptr) {
                if (l1->val <= l2->val) {
                    cur->val = l1->val;
                    l1 = l1->next;
                } else {
                    cur->val = l2->val;
                    l2 = l2->next;
                }
            } else if (l1 == nullptr && l2 != nullptr) {
                cur->val = l2->val;
                l2 = l2->next;
            } else if (l1 != nullptr && l2 == nullptr) {
                cur->val = l1->val;
                l1 = l1->next;
            } else if (l1 == nullptr && l2 == nullptr) {
                break;
            }

            if (l1 != nullptr || l2 != nullptr) {
                cur->next = new ListNode;
                cur = cur->next;
            }
        }

        return root;
    }
};

int main(){
    Solution s;

	auto output = s.mergeTwoLists(new ListNode(1, new ListNode(2, new ListNode(4))),
            new ListNode(1, new ListNode(3, new ListNode(4))));
	auto output1 = s.mergeTwoLists(new ListNode, new ListNode);
	auto output2 = s.mergeTwoLists(new ListNode, new ListNode(0));

    cout << "*************output*************" << endl;
    printList(output);
    printList(output1);
    printList(output2);

    return 0;
}
