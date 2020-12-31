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
    int maximalSquare(vector<vector<char>>& matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> dp(row, vector<int>(col));

        // base case
        // dp[row-1][i]
        // dp[i][col-1]
        for (int i = 0; i < row; i++) {
            dp[i][col - 1] = matrix[i][col - 1] == '1' ? 1 : 0;
        }
        for (int i = 0; i < col; i++) {
            dp[row - 1][i] = matrix[row - 1][i] == '1' ? 1 : 0;
        }

        for (int i = row - 2; i >= 0; i--) {
            for (int j = col - 2; j >= 0; j--) {
                dp[i][j] = matrix[i][j] == '1' ? 1 : 0;

                // it's possible to form a larger square
                if (dp[i][j] == 1 && dp[i + 1][j + 1] > 0) {
                    // maximum len of the square starting at (i,j)
                    int len = min(min(sqrt(dp[i + 1][j]), sqrt(dp[i][j + 1])),
                                  sqrt(dp[i + 1][j + 1])) +
                              1;
                    dp[i][j] = len * len;
                }
            }
        }

        print2DimVec(dp);

        int output = 0;
        for (auto& r : dp) {
            for (auto& c : r) {
                output = max(output, c);
            }
        }

        return output;
    }
};

int main(){
    Solution s;
    /*
    vector<vector<char>> input{{'1', '0', '1', '0', '0'},
                               {'1', '0', '1', '1', '1'},
                               {'1', '1', '1', '1', '1'},
                               {'1', '0', '0', '1', '0'}};
    cout << s.maximalSquare(input) << endl;
    vector<vector<char>> input1{{'0', '1'}, {'1', '0'}};
    cout << s.maximalSquare(input1) << endl;
    vector<vector<char>> input2{{'0'}};
    cout << s.maximalSquare(input2) << endl;
     */
    vector<vector<char>> input3{{'1', '1', '1', '1', '1', '1', '1', '1'},
                                {'1', '1', '1', '1', '1', '1', '1', '0'},
                                {'1', '1', '1', '1', '1', '1', '1', '0'},
                                {'1', '1', '1', '1', '1', '0', '0', '0'},
                                {'0', '1', '1', '1', '1', '0', '0', '0'}};
    cout << s.maximalSquare(input3) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
    }
