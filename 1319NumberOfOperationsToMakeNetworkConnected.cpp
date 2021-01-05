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
    int makeConnected(int n, vector<vector<int>>& connections) {
        vector<int> parents(n, -1);

        function<int(int)> f = [&](int vertex) {
            int root = parents[vertex];
            if (root < 0) {
                return vertex;
            }

            while (parents[root] >= 0) {
                root = parents[root];
            }
            parents[vertex] = root;
            return root;
        };

        function<bool(int, int)> u = [&](int v1, int v2) {
            if (v1 > v2) {
                return u(v2, v1);
            }

            int root1 = f(v1);
            int root2 = f(v2);
            if (root1 < root2) {
                // merge root2 into root1
                parents[root1] += parents[root2];
                parents[root2] = root1;
            } else if (root1 > root2) {
                // merge root1 into root2
                parents[root2] += parents[root1];
                parents[root1] = root2;
            } else {
                // will form a circle
                return false;
            }
            return true;
        };

        int redundantCableCount = 0;
        for (auto& e : connections) {
            if (!u(e[0], e[1])) {
                redundantCableCount++;
            }
        }

        int disjointSetCount = 0;
        for (auto r : parents) {
            if (r < 0) {
                disjointSetCount++;
            }
        }

        return redundantCableCount >= disjointSetCount - 1
                   ? disjointSetCount - 1
                   : -1;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<vector<int>> input{{0, 1}, {0, 2}, {1, 2}};
    cout << s.makeConnected(4, input) << endl;
    vector<vector<int>> input1{{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}};
    cout << s.makeConnected(6, input1) << endl;
    vector<vector<int>> input2{{0, 1}, {0, 2}, {0, 3}, {1, 2}};
    cout << s.makeConnected(6, input2) << endl;
    vector<vector<int>> input3{{0, 1}, {0, 2}, {3, 4}, {2, 3}};
    cout << s.makeConnected(5, input3) << endl;
    vector<vector<int>> input4{{1, 5}, {1, 7}, {1, 2}, {1, 4}, {3, 7},
                               {4, 7}, {3, 5}, {0, 6}, {0, 1}, {0, 4},
                               {2, 6}, {0, 3}, {0, 2}};
    cout << s.makeConnected(12, input4) << endl;
    vector<vector<int>> input5{
        {17, 51}, {33, 83}, {53, 62}, {25, 34}, {35, 90}, {29, 41}, {14, 53},
        {40, 84}, {41, 64}, {13, 68}, {44, 85}, {57, 58}, {50, 74}, {20, 69},
        {15, 62}, {25, 88}, {4, 56},  {37, 39}, {30, 62}, {69, 79}, {33, 85},
        {24, 83}, {35, 77}, {2, 73},  {6, 28},  {46, 98}, {11, 82}, {29, 72},
        {67, 71}, {12, 49}, {42, 56}, {56, 65}, {40, 70}, {24, 64}, {29, 51},
        {20, 27}, {45, 88}, {58, 92}, {60, 99}, {33, 46}, {19, 69}, {33, 89},
        {54, 82}, {16, 50}, {35, 73}, {19, 45}, {19, 72}, {1, 79},  {27, 80},
        {22, 41}, {52, 61}, {50, 85}, {27, 45}, {4, 84},  {11, 96}, {0, 99},
        {29, 94}, {9, 19},  {66, 99}, {20, 39}, {16, 85}, {12, 27}, {16, 67},
        {61, 80}, {67, 83}, {16, 17}, {24, 27}, {16, 25}, {41, 79}, {51, 95},
        {46, 47}, {27, 51}, {31, 44}, {0, 69},  {61, 63}, {33, 95}, {17, 88},
        {70, 87}, {40, 42}, {21, 42}, {67, 77}, {33, 65}, {3, 25},  {39, 83},
        {34, 40}, {15, 79}, {30, 90}, {58, 95}, {45, 56}, {37, 48}, {24, 91},
        {31, 93}, {83, 90}, {17, 86}, {61, 65}, {15, 48}, {34, 56}, {12, 26},
        {39, 98}, {1, 48},  {21, 76}, {72, 96}, {30, 69}, {46, 80}, {6, 29},
        {29, 81}, {22, 77}, {85, 90}, {79, 83}, {6, 26},  {33, 57}, {3, 65},
        {63, 84}, {77, 94}, {26, 90}, {64, 77}, {0, 3},   {27, 97}, {66, 89},
        {18, 77}, {27, 43}};
    cout << s.makeConnected(100, input5) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }
