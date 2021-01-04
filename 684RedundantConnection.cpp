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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> disjointSets(edges.size() + 1, -1);  // padding 0

        // find
        function<int(int)> f = [&](int v) {
            int root = disjointSets[v];
            if (root < 0) {
                return root;
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
            // v1 and v2 are both root
            if (root1 < 0 && root2 < 0) {
                disjointSets[v1]--;
                disjointSets[v2] = v1;
                return true;
            }
            // v1 is root, v2 isn't
            if (root1 < 0 && root2 > 0) {
                if (v1 < root2) {
                    disjointSets[v1] += disjointSets[root2];
                    disjointSets[root2] = v1;
                } else if (v1 > root2) {
                    disjointSets[root2] += disjointSets[v1];
                    disjointSets[v1] = root2;
                } else {
                    // find a circle
                    return false;
                }
                return true;
            }
            // v2 is root, v1 isn't
            if (root1 > 0 && root2 < 0) {
                if (root1 < v2) {
                    disjointSets[root1] += disjointSets[v2];
                    disjointSets[v2] = root1;
                } else if (root1 > v2) {
                    disjointSets[v2] += disjointSets[root1];
                    disjointSets[root1] = v2;
                } else {
                    // find a circle
                    return false;
                }
                return true;
            }

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


        for (auto& e : edges) {
            if (!u(e[0], e[1])) {
                return e;
            }
        }

        return vector<int>{};
    }
};

int main(){
    Solution s;
    /*
    vector<vector<int>> input{{1, 2}, {1, 3}, {2, 3}};
    printContainer(s.findRedundantConnection(input));
     */
    vector<vector<int>> input1{{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    printContainer(s.findRedundantConnection(input1));
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
