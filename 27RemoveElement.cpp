#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <utility>

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
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        for (int i = 0; i < len;) {
            if (nums[i] == val) {
                swap(nums[i], nums[len-1]);
                len--;
            } else {
                i++;
            }
        }

        return len;
    }
};

int main(){
    Solution s;

    auto vecInput = vector<int>{3, 2, 2, 3};
    auto output = s.removeElement(vecInput, 3);

    auto vecInput1 = vector<int>{0, 1, 2, 2, 3, 0, 4, 2};
    auto output1 = s.removeElement(vecInput1, 2);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;

    return 0;
}
