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
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // if prerequisites.size() is 0, still can not return, have to handle
        // all the nodes, even if they are not connected with each other

        vector<forward_list<int>> adjList(numCourses);
        for (auto& e : prerequisites) {
            adjList[e[1]].push_front(e[0]);
        }

        // since numCourses is fixed, we can use vector instead of unordered_set
        vector<bool> visited(numCourses);
        vector<bool> visiting(numCourses);

        vector<int> res;

        function<bool(int)> hasCircle = [&hasCircle, &visited, &visiting, &res,
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
            res.push_back(node);  // will reverse res
            return false;
        };

        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {  // not visited yet
                if (hasCircle(i)) {
                    return vector<int>{};
                }
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<vector<int>> input{{1, 0}};
    printContainer(s.findOrder(2, input));
    vector<vector<int>> input1{{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    printContainer(s.findOrder(4, input1));
    vector<vector<int>> input2{};
    printContainer(s.findOrder(1, input2));
    vector<vector<int>> input3{};
    printContainer(s.findOrder(2, input3));
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
