#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <random>
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
    Solution(vector<int>& nums) : m_nums(nums) {}

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return m_nums;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> output(m_nums);
        random_device rd;   // obtain a random number from hardware
        mt19937 gen(rd());  // seed the generator

        for (int i = 0; i < output.size() - 1; i++) {
            // get random [i, output.size()-1]
            uniform_int_distribution<int> distribution(i, output.size() - 1);
            swap(output[i], output[distribution(gen)]);
        }

        return output;
    }

private:
    vector<int>& m_nums;
};

int main(){

    cout << "*************output*************" << endl;

    return 0;
}
