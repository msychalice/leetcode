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
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int row = matrix.size();
        int col = matrix[0].size();

        function<int(vector<int>&, int)> maxSubarraySumNoLargerThanK =
            [](vector<int>& nums, int k) {
                // Since we only need to find the value no larger
                // than k, it is unnecessary to use multiset, even if
                // it's possible to have identical values.
                // Besides the behavior of lower_bound in multiset is different
                // than in set.
                //
                // Adding {0} is to faciliate finding the presum that is equal
                // to k
                set<int> s = {0};

                int preSum_i = 0;
                int res = numeric_limits<int>::min();  // preSum can be negative
                for (auto n : nums) {
                    preSum_i += n;
                    auto it = s.lower_bound(preSum_i - k);
                    // (preSum_i - *it) is the sum of subarray [i,j]
                    if (it != s.end()) {
                        res = max(res, preSum_i - *it);
                    }
                    s.insert(preSum_i);
                }

                return res;
            };

        int res = numeric_limits<int>::min();  // preSum can be negative

        if (row < col) {  // compress vertically
            for (int n = 0; n < row; n++) {
                vector<int> compressed(col);
                for (int i = n; i < row; i++) {
                    for (int j = 0; j < col; j++) {
                        compressed[j] += matrix[i][j];
                    }

                    res = max(res, maxSubarraySumNoLargerThanK(compressed, k));
                }
            }
        } else {  // compress horizontally
            for (int n = 0; n < col; n++) {
                vector<int> compressed(row);
                for (int i = n; i < col; i++) {
                    for (int j = 0; j < row; j++) {
                        compressed[j] += matrix[j][i];
                    }

                    res = max(res, maxSubarraySumNoLargerThanK(compressed, k));
                }
            }
        }

        return res;
    }
};

int main(){
    Solution s;
    /*
    vector<vector<int>> input{{1, 0, 1}, {0, -2, 3}};
    cout << s.maxSumSubmatrix(input, 2) << endl;
     */
    vector<vector<int>> input1{{2, 2, -1}};
    cout << s.maxSumSubmatrix(input1, 0) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
