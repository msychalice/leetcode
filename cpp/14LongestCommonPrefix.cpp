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
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }
        int i = 0;
        while (true) {
            int c = 0;
            for (const auto& s : strs) {
                if (i == s.size()) {
                    return strs[0].substr(0, i);
                }

                if (c == 0) {
                    c = static_cast<int>(s[i]);
                } else if (c != static_cast<int>(s[i])) {
                    return strs[0].substr(0, i);
                }
            }
            i++;
        }

        return strs[0].substr(0, i);
    }
};

int main(){
    Solution s;

    auto input = vector<string>{"flower", "flow", "flight"};
	auto output = s.longestCommonPrefix(input);

    auto input1 = vector<string>{"dog", "racecar", "car"};
	auto output1 = s.longestCommonPrefix(input1);

    auto input2 = vector<string>{"cir", "car"};
	auto output2 = s.longestCommonPrefix(input2);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;

    return 0;
}

