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
    int superEggDrop(int K, int N) {
        vector<vector<int>> mem(K - 1, vector<int>(N, 0));

        function<int(int, int)> dp = [&dp, &mem](int k, int n) {
            if (k == 1) {
                return n;
            }
            if (n == 0) {
                return 0;
            }

            if (mem[k - 2][n - 1] != 0) {
                return mem[k - 2][n - 1];
            }

            int result = numeric_limits<int>::max();
            int min = 1;
            int max = n + 1;
            while (min < max) {
                int cur = (min + max) / 2;
                int broken = dp(k - 1, cur - 1);
                int notBroken = dp(k, n - cur);
                if (broken < notBroken) {  // move cur rightwards
                    min = cur + 1;
                    result = std::min(result, notBroken + 1);
                } else {
                    max = cur;
                    result = std::min(result, broken + 1);
                }
            }

            mem[k - 2][n - 1] = result;
            return result;
        };

        int output = dp(K, N);

        return output;
    }
};

int main() {
    Solution s;

    auto output = s.superEggDrop(1, 2);

    auto output1 = s.superEggDrop(2, 6);

    auto output2 = s.superEggDrop(3, 14);

    auto output3 = s.superEggDrop(2, 9);

    auto output4 = s.superEggDrop(5, 5000);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;

    return 0;
}
