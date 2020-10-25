#include <iostream>
#include <set>
#include <vector>
#include <iterator>

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
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> output;
        multiset<int> window(nums.begin(), nums.begin() + k);
        auto leftMid = next(window.begin(), (k-1)/2);
        output.push_back((static_cast<double>(*leftMid) + *next(leftMid, (k+1)%2)) / 2.0);

        printContainer(nums);
        printContainer(window);

        for (int i = 1; i <= nums.size() - k; i++) {
            window.insert(nums[i+k-1]);

            // adjust the leftMid iterator after insertion
            if (k%2==0) {
                if (nums[i+k-1] >= *leftMid) {
                    leftMid++;
                } else {
                    //empty
                }
            } else {
                if (nums[i+k-1] < *leftMid) {
                    leftMid--;
                } else {
                    //empty
                }
            }
            //cout << "after insert " << nums[i+k-1] << " leftMid " << distance(window.begin(), leftMid) << endl;

            //adjest the leftMid iterator before erasion
            if ((k+1)%2==0) {
                if (nums[i-1] < *leftMid) {
                    leftMid++;
                } else if (nums[i-1] > *leftMid) {
                    //empty
                } else if (nums[i-1] == *leftMid) {
                    //always increase leftMid, no matter if it is equal to window.begin()
                    //or its left neighbor element has the same value or not
                    leftMid++;
                }
            } else {
                if (nums[i-1] > *leftMid) {
                    leftMid--;
                } else if (nums[i-1] < *leftMid) {
                    //empty
                } else if (nums[i-1] == *leftMid) {
                    if (leftMid == window.begin()) {
                        leftMid++;
                    } else {
                        if (*prev(leftMid, 1) != *leftMid) {
                            leftMid--;
                        } else {
                            //empty
                        }
                    }
                }
            }

            //cout << "before erase " << nums[i-1] << " leftMid " << distance(window.begin(), leftMid) << endl;

            window.erase(window.lower_bound(nums[i-1]));
            //cout << "after erase " << nums[i-1] << " leftMid " << distance(window.begin(), leftMid) << endl;
            printContainer(window);

            output.push_back((static_cast<double>(*leftMid) + *next(leftMid, (k+1)%2)) / 2.0);
        }

        return output;
    }

};

int main(){
    Solution s;

    auto vecInput = vector<int>{1,3,-1,-3,5,3,6,7};
    auto output = s.medianSlidingWindow(vecInput, 3);

    auto vecInput1 = vector<int>{9,7,0,3,9,8,6,5,7,6};
    auto output1 = s.medianSlidingWindow(vecInput1, 2);

    auto vecInput2 = vector<int>{1,1,1,1};
    auto output2 = s.medianSlidingWindow(vecInput2, 2);

    cout << "*************output*************" << endl;
    printContainer(output);
    printContainer(output1);
    printContainer(output2);

    return 0;
}
