#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <forward_list>
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
    int findJudge(int N, vector<vector<int>>& trust) {
        if (N == 1 && trust.size() == 0) {
            return 1;
        }
        vector<int> indegree(N + 1);  // padding 0
        vector<int> outdegree(N + 1);  // padding 0

        for (auto& e : trust) {
            indegree[e[1]]++;
            outdegree[e[0]]++;
        }

        for (int i = 0; i <= N; i++) {
            if (outdegree[i] == 0 && indegree[i] == N - 1) {
                return i;
            }
        }
        return -1;
    }
};

int main(){
    Solution s;
    /*
     */
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
