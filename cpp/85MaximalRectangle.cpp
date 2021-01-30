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
    int maximalRectangle(vector<vector<char>>& matrix) {
        int row = matrix.size();
        if (row == 0) {
            return 0;
        }
        int col = matrix[0].size();

        int output = 0;
        // heights[col] is the padding height to faciliatethe calculation of
        // largest rectangle in histogram
        vector<int> heights(col + 1);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
            }
            output = max(output, largestRectInHistogram(heights));
        }
        return output;
    }

    int largestRectInHistogram(vector<int>& heights) {
        int col = heights.size();
        stack<int> stk;

        int output = 0;
        for (int i = 0; i < col; i++) {
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
    vector<vector<char>> input{{'1', '0', '1', '0', '0'},
                               {'1', '0', '1', '1', '1'},
                               {'1', '1', '1', '1', '1'},
                               {'1', '0', '0', '1', '0'}};
    cout << s.maximalRectangle(input) << endl;
    /*
    vector<vector<char>> input1{{'0', '1'}, {'1', '0'}};
    cout << s.maximalRectangle(input1) << endl;
    vector<vector<char>> input2{{'0'}};
    cout << s.maximalRectangle(input2) << endl;
    vector<vector<char>> input3{{'1', '1', '1', '1', '1', '1', '1', '1'},
                                {'1', '1', '1', '1', '1', '1', '1', '0'},
                                {'1', '1', '1', '1', '1', '1', '1', '0'},
                                {'1', '1', '1', '1', '1', '0', '0', '0'},
                                {'0', '1', '1', '1', '1', '0', '0', '0'}};
    cout << s.maximalRectangle(input3) << endl;
     */

    cout << "*************output*************" << endl;

    return 0;
}
