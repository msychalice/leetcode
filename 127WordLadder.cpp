#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

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
    int ladderLength(string beginWord, string endWord,
                     vector<string>& wordList) {
        unordered_set<string> setWords;
        for (auto& s : wordList) {
            setWords.insert(s);
        }

        if (setWords.count(endWord) == 0) {
            return 0;
        }

        int step = 1;
        unordered_set<string> visited;
        queue<string> queNeighbor;
        queNeighbor.push(beginWord);
        visited.insert(beginWord);

        while (!queNeighbor.empty()) {
            int queSize = queNeighbor.size();
            for (int i = 0; i < queSize; i++) {
                string s = queNeighbor.front();
                queNeighbor.pop();

                for (int n = 0; n < s.size(); n++) {
                    string neighbor = s;
                    for (int m = 0; m < 26; m++) {
                        neighbor[n] = 'a' + m;
                        if (neighbor[n] != s[n] &&
                            setWords.count(neighbor) > 0 &&
                            visited.count(neighbor) == 0) {  // valid mutation
                            if (neighbor == endWord) {
                                return step + 1;
                            }
                            queNeighbor.push(neighbor);
                            visited.insert(neighbor);
                        }
                    }
                }
            }

            step++;
        }

        return 0;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<string> input{"hot", "dot", "dog", "lot", "log", "cog"};
    cout << s.ladderLength("hit", "cog", input) << endl;
    vector<string> input1{"hot", "dot", "dog", "lot", "log"};
    cout << s.ladderLength("hit", "cog", input1) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }
