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
    int compareVersion(string version1, string version2) {
        vector<string> vec1;
        vector<string> vec2;

        auto build = [](string& input, vector<string>& vec) {
            auto dotIndex = input.find(".");
            size_t head = 0;
            while (dotIndex != string::npos) {
                vec.push_back(input.substr(head, dotIndex-head));
                head = dotIndex + 1;
                dotIndex = input.find(".", head);
            }

            vec.push_back(input.substr(head));
        };

        build(version1, vec1);
        build(version2, vec2);

        int i = 0;
        for (;i<vec1.size() || i<vec2.size();i++) {
            int num1 = 0;
            int num2 = 0;
            if (i < vec1.size()) {
                num1 = stoi(vec1[i]);
            }
            if (i < vec2.size()) {
                num2 = stoi(vec2[i]);
            }

            if (num1 < num2) {
                return -1;
            } else if (num1 > num2) {
                return 1;
            } else {
                continue;
            }
        }

        return 0;
    }
};

int main(){
    Solution s;

	auto output = s.compareVersion("1.01", "1.001");
	auto output1 = s.compareVersion("1.0", "1.0.0");
	auto output2 = s.compareVersion("0.1", "1.1");
	auto output3 = s.compareVersion("1.0.1", "1");
	auto output4 = s.compareVersion("7.5.2.4", "7.5.3");

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;

    return 0;
}

