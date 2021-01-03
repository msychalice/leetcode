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
    bool isBipartite(vector<vector<int>>& graph) {
        if (graph.empty()) {
            return true;
        }
        // default is 0, means uncolored
        constexpr int Red = 1;
        constexpr int Green = 2;
        vector<int> vertexColor(graph.size());

        for (int i = 0; i < graph.size(); i++) {
            if (vertexColor[i] != 0) {  // visited
                continue;
            }

            int curColor = Red;
            vertexColor[i] = curColor;
            queue<int> queNeighbor;
            for (auto& n : graph[i]) {
                queNeighbor.push(n);
            }

            while (!queNeighbor.empty()) {
                curColor = curColor == Red ? Green : Red;
                int queSize = queNeighbor.size();
                for (int j = 0; j < queSize; j++) {
                    int vertex = queNeighbor.front();
                    queNeighbor.pop();
                    if (vertexColor[vertex] == 0) {
                        vertexColor[vertex] = curColor;

                        // add it's neighbors into queue
                        for (auto& n : graph[vertex]) {
                            queNeighbor.push(n);
                        }
                    } else {
                        // conflict with existing color
                        if (vertexColor[vertex] != curColor) {
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
    vector<vector<int>> input{{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    cout << s.isBipartite(input) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
