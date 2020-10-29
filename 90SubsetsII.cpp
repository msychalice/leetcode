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
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> output;
        output.push_back(vector<int>{});

        if (nums.empty()) {
            return output;
        }

        function<void(vector<int>&&)> dfs =
            [&dfs, &nums, &output](vector<int>&& preVec) {
                int curIndex = 0;
                int endIndex = nums.size() - 1;
                if (!preVec.empty()) {
                    curIndex = *(preVec.end()-1) + 1;
                }

                int mostLeftNodeIndex = curIndex;

                for (;curIndex <= endIndex; curIndex++) {
                    if (curIndex > mostLeftNodeIndex && nums[curIndex] == nums[curIndex - 1]) { //find duplicate node
                        continue;
                    }

                    vector<int> newNode(preVec);
                    newNode.push_back(curIndex);
                    vector<int> subset;
                    for (auto i : newNode) {
                        subset.push_back(nums[i]);
                    }
                    output.push_back(move(subset));

                    dfs(move(newNode));
                }
        };

        dfs(vector<int>{});

        return output;
    }
};

int main(){
    Solution s;
    vector<int> input = vector<int>{1, 2, 2};
	auto output = s.subsetsWithDup(input);

    cout << "*************output*************" << endl;
    print2DimVec(output);

    return 0;
}
