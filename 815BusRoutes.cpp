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
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) {
            return 0;
        }

        unordered_map<int, vector<int>> stopToBus;
        for (int i = 0; i < routes.size(); i++) {
            for (auto stop : routes[i]) {
                stopToBus[stop].push_back(i);
            }
        }

        unordered_set<int> visitedStops;
        unordered_set<int> visitedBuses;
        queue<int> neighborStops;
        neighborStops.push(S);
        visitedStops.insert(S);

        int busCount = 0;

        while (!neighborStops.empty()) {
            int queSize = neighborStops.size();

            busCount++;

            while (queSize--) {
                int curStop = neighborStops.front();
                neighborStops.pop();

                for (auto bus : stopToBus[curStop]) {
                    if (visitedBuses.count(bus) > 0) {
                        continue;
                    }
                    visitedBuses.insert(bus);

                    for (auto stop : routes[bus]) {
                        if (stop == T) {
                            return busCount;
                        }

                        if (visitedStops.count(stop) > 0) {
                            continue;
                        }
                        visitedStops.insert(stop);

                        neighborStops.push(stop);
                    }
                }
            }
        }

        return -1;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<vector<int>> input{{1, 2, 7}, {3, 6, 7}};
    cout << s.numBusesToDestination(input, 1, 6) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }
