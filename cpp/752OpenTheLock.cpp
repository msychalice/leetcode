#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
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
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        auto getNeighbors = [](int n) {
            vector<int> neighbors;
            int n1 = n % 10;
            int n2 = n % 100 / 10;
            int n3 = n % 1000 / 100;
            int n4 = n / 1000;

            auto getNextDigit = [](int i) {
                return (i + 1) % 10;
            };
            auto getPrevDigit = [](int i) {
                return i - 1 < 0 ? 9 : i - 1;
            };
            auto getNeighbor = [](int n1, int n2, int n3, int n4) {
                return n1 + n2 * 10 + n3 * 100 + n4 * 1000;
            };

            neighbors.push_back(getNeighbor(getNextDigit(n1), n2, n3, n4));
            neighbors.push_back(getNeighbor(getPrevDigit(n1), n2, n3, n4));
            neighbors.push_back(getNeighbor(n1, getNextDigit(n2), n3, n4));
            neighbors.push_back(getNeighbor(n1, getPrevDigit(n2), n3, n4));
            neighbors.push_back(getNeighbor(n1, n2, getNextDigit(n3), n4));
            neighbors.push_back(getNeighbor(n1, n2, getPrevDigit(n3), n4));
            neighbors.push_back(getNeighbor(n1, n2, n3, getNextDigit(n4)));
            neighbors.push_back(getNeighbor(n1, n2, n3, getPrevDigit(n4)));

            return neighbors;
        };

        unordered_set<int> setDeadends;
        for (auto& s : deadends) {
            setDeadends.insert(stoi(s));
        }

        int intTarget = stoi(target);
        queue<int> que;
        unordered_set<int> visited;
        que.push(0);
        visited.insert(0);
        int step = 0;

        while (!que.empty()) {
            int queSize = que.size();
            for (int i = 0; i < queSize; i++) {
                int cur = que.front();
                que.pop();
                if (setDeadends.find(cur) != setDeadends.end()) {
                    continue;
                }

                if (cur == intTarget) {
                    return step;
                }

                vector<int> neighbors = getNeighbors(cur);
                for (auto n : neighbors) {
                    if (visited.find(n) != visited.end()) {
                        continue;
                    }

                    que.push(n);
                    visited.insert(n);
                }
            }

            step++;
        }

        return -1;
    }
};

int main() {
    Solution s;

    vector<string> input{"0201", "0101", "0102", "1212", "2002"};
    auto output = s.openLock(input, "0202");

    vector<string> input1{"8888"};
    auto output1 = s.openLock(input1, "0009");

    vector<string> input2{"8887", "8889", "8878", "8898",
                          "8788", "8988", "7888", "9888"};
    auto output2 = s.openLock(input2, "8888");

    vector<string> input3{"0000"};
    auto output3 = s.openLock(input3, "8888");

    vector<string> input4{"2110", "0202", "1222", "2221", "1010"};
    auto output4 = s.openLock(input4, "2010");

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;

    return 0;
}
