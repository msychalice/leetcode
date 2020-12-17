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
    int findKthLargestUsingMaxHeap(vector<int>& nums, int k) {
        make_heap(nums.begin(), nums.end());

        int output = 0;
        for (;k > 0; k--) {
            output = nums.front();
            pop_heap(nums.begin(), nums.end());
            nums.pop_back();
        }

        return output;
    }

    // Quick selection
    int findKthLargest(vector<int>& nums, int k) {
        // return pivot index
        // nums[lo...p-1] < nums[p] < nums[p+1...hi]
        function<int(vector<int>&, int, int)> partition = [](vector<int>& nums,
                                                             int lo, int hi) {
            if (lo == hi) {
                return lo;
            }

            int pivot = nums[lo];  // initial pivot index is lo

            // two pointers
            int i = lo;
            int j = hi + 1;

            while (true) {
                while (nums[++i] < pivot) {
                    if (i == hi) {
                        break;
                    }
                }
                while (nums[--j] > pivot) {
                    if (j == lo) {
                        break;
                    }
                }

                if (i >= j) {
                    break;
                }

                // Reaching at this point, we must have
                // nums[i] >= pivot and nums[j] <= pivot,
                // so we need to swap them
                swap(nums[i], nums[j]);
            }

            // swap the pivot to the correct position
            swap(nums[lo], nums[j]);
            return j;
        };

        // randomize nums, make sure this algrothm won't be in the worst case,
        // which is O(n*n)
        for (int i = 0; i < nums.size(); i++) {
            swap(nums[0], nums[rand() % nums.size()]);
        }

        // convert the original kth largest to the correct index
        k = nums.size() - k;
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            int p = partition(nums, lo, hi);
            if (p < k) {  //
                lo = p + 1;
            } else if (p > k) {
                hi = p - 1;
            } else {
                return nums[p];
            }
        }
        return -1;
    }
};

int main(){
    Solution s;

    vector<int> input{3, 2, 1, 5, 6, 4};
    cout << s.findKthLargestUsingMaxHeap(input, 2) << endl;
    vector<int> input1{3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << s.findKthLargestUsingMaxHeap(input1, 4) << endl;

    vector<int> input2{3, 2, 1, 5, 6, 4};
    cout << s.findKthLargest(input2, 2) << endl;
    vector<int> input3{3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << s.findKthLargest(input3, 4) << endl;

    cout << "*************output*************" << endl;

    return 0;
}
