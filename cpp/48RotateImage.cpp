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

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int matrixLen = matrix.size();
        int halfMatrixLen = (matrixLen - 1) / 2;
        bool isEven = matrixLen % 2 == 0;

        for (int x = 0; x <= halfMatrixLen; x++) {
            if (x == halfMatrixLen && !isEven) {
                break;
            }

            for (int y = x; y < matrixLen - x - 1; y++) {
                int x1 = y;
                int y1 = matrixLen - 1 - x;
                int x2 = y1;
                int y2 = matrixLen - 1 - x1;
                int x3 = y2;
                int y3 = matrixLen - 1 -x2;

                int tmp1 = matrix[x1][y1];
                matrix[x1][y1] = matrix[x][y];
                int tmp2 = matrix[x2][y2];
                matrix[x2][y2] = tmp1;
                int tmp3 = matrix[x3][y3];
                matrix[x3][y3] = tmp2;
                matrix[x][y] = tmp3;
            }
        }
    }
};

int main(){
    Solution s;
    vector<vector<int>> input{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	s.rotate(input);
    vector<vector<int>> input1{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
	s.rotate(input1);
    vector<vector<int>> input2{{1}};
	s.rotate(input2);
    vector<vector<int>> input3{{1, 2}, {3, 4}};
	s.rotate(input3);

    cout << "*************output*************" << endl;
    print2DimVec(input);
    print2DimVec(input1);
    print2DimVec(input2);
    print2DimVec(input3);

    return 0;
}

