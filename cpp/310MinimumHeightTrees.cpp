#include <algorithm>
#include <cctype>
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
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return vector<int>{0};
        }
        if (n == 2) {
            return vector<int>{edges[0][0], edges[0][1]};
        }

        // build adjacency sets
        unordered_map<int, unordered_set<int>> adjSet;
        for (auto& e : edges) {
            adjSet[e[0]].insert(e[1]);
            adjSet[e[1]].insert(e[0]);
        }

        queue<int> quePeripheral;
        // add all peripheral nodes into queue
        for (auto& pair : adjSet) {
            if (pair.second.size() == 1) {
                quePeripheral.push(pair.first);
            }
        }

        while (!quePeripheral.empty()) {
            int peripheralNodeCount = quePeripheral.size();
            for (int i = 0; i < peripheralNodeCount; i++) {
                int peripheralNode = quePeripheral.front();
                quePeripheral.pop();

                int adjNode = *adjSet[peripheralNode].begin();
                adjSet.erase(peripheralNode);
                adjSet[adjNode].erase(peripheralNode);

                // become a peripheral node
                if (adjSet[adjNode].size() == 1) {
                    quePeripheral.push(adjNode);
                }
            }

            if (adjSet.size() <= 2) {
                break;
            }
        }

        vector<int> res;
        // the left nodes are the centroids
        for (auto& centroid : adjSet) {
            res.push_back(centroid.first);
        }
        return res;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<vector<int>> input{{1, 0}, {1, 2}, {1, 3}};
    printContainer(s.findMinHeightTrees(4, input));
    vector<vector<int>> input1{{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}};
    printContainer(s.findMinHeightTrees(6, input1));
    vector<vector<int>> input2{};
    printContainer(s.findMinHeightTrees(1, input2));
    vector<vector<int>> input3{{0, 1}};
    printContainer(s.findMinHeightTrees(2, input3));
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
