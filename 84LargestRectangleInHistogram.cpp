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
    int largestRectangleArea(vector<int>& heights) {
        if (heights.size() == 0) {
            return 0;
        }
        heights.push_back(0);  // add a padding 0 to faciliate the calculation
                               // of the real last height

        stack<int> stk;  // monotonic non-decreasing stack
        int output = 0;

        for (int i = 0; i < heights.size(); i++) {
            while (!stk.empty()) {
                int indexTop = stk.top();
                if (heights[i] < heights[indexTop]) {
                    int height = heights[indexTop];
                    stk.pop();
                    int rightBoundary = i;
                    int leftBoundary = stk.empty() ? -1 : stk.top();
                    int width = rightBoundary - leftBoundary - 1;
                    output = max(output, width * height);
                } else {
                    break;
                }
            }
            stk.push(i);
        }
        return output;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<int> input{2, 1, 5, 6, 2, 3};
    cout << s.largestRectangleArea(input) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
