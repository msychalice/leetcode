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
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (prerequisites.size() == 0) {
            return true;
        }

        vector<forward_list<int>> adjList(numCourses);
        for (auto& e : prerequisites) {
            adjList[e[1]].push_front(e[0]);
        }

        // since numCourses is fixed, we can use vector instead of unordered_set
        vector<bool> visited(numCourses);
        vector<bool> visiting(numCourses);

        function<bool(int)> hasCircle = [&hasCircle, &visited, &visiting,
                                         &adjList](int node) {
            if (visited[node]) {  // already visited
                return false;
            }
            if (visiting[node]) {  // is visiting, has circle
                return true;
            }

            visiting[node] = true;

            for (auto n : adjList[node]) {
                if (hasCircle(n)) {
                    return true;
                }
            }

            visited[node] = true;
            // insert node into the head of the ordered_list(topological sort)
            return false;
        };

        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {  // not visited yet
                if (hasCircle(i)) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<vector<int>> input{{1, 0}};
    cout << s.canFinish(2, input) << endl;
    vector<vector<int>> input1{{1, 0}, {0, 1}};
    cout << s.canFinish(2, input1) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
