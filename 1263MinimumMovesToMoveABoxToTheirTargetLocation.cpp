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
        int hashvalue() const {
            return bx << 24 | by << 16 | px << 8 | py;
        }
    };

    int minPushBox(vector<vector<char>>& grid) {
        // print2DimVec(grid);
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

        /*
        cout << "tx, ty, bx, by, px, py" << tx << "," << ty << "," << bx << ","
             << by << "," << px << "," << py << endl;
             */

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

            bool isPrint = false;
            /*
            if (px1 == 2 && py1 == 5 && px2 == 3 && py2 == 6) {
                isPrint = true;
            }
            */

            vector<vector<bool>> visited(height, vector<bool>(width));

            /*
            // DFS

            function<bool(int, int)> dfs = [&](int x, int y) {
                if (x == px2 && y == py2) {
                    return true;
                }

                if (isPrint) {
                    cout << "mark visited " << x << "," << y << endl;
                }

                visited[x][y] = true;
                for (auto dir : directions) {
                    int nextX = x + dir[0];
                    int nextY = y + dir[1];
                    if (nextX < 0 || nextY < 0 || nextX >= height ||
                        nextY >= width || grid[nextX][nextY] == 'B' ||
                        grid[nextX][nextY] == '#' || visited[nextX][nextY]) {
                        if (isPrint) {
                            if (nextX < 0 || nextY < 0 || nextX >= height ||
                                nextY >= width) {
                                cout << "not valid next " << nextX << ","
                                     << nextY << endl;
                            } else if (visited[nextX][nextY]) {
                                cout << "visited next " << nextX << "," << nextY
                                     << endl;
                            } else {
                                cout << "1not valid next " << nextX << ","
                                     << nextY << endl;
                            }
                        }
                        continue;
                    } else {
                        if (isPrint) {
                            cout << "dfs next " << nextX << "," << nextY
                                 << endl;
                        }
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

                    if (nextBX == 3 && nextBY == 4 && nextPX == 3 &&
                        nextPY == 5) {
                        /*
                        cout << "hasPath " << curNode.px << "," << curNode.py
                             << "->" << curNode.bx - dx << ","
                             << curNode.by - dy << endl;
                        print2DimVec(grid);
                        cout << "isvalid " << res << endl;
                        */
                    }

                    // after pathfinding, restore the position of box
                    swap(grid[bx][by], grid[curNode.bx][curNode.by]);
                    return make_pair(res, Node{nextBX, nextBY, nextPX, nextPY});
                }

                return make_pair(false, Node{});
            };

        unordered_set<int> visited;
        queue<Node> queNeighbor;

        // push all possible initial nodes, 4 at most
        for (auto dir : directions) {
            if (hasPath(px, py, bx + dir[0], by + dir[1])) {
                Node initialNode{bx, by, bx + dir[0], by + dir[1]};
                /*
                cout << "initialNode " << initialNode.bx << ","
                     << initialNode.by << "," << initialNode.px << ","
                     << initialNode.py << endl;
                     */
                queNeighbor.push(initialNode);
                visited.insert(initialNode.hashvalue());
            }
        }

        int steps = 0;

        while (!queNeighbor.empty()) {
            int queSize = queNeighbor.size();
            while (queSize--) {
                Node curNode = queNeighbor.front();
                queNeighbor.pop();


                // check all four directions
                for (auto dir : directions) {
                    auto [isValid, nextNode] = canPush(curNode, dir[0], dir[1]);

                    // next node is reachable and not visited
                    if (isValid && visited.count(nextNode.hashvalue()) == 0) {
                        if (nextNode.bx == tx && nextNode.by == ty) {
                            return steps + 1;
                        }

                        queNeighbor.push(nextNode);
                        visited.insert(nextNode.hashvalue());
                        /*
                        cout << "pushNode " << nextNode.bx << "," << nextNode.by
                             << "," << nextNode.px << "," << nextNode.py
                             << endl;
                    } else {
                        if (!isValid) {
                            cout << "!isvalid" << endl;
                        }
                        if (visited.count(nextNode.hashvalue()) > 0) {
                            cout << "visited" << endl;
                        }
                        cout << "not push node " << nextNode.bx << ","
                             << nextNode.by << "," << nextNode.px << ","
                             << nextNode.py << endl;
                             */
                    }
                }
            }
            steps++;
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
