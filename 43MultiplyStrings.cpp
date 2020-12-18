#include <algorithm>
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
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

        // set the larger num at left
        string left = num1.size() >= num2.size() ? num1 : num2;
        string right = num1.size() >= num2.size() ? move(num2) : move(num1);

        auto getDigit = [](char c) {
            return static_cast<int>(c - '0');
        };
        auto getIntermediateResult = [&left, &getDigit](int rightDigit,
                                                        int digitIndex) {
            stringstream ss;
            for (int i = 2; i <= digitIndex; i++) {
                ss << 0;
            }

            int advancedDigit = 0;
            for (int i = left.size() - 1; i >= 0; i--) {
                int sumDigit = getDigit(left[i]) * rightDigit + advancedDigit;
                advancedDigit = sumDigit / 10;
                sumDigit = sumDigit % 10;
                ss << sumDigit;
            }
            if (advancedDigit > 0) {
                ss << advancedDigit;
            }

            string output = ss.str();
            reverse(output.begin(), output.end());
            return output;
        };

        vector<string> vecIntermediateResults;
        for (int i = 1; i <= right.size(); i++) {
            vecIntermediateResults.emplace_back(
                getIntermediateResult(getDigit(right[right.size() - i]), i));
        }

        stringstream ss;
        int advancedDigit = 0;
        for (int i = 1; i <= vecIntermediateResults.back().size(); i++) {
            int sumDigit = advancedDigit;
            advancedDigit = 0;
            for (auto& str : vecIntermediateResults) {
                int index = str.size() - i;
                if (index < 0) {
                    continue;
                }

                sumDigit += getDigit(str[index]);
                advancedDigit += sumDigit / 10;
                sumDigit = sumDigit % 10;
            }
            ss << sumDigit;
        }

        if (advancedDigit > 0) {
            ss << advancedDigit;
        }

        string output = ss.str();
        reverse(output.begin(), output.end());
        return output;
    }
};

int main(){
    Solution s;

    cout << s.multiply("2", "3") << endl;
    cout << s.multiply("123", "456") << endl;

    cout << "*************output*************" << endl;

    return 0;
}
