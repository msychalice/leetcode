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

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        /*
         * recursive
        function<ListNode*(ListNode*, ListNode*)> reverse =
            [&reverse](ListNode* prev, ListNode* cur) ->ListNode* {
                if (cur == nullptr) {
                    return nullptr;
                }

                ListNode* next = cur->next;
                cur->next  = prev;

                if (next == nullptr) {
                    return cur;
                }
                return reverse(cur, next);
            };

        return reverse(nullptr, head);
         */

        //iterative
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* prev = nullptr;
        ListNode* next = head->next;

        while (true) {
            head->next = prev;

            if (next == nullptr) {
                break;
            }

            prev = head;
            head = next;
            next = head->next;
        }

        return head;
    }
};

int main(){
    Solution s;
    ListNode n4(4);
    ListNode n2(2, &n4);
    ListNode n1(1, &n2);
	auto output = s.reverseList(&n1);

    cout << "*************output*************" << endl;
    while (output != nullptr) {
        cout << output->val;
        output = output->next;
        if (output != nullptr) {
            cout << "->";
        }
    }
    cout << endl;

    return 0;
}
