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
    vector<int> diffWaysToCompute(string input) {
        function<vector<int>(int, int)> find = [&find, &input](int begin,
                                                               int end) {
            vector<int> output;

            // base case, doesn't have any operator
            auto found = input.find_first_of("+-*", begin);
            if (found == string::npos || found >= end) {
                output.push_back(stoi(input.substr(begin, end - begin + 1)));
                return output;
            }

            while (true) {
                if (found == string::npos || found >= end) {
                    return output;
                }

                auto leftResult = find(begin, found - 1);
                auto rightResult = find(found + 1, end);

                if (input[found] == '*') {
                    for (auto lr : leftResult) {
                        for (auto rr : rightResult) {
                            output.push_back(lr * rr);
                        }
                    }
                } else if (input[found] == '+') {
                    for (auto lr : leftResult) {
                        for (auto rr : rightResult) {
                            output.push_back(lr + rr);
                        }
                    }
                } else if (input[found] == '-') {
                    for (auto lr : leftResult) {
                        for (auto rr : rightResult) {
                            output.push_back(lr - rr);
                        }
                    }
                }

                found = input.find_first_of("+-*", found + 1);
            }
        };

        return find(0, input.size() - 1);
    }
};

int main(){
    Solution s;

    cout << "*************output*************" << endl;

    return 0;
}
