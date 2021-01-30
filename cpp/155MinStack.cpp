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

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() :
        m_min(0) {

    }

    void push(int x) {
        if (m_stack.size() == 0) {
            m_stack.push(x);
            m_min = x;
        } else {
            if (m_min >= x) {
                m_stack.push(m_min);
                m_min = x;
            }
            m_stack.push(x);
        }
    }

    void pop() {
        if (top() == m_min) {
            m_stack.pop();
            if (!m_stack.empty()) {
                m_min = m_stack.top();
                m_stack.pop();
            }
        } else {
            m_stack.pop();
        }
    }

    int top() {
        return m_stack.top();
    }

    int getMin() {
        return m_min;
    }
private:
    int m_min;
    stack<int> m_stack;
};

int main(){
    MinStack* obj = new MinStack();
    obj->push(3);
    cout << "top" << obj->top() << endl;
    obj->push(2);
    cout << "min" << obj->getMin() << endl;
    obj->push(4);
    cout << "min" << obj->getMin() << endl;
    obj->pop();
    cout << "min" << obj->getMin() << endl;
    obj->pop();
    cout << "min" << obj->getMin() << endl;

    cout << "*************output*************" << endl;

    return 0;
}

