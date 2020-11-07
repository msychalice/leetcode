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
#include <map>

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
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) {
            return 0;
        }

        int output = -1;

        vector<int> cachedResults(amount + 1, numeric_limits<int>::max());
        for (int cur = 1; cur <= amount; cur++) {
            int result = numeric_limits<int>::max();
            for (int coin : coins) {
                if (cur == coin) {
                    result = 1;
                } else if (cur < coin) {
                    // empty
                } else {
                    if (cachedResults[cur-coin] < numeric_limits<int>::max()) {
                        int newResult = cachedResults[cur-coin] + 1;
                        result = min(result, newResult);
                    }
                }
            }

            cachedResults[cur] = result;
        }

        if (cachedResults[amount] != numeric_limits<int>::max()) {
            output = cachedResults[amount];
        }

        return output;
    }
};

int main(){
    Solution s;

    vector<int> input{1,2,5};
	auto output = s.coinChange(input, 11);

    vector<int> input1{2};
	auto output1 = s.coinChange(input1, 3);

    vector<int> input2{1};
	auto output2 = s.coinChange(input2, 0);

    vector<int> input3{1};
	auto output3 = s.coinChange(input3, 1);

    vector<int> input4{1};
	auto output4 = s.coinChange(input4, 2);

    vector<int> input5{186, 419, 83, 408};
	auto output5 = s.coinChange(input5, 6249);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;
    cout << output5 << endl;

    return 0;
}
