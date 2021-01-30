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
    char findTheDifference(string s, string t) {
        using HashMap = unordered_map<char, int>;

        function<HashMap(const string&)> buildHashMap = [](const string& input) {
            HashMap hm;
            for (auto itChar = input.begin(); itChar != input.end(); itChar++) {
                auto itCount = hm.find(*itChar);
                if (itCount == hm.end()) {
                    hm.emplace(*itChar, 1);
                } else {
                    ++(itCount->second);
                }
            }
            return hm;
        };

        HashMap mapS = buildHashMap(s);
        HashMap mapT = buildHashMap(t);

        for (auto itCountT = mapT.begin(); itCountT != mapT.end(); itCountT++) {
            auto itCountS = mapS.find(itCountT->first);
            if (itCountS == mapS.end() ||
                (itCountS != mapS.end() && itCountS->second != itCountT->second)) {
                return itCountT->first;
            }
        }
        return ' ';
    }
};

int main(){
    Solution s;
	auto output = s.findTheDifference("abcd", "abcde");
	auto output1 = s.findTheDifference("", "y");
	auto output2 = s.findTheDifference("a", "aa");
	auto output3 = s.findTheDifference("ae", "aea");
	auto output4 = s.findTheDifference("abcdereed", "abcedereed");

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;

    return 0;
}

