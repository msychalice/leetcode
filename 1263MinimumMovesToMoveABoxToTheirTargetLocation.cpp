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
    struct Node {
        int bx;  // box x
        int by;  // box y
        int px;  // player x
        int py;  // player y
        int g;   // steps away from starting position
        int h;  // heuristic distance(Manhattan distance)
        int f() const {
            return g + h;
        }
        int hashvalue() const {
            return bx << 24 | by << 16 | px << 8 | py;
        }
    };

    int minPushBox(vector<vector<char>>& grid) {
        // locate the position of S B T
        int height = grid.size();
        int width = grid[0].size();
        int tx, ty, bx, by, px, py = -1;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j] == 'S') {
                    px = i;
                    py = j;
                }
                if (grid[i][j] == 'B') {
                    bx = i;
                    by = j;
                }
                if (grid[i][j] == 'T') {
                    tx = i;
                    ty = j;
                }
            }
        }

        // four directions
        static const vector<vector<int>> directions{
            {0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        // check there is a path from (px1, py1) to (px2, py2)
        function<bool(int, int, int, int)> hasPath = [&](int px1, int py1,
                                                         int px2, int py2) {
            if (px1 == px2 && py1 == py2) {
                return true;
            }

            if (px2 < 0 || py2 < 0 || px2 >= height || py2 >= width ||
                grid[px2][py2] == 'B' || grid[px2][py2] == '#') {
                return false;
            }

            vector<vector<bool>> visited(height, vector<bool>(width));

            /*
            // DFS
            function<bool(int, int)> dfs = [&](int x, int y) {
                if (x == px2 && y == py2) {
                    return true;
                }

                visited[x][y] = true;
                for (auto dir : directions) {
                    int nextX = x + dir[0];
                    int nextY = y + dir[1];
                    if (nextX < 0 || nextY < 0 || nextX >= height ||
                        nextY >= width || grid[nextX][nextY] == 'B' ||
                        grid[nextX][nextY] == '#' || visited[nextX][nextY]) {
                        continue;
                    }

                    if (dfs(nextX, nextY)) {
                        return true;
                    }
                }

                return false;
            };

            return dfs(px1, py1);
             */

            // we can use either DFS or BFS to find the path, but BFS will be
            // faster. In mose cases,the next player's position is around the
            // current player's position.

            // BFS
            queue<pair<int, int>> queNeighbor;
            queNeighbor.push(make_pair(px1, py1));
            visited[px1][py1] = true;

            while (!queNeighbor.empty()) {
                int queSize = queNeighbor.size();
                while (queSize--) {
                    auto [curX, curY] = queNeighbor.front();
                    queNeighbor.pop();

                    for (auto dir : directions) {
                        int nextX = curX + dir[0];
                        int nextY = curY + dir[1];
                        if (nextX < 0 || nextY < 0 || nextX >= height ||
                            nextY >= width || grid[nextX][nextY] == 'B' ||
                            grid[nextX][nextY] == '#' ||
                            visited[nextX][nextY]) {
                            continue;
                        }

                        if (nextX == px2 && nextY == py2) {
                            return true;
                        }

                        visited[nextX][nextY] = true;
                        queNeighbor.push(make_pair(nextX, nextY));
                    }
                }
            }

            return false;
        };

        // check the four directions
        function<pair<bool, Node>(Node, int, int)> canPush =
            [&](Node curNode, int dx, int dy) {
                int nextBX = curNode.bx + dx;
                int nextBY = curNode.by + dy;
                int nextPX = curNode.bx;
                int nextPY = curNode.by;

                if (nextBX >= 0 && nextBY >= 0 && nextBX < height &&
                    nextBY < width && grid[nextBX][nextBY] != '#') {
                    // before finding the possible path, we need to update
                    // the position of box
                    swap(grid[bx][by], grid[curNode.bx][curNode.by]);

                    bool res = hasPath(curNode.px, curNode.py, curNode.bx - dx,
                                       curNode.by - dy);

                    // after pathfinding, restore the position of box
                    swap(grid[bx][by], grid[curNode.bx][curNode.by]);
                    return make_pair(res, Node{nextBX, nextBY, nextPX, nextPY});
                }

                return make_pair(false, Node{});
            };

        unordered_set<int> visited;
        function<bool(const Node&, const Node&)> greaterNode =
            [](const Node& n1, const Node& n2) -> bool {
            return n1.f() > n2.f();
        };
        priority_queue<Node, vector<Node>,
                       function<bool(const Node&, const Node&)>>
            queNeighbor(greaterNode);

        // push all possible initial nodes, 4 at most
        for (auto dir : directions) {
            if (hasPath(px, py, bx + dir[0], by + dir[1])) {
                // manhattan distance
                Node initialNode{bx,          by, bx + dir[0],
                                 by + dir[1], 0,  abs(bx - tx) + abs(by - ty)};
                queNeighbor.push(initialNode);
                visited.insert(initialNode.hashvalue());
            }
        }

        while (!queNeighbor.empty()) {
            Node curNode = queNeighbor.top();
            queNeighbor.pop();

            // check all four directions
            for (auto dir : directions) {
                auto [isValid, nextNode] = canPush(curNode, dir[0], dir[1]);

                // next node is reachable and not visited
                if (isValid && visited.count(nextNode.hashvalue()) == 0) {
                    nextNode.g = curNode.g + 1;
                    nextNode.h = abs(nextNode.bx - tx) + abs(nextNode.by - ty);

                    if (nextNode.bx == tx && nextNode.by == ty) {
                        return nextNode.g;
                    }

                    queNeighbor.push(nextNode);
                    visited.insert(nextNode.hashvalue());
                }
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    /*
     */
    vector<vector<char>> input = {
        {'#', '#', '#', '#', '#', '#'}, {'#', 'T', '#', '#', '#', '#'},
        {'#', '.', '.', 'B', '.', '#'}, {'#', '.', '#', '#', '.', '#'},
        {'#', '.', '.', '.', 'S', '#'}, {'#', '#', '#', '#', '#', '#'}};
    cout << s.minPushBox(input) << endl;
    vector<vector<char>> input1 = {
        {'#', '#', '#', '#', '#', '#'}, {'#', 'T', '#', '#', '#', '#'},
        {'#', '.', '.', 'B', '.', '#'}, {'#', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', 'S', '#'}, {'#', '#', '#', '#', '#', '#'}};
    cout << s.minPushBox(input1) << endl;
    vector<vector<char>> input2 = {
        {'#', '#', '#', '#', '#', '#'}, {'#', 'T', '.', '.', '#', '#'},
        {'#', '.', '#', 'B', '.', '#'}, {'#', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', 'S', '#'}, {'#', '#', '#', '#', '#', '#'}};
    cout << s.minPushBox(input2) << endl;
    vector<vector<char>> input3 = {{'#', '#', '#', '#', '#', '#', '#'},
                                   {'#', 'S', '#', '.', 'B', 'T', '#'},
                                   {'#', '#', '#', '#', '#', '#', '#'}};
    cout << s.minPushBox(input3) << endl;
    vector<vector<char>> input4 = {{'#', '.', '.', '#', '#', '#', '#', '#'},
                                   {'#', '.', '.', 'T', '#', '.', '.', '#'},
                                   {'#', '.', '.', '.', '#', 'B', '.', '#'},
                                   {'#', '.', '.', '.', '.', '.', '.', '#'},
                                   {'#', '.', '.', '.', '#', '.', 'S', '#'},
                                   {'#', '.', '.', '#', '#', '#', '#', '#'}};
    cout << s.minPushBox(input4) << endl;
    /*
     */

    cout << "*************output*************" << endl;

    return 0;
}
