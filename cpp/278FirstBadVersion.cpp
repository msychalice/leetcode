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

// The API isBadVersion is defined for you.
 bool isBadVersion(int version) {
     if (version >= 1) {
         return true;
     }
     return false;
 }

class Solution {
public:
    int firstBadVersion(int n) {
        int64_t min = 1;
        int64_t max = static_cast<int64_t>(n) + 1;

        while (min < max) {
            int64_t cur = (min + max) / 2;

            bool isCurBadVersion = isBadVersion(cur);
            bool isPrevBadVersion = false;
            if (cur > 1) {
                isPrevBadVersion = isBadVersion(cur - 1);
            }

            if (isCurBadVersion && !isPrevBadVersion) {
                return cur;
            } else if (isCurBadVersion && isPrevBadVersion) {
                max = cur;
            } else if (!isCurBadVersion) {
                min = cur + 1;
            }
        }

        return -1;
    }
};

int main(){
    Solution s;
	auto output = s.firstBadVersion(1);

    cout << "*************output*************" << endl;
    cout << output << endl;

    return 0;
}
