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
    int minMutation(string start, string end, vector<string>& bank) {
        if (start == end) {
            return 0;
        }

        unordered_set<string> setBank;
        for (auto& s : bank) {
            setBank.insert(s);
        }

        if (setBank.count(end) == 0) {
            return -1;
        }

        const vector<char> vecChoices{'A', 'C', 'G', 'T'};

        int step = 1;
        unordered_set<string> visited;
        queue<string> queNeighbor;
        queNeighbor.push(start);
        visited.insert(start);

        while (!queNeighbor.empty()) {
            int queSize = queNeighbor.size();
            for (int i = 0; i < queSize; i++) {
                string s = queNeighbor.front();
                queNeighbor.pop();

                for (int n = 0; n < s.size(); n++) {
                    string neighbor = s;
                    for (int m = 0; m < vecChoices.size(); m++) {
                        neighbor[n] = vecChoices[m];
                        if (neighbor[n] != s[n] &&
                            setBank.count(neighbor) > 0 &&
                            visited.count(neighbor) == 0) {  // valid mutation
                            if (neighbor == end) {
                                return step;
                            }
                            queNeighbor.push(neighbor);
                            visited.insert(neighbor);
                        }
                    }
                }
            }

            step++;
        }

        return -1;
    }
};

int main(){
    Solution s;
    /*
     */
    vector<string> input{"AACCGGTA"};
    cout << s.minMutation("AACCGGTT", "AACCGGTA", input) << endl;
    vector<string> input1{"AACCGGTA", "AACCGCTA", "AAACGGTA"};
    cout << s.minMutation("AACCGGTT", "AAACGGTA", input1) << endl;
    vector<string> input2{"AAAACCCC", "AAACCCCC", "AACCCCCC"};
    cout << s.minMutation("AAAAACCC", "AACCCCCC", input2) << endl;
    vector<string> input3{"AATTCCGG", "AACCTGGG", "AACCCCGG", "AACCTACC"};
    cout << s.minMutation("AACCTTGG", "AATTCCGG", input3) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }
