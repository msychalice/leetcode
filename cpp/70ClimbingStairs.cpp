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

class Solution {
public:
    int climbStairs(int n) {
        unordered_map<int, int> cachedResult;

        function<int(int)> findSteps = [&cachedResult, &findSteps](int length) ->int {
            if (length == 1) {
                return 1;
            }

            auto it = cachedResult.find(length);
            if (it != cachedResult.end()) {
                return it->second;
            }

            int steps = 0;

            if (length > 1) {
                steps += findSteps(length - 1);
            }

            if (length > 2) {
                steps += findSteps(length - 2);
            }

            cachedResult.emplace(length, steps);

            return steps;
        };

        return findSteps(n+1);
    }
};

int main(){
    Solution s;
	auto output = s.climbStairs(3);
	auto output1 = s.climbStairs(4);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}
