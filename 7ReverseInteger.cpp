#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <utility>
#include <cstdlib>
#include <limits>

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
    int reverse(int x) {
        int sign = x < 0 ? -1 : 1;
        x = abs(x);
        uint32_t output = 0;

        while (x > 0) {
            int digit = x % 10;
            x = x / 10;

            uint32_t preOutput = output;
            output = output * 10 + digit;

            if ((output - digit) / 10 != preOutput ||
                (sign > 0 && output > static_cast<uint32_t>(numeric_limits<int>::max())) ||
                (sign < 0 && output > (static_cast<uint32_t>(numeric_limits<int>::max()) + 1))) {
                return 0;
            }
        }

        return sign * static_cast<int>(output);
    }
};

int main(){
    Solution s;
    auto output = s.reverse(123);
    auto output1 = s.reverse(-123);
    auto output2 = s.reverse(120);
    auto output3 = s.reverse(0);
    auto output4 = s.reverse(1534236469);

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;

    return 0;
}
