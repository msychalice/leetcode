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
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        vector<int> disjointSets(edges.size() + 1, -1);  // padding 0

        // find root
        function<int(int)> f = [&](int v) {
            int root = disjointSets[v];
            // v is a root ,return itself
            if (root < 0) {
                return v;
            }

            while (disjointSets[root] > 0) {
                root = disjointSets[root];
            }
            disjointSets[v] = root;

            return root;
        };

        // union
        // return false, if find a circle
        function<bool(int, int)> u = [&](int v1, int v2) {
            int root1 = f(v1);
            int root2 = f(v2);

            if (root1 < root2) {
                disjointSets[root1] += disjointSets[root2];
                disjointSets[root2] = root1;
            } else if (root1 > root2) {
                disjointSets[root2] += disjointSets[root1];
                disjointSets[root1] = root2;
            } else {
                // find a circle
                return false;
            }
            return true;
        };

        // check whether there is a vertex having two parents,
        // and find the two edges if it does exist.
        unordered_map<int, int> childToParent;
        vector<vector<int>> twoParents;
        for (auto& e : edges) {
            auto it = childToParent.find(e[1]);
            if (it != childToParent.end()) {
                twoParents.push_back(vector<int>{it->second, it->first});
                twoParents.push_back(e);

                // delete the second edge
                e[0] = -1;
                e[1] = -1;
                break;
            } else {
                childToParent.emplace(e[1], e[0]);
            }
        }

        // 1. no vertex having two parents and there is a circle in the graph
        if (twoParents.empty()) {
            for (auto& e : edges) {
                if (!u(e[0], e[1])) {
                    return e;
                }
            }
        } else {
            for (auto& e : edges) {
                if (e[0] == -1) {  // ignore the deleted edge
                    continue;
                }

                if (!u(e[0], e[1])) {
                    // find a circle, return the first edge
                    return twoParents[0];
                }
            }

            // Don't find a circle, and we don't need to double check with
            // adding the previously deleted edge neither.
            // If adding the second edge form a circle, we should return the
            // second edge.
            // If not form a circle, which means adding one of these two edges
            // won't form a circle, in such case return the second edge as well.
            return twoParents[1];
        }

        return vector<int>{};
    }
};

int main(){
    Solution s;
    /*
     */
    vector<vector<int>> input{{1, 2}, {1, 3}, {2, 3}};
    printContainer(s.findRedundantDirectedConnection(input));
    vector<vector<int>> input1{{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 5}};
    printContainer(s.findRedundantDirectedConnection(input1));
    vector<vector<int>> input2{{2, 1}, {3, 1}, {4, 2}, {1, 4}};
    printContainer(s.findRedundantDirectedConnection(input2));
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
