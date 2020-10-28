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
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

        function<bool(int,int)> searchRoot = [&searchRoot, &visited, &grid](int x, int y) {
            if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) {
                return false;
            }

            if (!visited[x][y]) {
                visited[x][y] = true;

                if (grid[x][y] == '1') {
                    searchRoot(x-1, y);
                    searchRoot(x+1, y);
                    searchRoot(x, y-1);
                    searchRoot(x, y+1);
                    return true;
                }
            }
            return false;
        };

        int output = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (searchRoot(i, j)) {
                    output++;
                }
            }
        }

        return output;
    }
};

int main(){
    Solution s;

    vector<vector<char>> input{
		{'1', '1', '1', '1', '0'},
		{'1', '1', '0', '1', '0'},
		{'1', '1', '0', '0', '0'},
		{'0', '0', '0', '0', '0'}};
	auto output = s.numIslands(input);

    vector<vector<char>> input1{
		{'1', '1', '0', '0', '0'},
		{'1', '1', '0', '0', '0'},
		{'0', '0', '1', '0', '0'},
		{'0', '0', '0', '1', '1'}};
	auto output1 = s.numIslands(input1);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}

