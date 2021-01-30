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
#include <map>

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


/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printList(const ListNode* node) {
    while (node != nullptr) {
        cout << node->val;

        node = node->next;
        
        if (node != nullptr) {
            cout << "->";
        } else {
            cout << endl;
        }
    }
}

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int lenStr = s.size();
        if (lenStr == 0) {
            return 0;
        }

        int output = 0;

        unordered_map<char, int> window;
        int left = 0;
        int right = 0;
        while (right < s.size()) {
            char rChar = s[right];
            window[rChar]++;
            right++;

            while (window[rChar] > 1) {
                char lChar = s[left];
                window[lChar]--;
                left++;
            }

            output = max(output, right - left);
        }

        return output;
    }
};

int main(){
    Solution s;

	auto output = s.lengthOfLongestSubstring("abcabcbb");
	auto output1 = s.lengthOfLongestSubstring("bbbbb");
	auto output2 = s.lengthOfLongestSubstring("pwwkew");
	auto output3 = s.lengthOfLongestSubstring("");
	auto output4 = s.lengthOfLongestSubstring(" ");
	auto output5 = s.lengthOfLongestSubstring("a");
	auto output6 = s.lengthOfLongestSubstring("tmmzuxt");

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;
    cout << output5 << endl;
    cout << output6 << endl;

    return 0;
}
