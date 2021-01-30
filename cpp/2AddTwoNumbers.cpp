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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int liftedNum = 0;
        ListNode* root = new ListNode;
        ListNode* cur = root;
        
        while (l1 != nullptr || l2 != nullptr) {
            int total = (l1 != nullptr ? l1->val : 0) + (l2 != nullptr ? l2->val : 0) + liftedNum;
            cur->val = total % 10;
            liftedNum = total / 10;
                
            l1 = l1 != nullptr ? l1->next : nullptr;
            l2 = l2 != nullptr ? l2->next : nullptr;

            if (l1 == nullptr && l2 == nullptr) {
                if (liftedNum > 0) {
                    cur->next = new ListNode(liftedNum);
                }
            } else {
                cur->next = new ListNode;
                cur = cur->next;
            }
        }

        return root;
    }
};

int main(){
    Solution s;
    ListNode n1(9);
    ListNode n2(9, &n1);
    ListNode n3(9, &n2);
    ListNode n4(9, &n3);
    ListNode n5(9, &n4);
    ListNode n6(9, &n5);
    ListNode n7(9, &n6);
    ListNode n8(9);
    ListNode n9(9, &n8);
    ListNode n10(9, &n9);
    ListNode n11(9, &n10);
	auto output = s.addTwoNumbers(&n7, &n11);
    printList(&n7);
    printList(&n11);
    printList(output);

    cout << "*************output*************" << endl;

    return 0;
}
