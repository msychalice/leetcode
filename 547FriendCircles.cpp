#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template<class Container>
void printContainer(const Container& container) {
    return;

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

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        using VecInt = vector<int>;
        VecInt disjointSets = VecInt(M.size(), -1);

        function<int(int)> findRoot = [&disjointSets, &findRoot](int node) {
            if (disjointSets[node] < 0) {
                return node;
            } else {
                int root = findRoot(disjointSets[node]);
                disjointSets[node] = root;
                return root;
            }
        };

        function<void(int,int)> unionSet = [&disjointSets, &unionSet, &findRoot](int node1, int node2) {
            if (node1 == node2) {
                return;
            }

            int parent1 = disjointSets[node1];
            int parent2 = disjointSets[node2];

            if (parent1 < 0 && parent2 < 0) {
                if (parent1 < parent2) {
                    disjointSets[node1] = parent1 + parent2;
                    disjointSets[node2] = node1;
                } else if (parent1 > parent2) {
                    disjointSets[node2] = parent1 + parent2;
                    disjointSets[node1] = node2;
                } else if (parent1 == parent2) {
                    if (node1 < node2) {
                        disjointSets[node1] = parent1 + parent2;
                        disjointSets[node2] = node1;
                    } else {
                        disjointSets[node2] = parent1 + parent2;
                        disjointSets[node1] = node2;
                    }
                }
            } else if (parent1 < 0 && parent2 >= 0) {
                unionSet(node1, findRoot(node2));
            } else if (parent1 >= 0 && parent2 < 0) {
                unionSet(findRoot(node1), node2);
            } else if (parent1 >= 0 && parent2 >= 0) {
                unionSet(findRoot(node1), findRoot(node2));
            }
        };

        for (int i = 0; i < M.size(); i++) {
            for (int j = i + 1; j < M[i].size(); j++) {
                if (M[i][j] == 1) {
                    unionSet(i, j);
                }
            }
        }

        printContainer(disjointSets);

        int output = 0;
        for (auto r : disjointSets) {
            if (r < 0) {
                output++;
            }
        }

        return output;
    }
};

int main(){
    Solution s;

    auto vecInput = vector<vector<int>>{{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    auto output = s.findCircleNum(vecInput);

    auto vecInput1 = vector<vector<int>>{{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 1, 1}};
    auto output1 = s.findCircleNum(vecInput1);


    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}
