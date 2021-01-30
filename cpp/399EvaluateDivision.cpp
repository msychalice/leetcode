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
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, int> mapCharIndex;
        int curIndex = 0;
        for (const auto& edge : equations) {
            for (const auto& node : edge) {
                if (mapCharIndex.emplace(node, curIndex).second) {
                    curIndex++;
                }
            }
        }

        using Vec2D = vector<vector<double>>;
        Vec2D cachedResults(mapCharIndex.size(), vector<double>(mapCharIndex.size(), 0.0));

        for (int i = 0; i < mapCharIndex.size(); i++) {
            cachedResults[i][i] = 1.0;
        }

        for (int i = 0; i < equations.size(); i++) {
            const auto& node1 = equations[i][0];
            const auto& node2 = equations[i][1];
            int index1 = mapCharIndex.find(node1)->second;
            int index2 = mapCharIndex.find(node2)->second;

            cachedResults[index1][index2] = values[i];
            cachedResults[index2][index1] = 1 / values[i];
        }

        function<double(unordered_set<int>&, int, int)> dfs =
            [&dfs, &cachedResults](unordered_set<int>& visited, int node1, int node2) {
                if (cachedResults[node1][node2] > 0.0) {
                    return cachedResults[node1][node2];
                }

                double result = 0.0;
                for (int neighbor = 0; neighbor < cachedResults[node1].size(); neighbor++) {
                    if (neighbor != node1 && visited.find(neighbor) == visited.end() &&
                            cachedResults[node1][neighbor] > 0.0) {
                        unordered_set<int> newVisisted(visited);
                        newVisisted.emplace(node1);
                        result = dfs(newVisisted, neighbor, node2);
                        if (result > 0.0) {
                            result = cachedResults[node1][neighbor] * result;
                            cachedResults[node1][node2] = result;
                            cachedResults[node2][node1] = 1 / result;
                            break;
                        }
                    }
                }

                return result;
            };


        vector<double> output;

        for (const auto& query : queries) {
            const auto& node1 = query[0];
            const auto& node2 = query[1];
            int index1 = -1;
            const auto& it1 = mapCharIndex.find(node1);
            if (it1 != mapCharIndex.end()) {
                index1 = it1->second;
            } else {
                output.push_back(-1.0);
                continue;
            }
            int index2 = -1;
            const auto& it2 = mapCharIndex.find(node2);
            if (it2 != mapCharIndex.end()) {
                index2 = it2->second;
            } else {
                output.push_back(-1.0);
                continue;
            }

            unordered_set<int> visited;
            double result = dfs(visited, index1, index2);
            if (result > 0.0) {
                output.push_back(result);
            } else {
                output.push_back(-1.0);
            }
        }

        return output;
    }
};

int main(){
    Solution s;

    vector<vector<string>> input01{{"a", "b"}, {"b", "c"}};
    vector<double> input02{2.0,3.0};
    vector<vector<string>> input03{{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
	auto output = s.calcEquation(input01, input02, input03);

    vector<vector<string>> input11{{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
    vector<double> input12{1.5, 2.5, 5.0};
    vector<vector<string>> input13{{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
	auto output1 = s.calcEquation(input11, input12, input13);

    vector<vector<string>> input21{{"a", "b"}};
    vector<double> input22{0.5};
    vector<vector<string>> input23{{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
	auto output2 = s.calcEquation(input21, input22, input23);

    vector<vector<string>> input31{{"x1", "x2"}, {"x2", "x3"}, {"x3", "x4"}, {"x4", "x5"}};
    vector<double> input32{3.0, 4.0, 5.0, 6.0};
    vector<vector<string>> input33{{"x1", "x5"}, {"x5", "x2"}, {"x2", "x4"}, {"x2", "x2"}, {"x2", "x9"}, {"x9", "x9"}};
	auto output3 = s.calcEquation(input31, input32, input33);

    cout << "*************output*************" << endl;
    printContainer(output);
    printContainer(output1);
    printContainer(output2);
    printContainer(output3);

    return 0;
}
