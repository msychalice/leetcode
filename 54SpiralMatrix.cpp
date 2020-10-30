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
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int minHeight = 0;
        int minWidth = 0;
        int maxHeight = matrix.size() - 1;
        int maxWidth = matrix.size() > 0 ? matrix[0].size() - 1 : 0;

        vector<vector<int>> direction{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};    // speed of {x, y}
        vector<vector<int>> limit{{1,0,0,0}, {0,0,0,-1}, {0,-1,0,0}, {0,0,1,0}};    //change {minHeight,maxHeight,minWidth,maxWidth}

        vector<int> output;
        int x = 0;
        int y = 0;
        int directionIndex = 0;
        while (minHeight <= maxHeight && minWidth <= maxWidth) {
            output.emplace_back(matrix[x][y]);

            int xDiff = direction[directionIndex][0];
            int yDiff = direction[directionIndex][1];
            int newX = x + xDiff;
            int newY = y + yDiff;
            if (newX > maxHeight || newX < minHeight ||
                    newY > maxWidth || newY < minWidth) {
                //update limits first
                minHeight += limit[directionIndex][0];
                maxHeight += limit[directionIndex][1];
                minWidth += limit[directionIndex][2];
                maxWidth += limit[directionIndex][3];

                //try with another direction
                directionIndex = (directionIndex + 1) % direction.size();

                xDiff = direction[directionIndex][0];
                yDiff = direction[directionIndex][1];
                newX = x + xDiff;
                newY = y + yDiff;

                /*
                cout << "x, y, minHeight, maxHeight, minWidth, maxWidth " <<
                    newX <<  "," << newY  << "," << minHeight << "," << maxHeight <<
                    "," <<  minWidth << "," << maxWidth << endl;
                    */

                if (newX > maxHeight || newX < minHeight ||
                        newY > maxWidth || newY < minWidth) {
                    //cout << "break" << endl;
                    break;
                } else {
                    x = newX;
                    y = newY;
                }
            } else {
                x = newX;
                y = newY;
            }
        }

        return output;
    }
};

int main(){
    Solution s;

    using Vec2D = vector<vector<int>>;
    Vec2D input{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	auto output = s.spiralOrder(input);
    Vec2D input1{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
	auto output1 = s.spiralOrder(input1);
    Vec2D input2{{1}};
	auto output2 = s.spiralOrder(input2);
    Vec2D input3{{1, 2}, {3, 4}};
	auto output3 = s.spiralOrder(input3);
    Vec2D input4;
	auto output4 = s.spiralOrder(input4);

    cout << "*************output*************" << endl;
    printContainer(output);
    printContainer(output1);
    printContainer(output2);
    printContainer(output3);
    printContainer(output4);

    return 0;
}
