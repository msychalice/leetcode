#include <algorithm>
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
    int preimageSizeFZF(int K) {
        function<int64_t(int64_t)> trailingZeroes = [](int64_t n) {
            int64_t output = 0;
            for (int64_t i = 1; n >= static_cast<int64_t>(pow(5, i)); i++) {
                output += n / static_cast<int64_t>(pow(5, i));
            }
            return output;
        };

        // Given K <= 10^9, trailingZeroes(2 * int::max) > 10^9,
        // we can safely set hi = 2 * int::max
        function<int64_t(int)> leftBound = [&trailingZeroes](int K) {
            int64_t lo = 0;
            int64_t hi = 2 * static_cast<int64_t>(numeric_limits<int>::max());

            while (lo < hi) {
                int64_t mid = (lo + hi) / 2;

                int curK = trailingZeroes(mid);
                if (curK == K) {
                    if (mid == lo || trailingZeroes(mid - 1) < curK) {
                        return mid;
                    }
                    hi = mid;
                } else if (curK < K) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
            return lo;
        };

        function<int64_t(int)> rightBound = [&trailingZeroes](int K) {
            int64_t lo = 0;
            int64_t hi = 2 * static_cast<int64_t>(numeric_limits<int>::max());

            while (lo < hi) {
                int64_t mid = (lo + hi) / 2;

                int curK = trailingZeroes(mid);
                if (curK == K) {
                    if (mid == hi - 1 || trailingZeroes(mid + 1) > curK) {
                        return mid;
                    }
                    lo = mid + 1;
                } else if (curK < K) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
            return lo;
        };

        int left = leftBound(K);
        int right = rightBound(K);

        return right > left ? right - left + 1 : 0;
    }
};

int main(){
    Solution s;

    cout << s.preimageSizeFZF(0) << endl;
    cout << s.preimageSizeFZF(5) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
