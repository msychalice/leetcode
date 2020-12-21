#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
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
    int calculate(string s) {
        // @param begin is the position of the first character
        // @return (result number, the position of the first unhandled character
        function<pair<int, int>(int)> calc = [&calc, &s](int begin) {
            stack<int> stkNum;
            // if the first char is a digit, the default sign is +
            char sign = '+';
            int num = 0;
            int cur = begin;

            while (cur < s.size()) {
                char c = s[cur];
                if (isdigit(c)) {
                    num = 10 * num + (c - '0');  // convert string to int
                    cur++;
                    continue;
                }

                if (c == '(') {
                    auto [resultNum, last] = calc(cur + 1);
                    num = resultNum;
                    cur = last;  // move to the next unhandled character
                    continue;
                }

                if (c == ')') {
                    cur++;
                    break;  // calculate the sum and return
                }

                if (c == ' ') {
                    cur++;
                    continue;
                }

                if (!isdigit(c)) {  // c is a sign
                    if (sign == '+') {
                        stkNum.push(num);
                    } else {
                        stkNum.push(-num);
                    }
                    num = 0;
                    sign = c;
                    cur++;
                }
            }

            if (sign == '+') {
                stkNum.push(num);
            } else {
                stkNum.push(-num);
            }

            int output = 0;
            while (!stkNum.empty()) {
                output += stkNum.top();
                stkNum.pop();
            }

            return make_pair(output, cur);
        };

        auto [output, _] = calc(0);
        return output;
    }
};

int main(){
    Solution s;

    cout << s.calculate("1 + 1") << endl;
    cout << s.calculate(" 2-1 + 2 ") << endl;
    cout << s.calculate("(1+(4+5+2)-3)+(6+8)") << endl;

    cout << "*************output*************" << endl;

    return 0;
}
