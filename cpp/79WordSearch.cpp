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
    bool exist(vector<vector<char>>& board, string word) {

        function<int(int,int)> convert = [](int x, int y) {
            return x * 1000 + y;
        };
        function<int(int)> getX = [](int index) {
            return index / 1000;
        };
        function<int(int)> getY = [](int index) {
            return index % 1000;
        };

        unordered_map<char, vector<int>> mapCharIndex;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j< board[0].size(); j++) {
                auto it = mapCharIndex.find(board[i][j]);
                if (it != mapCharIndex.end()) {
                    it->second.push_back(convert(i, j));
                } else {
                    mapCharIndex.emplace(board[i][j], vector<int>{convert(i, j)});
                }
            }
        }

        unordered_set<int> visited;

        function<bool(int, int)> findPath =
            [&findPath, &visited, &mapCharIndex, &board, &word, &convert, &getX, &getY](int curBoardIndex, int curCharIndex) {

                char curChar = word[curCharIndex];
                int x = getX(curBoardIndex);
                int y = getY(curBoardIndex);

                if (curChar != board[x][y]) {
                    return false;
                }

                if (visited.find(curBoardIndex) != visited.end()) {
                    return false;
                }

                int nextCharIndex = curCharIndex + 1;
                if (nextCharIndex == word.size()) {
                    return true;
                }

                visited.emplace(curBoardIndex);

                if (x - 1 >= 0 && findPath(convert(x-1, y), nextCharIndex)) {
                    return true;
                }
                if (y - 1 >= 0 && findPath(convert(x, y-1), nextCharIndex)) {
                    return true;
                }
                if (x + 1 < board.size() && findPath(convert(x+1, y), nextCharIndex)) {
                    return true;
                }
                if (y + 1 < board[0].size() && findPath(convert(x, y+1), nextCharIndex)) {
                    return true;
                }

                visited.erase(curBoardIndex);

                return false;
            };

        for (const auto& index : mapCharIndex[word[0]]) {
            if (findPath(index, 0)) {
                return true;
            }
        }

        return false;
    }
};

int main(){
    Solution s;

    vector<vector<char>> input{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
	auto output = s.exist(input, "ABCCED");

    vector<vector<char>> input1{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
	auto output1 = s.exist(input1, "SEE");

    vector<vector<char>> input2{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
	auto output2 = s.exist(input2, "ABCB");

    vector<vector<char>> input3{{'a'}};
	auto output3 = s.exist(input3, "a");

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;

    return 0;
}
