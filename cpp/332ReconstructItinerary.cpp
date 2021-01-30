#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <utility>
#include <cstdlib>
#include <limits>
#include <functional>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cstdint>
#include <map>

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

template<class T>
void printMap(const T& container) {
//    return;

    cout << "size " << container.size() << endl;
    if (container.size() == 0) {
        cout << "[]" << endl;
        return;
    }
    for (auto it = container.begin(); it != container.end(); it++) {
        if (it == container.begin()) {
            cout << "[ ";
        }

        cout << "[" << it->first << ", " << it->second << "]";

        if (next(it) == container.end()) {
            cout << " ]" << endl;
        } else {
            cout << ", ";
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
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> output;
        unordered_map<string, vector<string>> unvisitedEdges;

        for (const auto& edge : tickets) {
            const auto& fromVertex = edge[0];
            const auto& toVertex = edge[1];

            auto itMap = unvisitedEdges.find(fromVertex);
            if (itMap != unvisitedEdges.end()) {
                auto& vecEdges = itMap->second;
                vecEdges.push_back(toVertex);
                push_heap(vecEdges.begin(), vecEdges.end(), greater<string>());
            } else {
                unvisitedEdges.emplace(fromVertex, vector<string>{toVertex});
            }
        }

        function<void(const string&)> dfs = [&dfs, &unvisitedEdges, &output](const string& fromVertex) {
            auto itEdges = unvisitedEdges.find(fromVertex);

            while (itEdges != unvisitedEdges.end() && !itEdges->second.empty()) {
                auto& vecEdges = itEdges->second;
                auto edge = vecEdges.front();
                pop_heap(vecEdges.begin(), vecEdges.end(), greater<string>());
                vecEdges.pop_back();
                dfs(edge);
            }

            output.push_back(fromVertex);
        };

        dfs("JFK");

        return vector<string>(output.rbegin(), output.rend());
    }
};

int main(){
    Solution s;

    vector<vector<string>> input{{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
	auto output = s.findItinerary(input);

    vector<vector<string>> input1{{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
	auto output1 = s.findItinerary(input1);

    vector<vector<string>> input2{{"EZE","AXA"},{"TIA","ANU"},{"ANU","JFK"},{"JFK","ANU"},{"ANU","EZE"},
        {"TIA","ANU"},{"AXA","TIA"},{"TIA","JFK"},{"ANU","TIA"},{"JFK","TIA"}};
	auto output2 = s.findItinerary(input2);

    cout << "*************output*************" << endl;
    printContainer(output);
    printContainer(output1);
    printContainer(output2);

    return 0;
}
