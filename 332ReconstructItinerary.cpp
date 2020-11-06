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
        vector<string> vecVertices;
        set<string> setVertices;
        for (const auto& edge : tickets) {
            setVertices.insert(edge[0]);
            setVertices.insert(edge[1]);
        }

        //index of "JFK"
        int startVertexIndex = distance(setVertices.begin(), setVertices.find("JFK"));

        unordered_map<string, int> name2Index;
        for (auto& vertex : setVertices) {
            vecVertices.push_back(move(vertex));
            name2Index.emplace(vecVertices[vecVertices.size()-1], vecVertices.size()-1);
        }

        unordered_map<int, map<int, int>> mapNeighbors; //can have multiple identical tickets, use map to store count
        for (const auto& edge: tickets) {
            int startVertexIndex = name2Index[edge[0]];
            int endVertexIndex = name2Index[edge[1]];

            auto it = mapNeighbors.find(startVertexIndex);
            if (it != mapNeighbors.end()) {
                auto& neighborCount = it->second;
                auto itCount = neighborCount.find(endVertexIndex);
                if (itCount != neighborCount.end()) {
                    itCount->second++;
                } else {
                    neighborCount.emplace(endVertexIndex, 1);
                }
            } else {
                mapNeighbors.emplace(startVertexIndex, map<int, int>{{endVertexIndex, 1}});
            }
        }

        int vertexCount = vecVertices.size();
        auto visited = vector<vector<int>>(vertexCount, vector<int>(vertexCount, 0));
        deque<int> deqPath;

        function<void(int)> dfs = [&dfs, &visited, &mapNeighbors, &deqPath](int vertexIndex) {
            for (const auto& neighbor : mapNeighbors[vertexIndex]) {
                int neighborIndex = neighbor.first;
                int neighborCount = neighbor.second;
                if (visited[vertexIndex][neighborIndex] < neighborCount) {
                    visited[vertexIndex][neighborIndex]++;
                    dfs(neighborIndex);
                }
            }

            deqPath.push_front(vertexIndex);
        };

        dfs(startVertexIndex);

        vector<string> output;
        for (const auto& index : deqPath) {
            output.push_back(vecVertices[index]);
        }

        return output;
    }
};

int main(){
    Solution s;

    /*
    vector<vector<string>> input{{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
	auto output = s.findItinerary(input);

    vector<vector<string>> input1{{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
	auto output1 = s.findItinerary(input1);
    */

    vector<vector<string>> input2{{"EZE","AXA"},{"TIA","ANU"},{"ANU","JFK"},{"JFK","ANU"},{"ANU","EZE"},
        {"TIA","ANU"},{"AXA","TIA"},{"TIA","JFK"},{"ANU","TIA"},{"JFK","TIA"}};
	auto output2 = s.findItinerary(input2);

    cout << "*************output*************" << endl;
    /*
    printContainer(output);
    printContainer(output1);
    */
    printContainer(output2);

    return 0;
}
