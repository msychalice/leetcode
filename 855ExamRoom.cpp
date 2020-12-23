#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
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

class ExamRoom {
public:
    ExamRoom(int N)
        : m_size(N), m_setSegment([this](pair<int, int> a, pair<int, int> b) {
              int distA = distance(a);
              int distB = distance(b);
              if (distA == distB) {
                  // attention
                  // the less the begin is, the more back the segment will be
                  return a.first > b.first;
              }
              return distA < distB;
          }) {
        // add the initial segment [-1, m_size]
        // -1 and m_size are virtual seats
        auto newSegment = make_pair(-1, m_size);
        m_setSegment.insert(newSegment);
        m_mapBeginSegment.insert(make_pair(-1, newSegment));
        m_mapBackSegment.insert(make_pair(m_size, newSegment));
    }

    int seat() {
        auto maxSegment = *(m_setSegment.rbegin());
        int middle = getMiddle(maxSegment);

        // remove old segment
        m_setSegment.erase(maxSegment);
        m_mapBeginSegment.erase(maxSegment.first);
        m_mapBackSegment.erase(maxSegment.second);

        // add new segments
        auto leftSegment = make_pair(maxSegment.first, middle);
        m_setSegment.insert(leftSegment);
        m_mapBeginSegment.insert(make_pair(leftSegment.first, leftSegment));
        m_mapBackSegment.insert(make_pair(leftSegment.second, leftSegment));
        auto rightSegment = make_pair(middle, maxSegment.second);
        m_setSegment.insert(rightSegment);
        m_mapBeginSegment.insert(make_pair(rightSegment.first, rightSegment));
        m_mapBackSegment.insert(make_pair(rightSegment.second, rightSegment));

        return middle;
    }

    void leave(int p) {
        int newBack = m_mapBeginSegment[p].second;
        int newBegin = m_mapBackSegment[p].first;

        // remove old segments
        m_setSegment.erase(make_pair(newBegin, p));
        m_mapBeginSegment.erase(newBegin);
        m_mapBackSegment.erase(p);
        m_setSegment.erase(make_pair(p, newBack));
        m_mapBeginSegment.erase(p);
        m_mapBackSegment.erase(newBack);

        // add new segment
        auto newSegment = make_pair(newBegin, newBack);
        m_setSegment.insert(newSegment);
        m_mapBeginSegment.insert(make_pair(newBegin, newSegment));
        m_mapBackSegment.insert(make_pair(newBack, newSegment));
    }

private:
    int distance(pair<int, int>& s) const {
        if (s.second == s.first + 1) {  // there is no space in the segment
            return 0;
        }
        if (s.first == -1) {
            return s.second;
        }
        if (s.second == m_size) {
            return s.second - s.first - 1;
        }
        return (s.second - s.first) / 2;
    }

    int getMiddle(pair<int, int>& s) const {
        int dist = distance(s);
        if (dist == 0) {
            return -1;
        }

        if (s.first == -1) {
            return s.second - dist;
        }
        return s.first + dist;
    }

    int m_size;
    // key is the begin seat of a segment {begin, {begin, back}}
    unordered_map<int, pair<int, int>> m_mapBeginSegment;
    // key is the back seat of a segment {back, {begin, back}}
    unordered_map<int, pair<int, int>> m_mapBackSegment;
    set<pair<int, int>, function<bool(pair<int, int>, pair<int, int>)>>
        m_setSegment;  // self defined comparison function
};

int main(){
    ExamRoom e(10);
    cout << e.seat() << endl;
    cout << e.seat() << endl;
    cout << e.seat() << endl;
    cout << e.seat() << endl;
    e.leave(4);
    cout << e.seat() << endl;

    cout << "*************output*************" << endl;

    return 0;
}
