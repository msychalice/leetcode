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
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        vector<vector<int>> adjList(s.size());
        for (auto& e : pairs) {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
        }

        unordered_set<int> visited;
        string strConnectedVertices;
        vector<int> vecConnectedVertices;

        function<void(int)> dfs = [&](int root) {
            if (visited.count(root) > 0) {
                return;
            }

            visited.insert(root);
            strConnectedVertices += s[root];
            vecConnectedVertices.push_back(root);

            for (auto neighbor : adjList[root]) {
                dfs(neighbor);
            }
        };

        for (int i = 0; i < s.size(); i++) {
            if (visited.count(i) > 0) {
                continue;
            }

            strConnectedVertices.clear();
            vecConnectedVertices.clear();
            dfs(i);

            sort(strConnectedVertices.begin(), strConnectedVertices.end());
            sort(vecConnectedVertices.begin(), vecConnectedVertices.end());
            for (int j = 0; j < vecConnectedVertices.size(); j++) {
                s[vecConnectedVertices[j]] = strConnectedVertices[j];
            }
        }
        return s;
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
