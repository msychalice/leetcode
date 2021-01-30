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
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> output;
        output.emplace_back(vector<int>{});
        vector<int> curPath;

        function<void(vector<int> &&)> backtrack =
            [&](vector<int>&& curChoices) {
                for (auto it = curChoices.begin(); it != curChoices.end();
                     it++) {
                    curPath.push_back(*it);
                    output.push_back(curPath);
                    backtrack(vector<int>(next(it), curChoices.end()));
                    curPath.pop_back();
                }
            };

        backtrack(move(nums));

        return output;
    }
};


int main(){
    Solution s;
    vector<int> input = vector<int>{1, 2, 3};
	auto output = s.subsets(input);

    cout << "*************output*************" << endl;
    print2DimVec(output);

    return 0;
}
