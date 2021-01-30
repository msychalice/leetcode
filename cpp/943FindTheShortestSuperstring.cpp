#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
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
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

void printTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->val << endl;
    printTree(root->left);
    printTree(root->right);
}

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        // Backtracking
        // savedLen[i][j] : how many characters can be saved when concatenate
        // A[j] into A[i]
        vector<vector<int>> savedLen(A.size(), vector<int>(A.size()));
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A.size(); j++) {
                if (i == j) {
                    savedLen[i][j] = A[i].size();
                    continue;
                }

                int curI = 0;
                int curJ = 0;
                while (curI < A[i].size()) {
                    if (A[i][curI] == A[j][curJ]) {
                        curI++;
                        curJ++;
                    } else {
                        if (curJ == 0) {
                            curI++;
                        } else {
                            // don't move curI, otherwise might miss a match
                            curJ = 0;
                        }
                    }
                }
                /*
                if (i == 4 && j == 2) {
                    cout << A[i] << " <- " << A[j] << endl;
                    cout << "curJ " << curJ << endl;
                }
                */

                savedLen[i][j] = curJ;
            }
        }

        // print2DimVec(savedLen);

        vector<int> ansPath;
        int ansSize = numeric_limits<int>::max();
        vector<int> selected(A.size(), false);

        function<void(int, vector<int>&)> backtrack =
            [&](int curSuperStrSize, vector<int>& curPath) {
                /*
                cout << "curSize " << curSuperStrSize << endl;
                printContainer(curPath);
                */
                bool isAllSelected = true;
                for (int i = 0; i < selected.size(); i++) {
                    if (!selected[i]) {
                        isAllSelected = false;

                        /*
                        cout << "curSuperSize " << curSuperStrSize << endl;
                        cout << "curPath.back() " << curPath.back() << " i " <<
                        i
                             << endl;
                        cout << "A[i].size() " << A[i].size() << ", savedLen "
                             << savedLen[curPath.back()][i] << endl;
                             */
                        int addedLen =
                            A[i].size() - savedLen[curPath.back()][i];
                        if (curSuperStrSize + addedLen >= ansSize) {
                            continue;
                        }

                        selected[i] = true;
                        curPath.push_back(i);
                        backtrack(curSuperStrSize + addedLen, curPath);
                        selected[i] = false;
                        curPath.pop_back();
                    }
                }

                if (isAllSelected) {
                    ansSize = curSuperStrSize;
                    ansPath = curPath;
                    /*
                    cout << "found len " << curSuperStrSize << endl;
                    printContainer(ansPath);
                    */
                }
            };

        vector<int> path;
        for (int i = 0; i < A.size(); i++) {
            path.push_back(i);
            selected[i] = true;
            backtrack(A[i].size(), path);
            path.pop_back();
            selected[i] = false;
        }

        /*
        cout << "ansSize " << ansSize << endl;
        printContainer(ansPath);
        */

        stringstream strm;
        for (int i = 0; i < ansPath.size(); i++) {
            if (i == 0) {
                strm << A[ansPath[i]];
                continue;
            }

            for (int j = savedLen[ansPath[i - 1]][ansPath[i]];
                 j < A[ansPath[i]].size(); j++) {
                strm << A[ansPath[i]][j];
            }
        }

        return strm.str();
    }
};

int main() {
    Solution s;
    /*
    vector<string> input{"alex", "loves", "leetcode"};
    cout << s.shortestSuperstring(input) << endl;
    vector<string> input1{"catg", "ctaagt", "gcta", "ttca", "atgcatc"};
    cout << s.shortestSuperstring(input1) << endl;
    vector<string> input2{"yeeiebcz", "qbqhdytk",  "ygueikth",
                          "thqzyeei", "gyygueikt", "ikthqzyee"};
    cout << s.shortestSuperstring(input2) << endl;
     */
    vector<string> input3{
        "orugbsuuxowmhjh",      "zjyxzmpduthlsioor",    "qtxocgehmhfqnstl",
        "tlrlcnnrsyryfrywuebq", "hozjyxzmpduthlsio",    "hjhdmnqtxocgehm",
        "mjhzwdudlnbfkjawqacf", "hfqnstlrlcnnrsyryfry", "yfrywuebqhvwewzmq",
        "zzieemjhzwdudlnbfkj",  "nnrsyryfrywuebqhvw",   "acfgaihbhozjyxzmpdut"};
    cout << s.shortestSuperstring(input3) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
