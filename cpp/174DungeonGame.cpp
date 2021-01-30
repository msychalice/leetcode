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
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        print2DimVec(dungeon);
        /* getting wrong answer
        vector<vector<pair<int, int>>> dp(
            dungeon.size(), vector<pair<int, int>>(dungeon[0].size()));

        function<pair<int, int>(pair<int, int>, int)> calc =
            [](pair<int, int> prev, int curGrid) {
                if (curGrid >= 0) {  // orb
                    prev.second += curGrid;
                    return prev;
                }

                // demon
                // orb will deduct the damage
                int realDamage = prev.second + curGrid;
                prev.first += realDamage < 0 ? realDamage : 0;
                prev.second = realDamage > 0 ? realDamage : 0;
                return prev;
            };

        for (int i = 0; i < dungeon.size(); i++) {
            for (int j = 0; j < dungeon[0].size(); j++) {
                bool hasLeft = false;
                auto leftGrid = make_pair(0, 0);
                bool hasUp = false;
                auto upGrid = make_pair(0, 0);
                if (j > 0) {  // has left grid
                    hasLeft = true;
                    leftGrid = dp[i][j - 1];
                }
                if (i > 0) {  // has up grid
                    hasUp = true;
                    upGrid = dp[i - 1][j];
                }

                if (hasLeft && hasUp) {
                    auto chooseLeft = calc(leftGrid, dungeon[i][j]);
                    auto chooseUp = calc(upGrid, dungeon[i][j]);
                    if (chooseLeft.first > chooseUp.first ||
                        (chooseLeft.first == chooseUp.first &&
                         chooseLeft.second > chooseUp.second)) {
                        dp[i][j] = chooseLeft;
                    } else {
                        dp[i][j] = chooseUp;
                    }
                } else if (hasLeft && !hasUp) {
                    dp[i][j] = calc(leftGrid, dungeon[i][j]);
                } else if (!hasLeft && hasUp) {
                    dp[i][j] = calc(upGrid, dungeon[i][j]);
                } else {  // base case
                    dp[i][j].first = dungeon[i][j] < 0 ? dungeon[i][j] : 0;
                    dp[i][j].second = dungeon[i][j] > 0 ? dungeon[i][j] : 0;
                }
            }
        }

        for (int i = 0; i < dp.size(); i++) {
            for (int j = 0; j < dp[0].size(); j++) {
                cout << "{" << dp[i][j].first << "," << dp[i][j].second << "},";
            }
            cout << endl;
        }

        return -dp[dungeon.size() - 1][dungeon[0].size() - 1].first + 1;
        */

        int row = dungeon.size();
        int col = dungeon[0].size();
        vector<vector<int>> dp(
            row + 1, vector<int>(col + 1, numeric_limits<int>::max()));

        // they are not base cases, but they can make calculating
        // dp[row-1][col-1] much easier
        dp[row][col - 1] = 1;
        dp[row - 1][col] = 1;

        for (int i = dungeon.size() - 1; i >= 0; i--) {
            for (int j = dungeon[0].size() - 1; j >= 0; j--) {
                dp[i][j] =
                    max(1, min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j]);
            }
        }

        return dp[0][0];
    }
};

int main(){
    Solution s;
    /*
     */
    vector<vector<int>> input{{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
    cout << s.calculateMinimumHP(input) << endl;
    vector<vector<int>> input1{{1,-3,3},{0,-2,0},{-3,-3,-3}};
    cout << s.calculateMinimumHP(input1) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
    }
