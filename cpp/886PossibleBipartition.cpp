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
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<vector<int>> adjList(N + 1);  // padding 0
        for (auto& e : dislikes) {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
        }

        vector<int> vertexColor(N + 1);  // default is 0, which means unvisited

        for (int i = 1; i <= N; i++) {
            if (vertexColor[i] != 0) {  // visited
                continue;
            }

            queue<int> queNeighbor;
            int curColor = 1;
            vertexColor[i] = curColor;
            for (auto n : adjList[i]) {
                queNeighbor.push(n);
            }

            while (!queNeighbor.empty()) {
                int queSize = queNeighbor.size();
                curColor = curColor == 1 ? 2 : 1;  // switch color
                for (int j = 0; j < queSize; j++) {
                    int neighbor = queNeighbor.front();
                    queNeighbor.pop();
                    if (vertexColor[neighbor] == 0) {
                        vertexColor[neighbor] = curColor;

                        for (auto n : adjList[neighbor]) {
                            queNeighbor.push(n);
                        }
                    } else {
                        // conflict with existing color
                        if (vertexColor[neighbor] != curColor) {
                            return false;
                        }
                    }
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
    vector<vector<int>> input{{1, 2}, {1, 3}, {2, 4}};
    cout << s.possibleBipartition(4, input) << endl;
    vector<vector<int>> input1{{1, 2}, {1, 3}, {2, 3}};
    cout << s.possibleBipartition(3, input1) << endl;
    vector<vector<int>> input2{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}};
    cout << s.possibleBipartition(5, input2) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
