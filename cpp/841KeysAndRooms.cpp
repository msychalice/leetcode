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
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        /*
        // DFS
        unordered_set<int> visited;

        function<void(int)> dfs = [&dfs, &rooms, &visited](int root) {
            if (visited.count(root) > 0) {
                return;
            }

            visited.insert(root);
            for (auto neighbor : rooms[root]) {
                dfs(neighbor);
            }
        };

        dfs(0);

        return visited.size() == rooms.size();
        */

        // BFS
        unordered_set<int> visited;
        queue<int> queNeighbor;

        // add the first vertex into queue to trigger the following algorithm
        queNeighbor.push(0);

        while (!queNeighbor.empty()) {
            int queSize = queNeighbor.size();
            for (int i = 0; i < queSize; i++) {
                int neighbor = queNeighbor.front();
                queNeighbor.pop();
                if (visited.count(neighbor) == 0) {
                    visited.insert(neighbor);

                    // push all the neighbors into queue
                    for (auto n : rooms[neighbor]) {
                        queNeighbor.push(n);
                    }
                } else {
                    // empty
                }
            }
        }
        return visited.size() == rooms.size();
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
