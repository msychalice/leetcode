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

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int curMax = 0;
        int curIndex = 0;

        while (curMax < nums.size() - 1) {
            int prevMax = curMax;
            for (; curIndex <= prevMax; curIndex++) {
                curMax = max(curMax, curIndex + nums[curIndex]);
            }

            if (prevMax == curMax) {
                return false;
            }
        }
        return true;
    }
};

int main(){
    Solution s;

    vector<int> input{2, 3, 1, 1, 4};
	auto output = s.canJump(input);

    vector<int> input1{3, 2, 1, 0, 4};
	auto output1 = s.canJump(input1);

    vector<int> input2{1, 1, 1, 0};
	auto output2 = s.canJump(input2);

    vector<int> input3{4,0,3,4,1,4,2,1};
	auto output3 = s.canJump(input3);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;

    return 0;
}

