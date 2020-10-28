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

/*
// Definition for a Node.
*/
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<Node*, Node*> visited;

        function<Node*(Node*)> clone = [&clone, &visited](Node* srcNode)->Node* {
            if (srcNode == nullptr) {
                return nullptr;
            }

            auto it = visited.find(srcNode);
            if (it != visited.end()) {
                return it->second;
            }

            Node* destNode = new Node(srcNode->val);

            visited.emplace(srcNode, destNode);

            for (auto n : srcNode->neighbors) {
                destNode->neighbors.push_back(clone(n));
            }

            return destNode;
        };

        return clone(node);
    }
};

int main(){
    Solution s;
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    node1.neighbors = vector<Node*>{&node2, &node4};
    node2.neighbors = vector<Node*>{&node1, &node3};
    node3.neighbors = vector<Node*>{&node2, &node4};
    node4.neighbors = vector<Node*>{&node1, &node3};
	auto output = s.cloneGraph(&node1);

    Node node11(1);
	auto output1 = s.cloneGraph(&node11);

	auto output2 = s.cloneGraph(nullptr);

    Node node31(1);
    Node node32(2);
    node31.neighbors = vector<Node*>{&node2};
    node32.neighbors = vector<Node*>{&node1};
	auto output3 = s.cloneGraph(&node31);

    cout << "*************output*************" << endl;

    return 0;
}

