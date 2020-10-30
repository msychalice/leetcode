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
#include <queue>
#include <algorithm>

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
    int uniquePaths(int m, int n) {
        if (m == 1 && n == 1) {
            return 1;
        }

        vector<vector<int>> cachedResults(m, vector<int>(n, 0));
        /*
        vector<vector<int>> cachedResults(m);
        for (auto& r : cachedResults) {
            r = vector<int>(n, 0);
        }
        */

        for (int i = m-1; i >=0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (i == m - 1 && j == n - 1) {
                    cachedResults[i][j] = 1;
                    continue;
                }

                int rightPaths = (j + 1) >= n ? 0 : cachedResults[i][j+1];
                int downPaths = (i + 1) >= m ? 0 : cachedResults[i+1][j];
                cachedResults[i][j] = rightPaths + downPaths;
            }
        }

        return cachedResults[0][0];
    }
};

int main(){
    Solution s;
	auto output = s.uniquePaths(3, 7);
	auto output1 = s.uniquePaths(3, 2);
	auto output2 = s.uniquePaths(7, 3);
	auto output3 = s.uniquePaths(3, 3);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;

    return 0;
}
