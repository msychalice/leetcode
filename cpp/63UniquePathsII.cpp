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
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int height = obstacleGrid.size();
        if (height == 0) {
            return 0;
        }
        int width = obstacleGrid[0].size();

        if (obstacleGrid[height-1][width-1] == 1 ||
                obstacleGrid[0][0] == 1) {
            return 0;
        }

        vector<vector<int64_t>> result;
        for (auto& v : obstacleGrid) {
            vector<int64_t> row;
            for (auto& o : v) {
                if (o == 1) {
                    row.push_back(-1);//change obstacle to -1
                } else {
                    row.push_back(0);
                }
            }
            result.push_back(move(row));
        }

        for (int x = height - 1; x >= 0; x--) {
            for (int y = width - 1; y >= 0; y--) {
                if (x == height - 1 && y == width - 1) {
                    result[height-1][width-1] = 1;
                    continue;
                }

                if (result[x][y] == -1) { // obstacle
                    continue;
                }
                

                int64_t downGrid = (x+1 < height && result[x+1][y] != -1) ? result[x+1][y] : 0;
                int64_t rightGrid = (y+1 < width && result[x][y+1] != -1) ? result[x][y+1] : 0;
                result[x][y] = downGrid + rightGrid;
            }
        }

        return result[0][0];
    }
};

int main(){
    Solution s;

    vector<vector<int>> input{
		{0, 0, 0},
		{0, 1, 0},
		{0, 0, 0}
    };
	auto output = s.uniquePathsWithObstacles(input);

    vector<vector<int>> input1{
		{0, 1}
    };
	auto output1 = s.uniquePathsWithObstacles(input1);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}
