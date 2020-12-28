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
    int lastStoneWeight(vector<int>& stones) {
        if (stones.size() == 1) {
            return stones[0];
        }

        make_heap(stones.begin(), stones.end());

        int output = 0;
        while (!stones.empty()) {
            int firstStone = 0;
            int secondStone = 0;
            firstStone = stones.front();
            pop_heap(stones.begin(), stones.end());
            stones.pop_back();

            if (stones.empty()) {
                output = firstStone;
                break;
            }

            secondStone = stones.front();
            pop_heap(stones.begin(), stones.end());
            stones.pop_back();

            int smashedStone = abs(firstStone - secondStone);
            if (smashedStone != 0) {
                stones.push_back(smashedStone);
                push_heap(stones.begin(), stones.end());
            }
        }
        return output;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<int> input{2, 7, 4, 1, 8, 1};
    cout << s.lastStoneWeight(input) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
