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
    vector<int> plusOne(vector<int>& digits) {
        vector<int> output(digits.crbegin(), digits.crend());

        int liftedNum = 0;
        output[0] += 1;
        for (auto& n : output) {
            n += liftedNum;
            liftedNum = n > 9 ? n - 9 : 0;
            n = n % 10;
        }

        if (liftedNum > 0) {
            output.push_back(liftedNum);
        }

        reverse(output.begin(), output.end());
        
        return output;
    }
};

int main(){
    Solution s;

    vector<int> input{1,2,3};
	auto output = s.plusOne(input);

    vector<int> input1{4, 3, 2, 1};
	auto output1 = s.plusOne(input1);

    vector<int> input2{0};
	auto output2 = s.plusOne(input2);

    vector<int> input3{9, 9};
	auto output3 = s.plusOne(input3);

    cout << "*************output*************" << endl;
    printContainer(output);
    printContainer(output1);
    printContainer(output2);
    printContainer(output3);

    return 0;
}
