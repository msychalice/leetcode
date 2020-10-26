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
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) {
            return 0;
        }

        if (needle.size() > haystack.size()) {
            return -1;
        }

        int output = -1;
        for (int i = 0; i <= haystack.size() - needle.size(); i++) {
            bool isSame = true;
            for (int j = 0; j < needle.size(); j++) {
                if (haystack[i+j] != needle[j]) {
                    isSame = false;
                    break;
                }
            }
            
            if (isSame) {
                output = i;
                break;
            }
        }
        return output;
    }
};

int main(){
    Solution s;
    auto output = s.strStr("hello", "ll");
    auto output1 = s.strStr("aaaaa", "bba");
    auto output2 = s.strStr("", "");
    auto output3 = s.strStr("mississippi", "issipi");
    auto output4= s.strStr("a", "a");

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;
    cout << output4 << endl;

    return 0;
}
