#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
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
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> target;
        for (auto c : s1) {
            target[c]++;
        }

        int left = -1;
        int right = 0;
        int validCharCount = 0;
        unordered_map<char, int> window;

        while (right < s2.size()) {
            char rChar = s2[right];
            if (target.find(rChar) != target.end()) {
                if (left == -1) {  // create a new window
                    left = right;
                }

                window[rChar]++;
                if (window[rChar] == target[rChar]) {
                    validCharCount++;
                }

                if (right - left == s1.size()) {  // exceed the length of s1,
                                                  // update the left index
                    int lChar = s2[left];
                    if (window[lChar] == target[lChar]) {
                        validCharCount--;
                    }
                    window[lChar]--;
                    left++;
                }

                if (validCharCount == target.size()) {
                    return true;
                }

            } else {  // clear the window
                left = -1;
                window.clear();
                validCharCount = 0;
            }
            right++;
        }

        return false;
    }
};

int main() {
    Solution s;

    auto output = s.checkInclusion("ab", "eidbaooo");

    auto output1 = s.checkInclusion("ab", "eidboaoo");

    auto output2 = s.checkInclusion("hello", "ooolleoooleh");

    auto output3 = s.checkInclusion(
        "trfhcbogglim",
        "amwfpqwfwkarvhfcisywzaahtbdbuicxmjseeoudwfcdxetbmacayfikolbdxkocezhalf"
        "hxabwvuddcyazwiqiwefgolzvrpdxcuskpsmwhslpeygjrvvajajafppcwkqhxwkigemfu"
        "llbqkvuqwfnqnhxiltyfcpfdyumfwyelmtzbdccmbvxedgfimmsqwxmopvxmuonuzyzlhp"
        "eunailpydcqybghdwvqxrpautsvrhfxprdqlgzownvincoxjnjwrqrdgpegtgvlifbbaut"
        "kfqbhqiftbmxadvorqjnqlsceuctazxgofmchypspqvwyzoeejqfkvvwftvagajafmafvy"
        "tslubpzalnahjknarjswkxmzzlmlokrifiopjcamvynmmuegnzvveetssuucqclbzxgjwb"
        "sflyelpdsvzicdnlenuxggcsrckfdixsqcjrzsbztgvxbpktlbdqrcqoatgxqhwehqiuqj"
        "nldursyzplwlcdvwrmlknviqtexwgqovwbcdugdblakufxcapvkvhraacetowtcypfxlvw"
        "mwdafesfgqezspbvqzxicblrdsmmdzunpcmzvysgbnspuldkppwlrsrnnewwjquhzrodms"
        "bgbycvrzmtnskyuqqoqkxyakojewbbtntbdjuncpgbwgrtvewyscyujnqtpuaulrnjqmdu"
        "jxydwzfyqfnxmjqogibxqeuqdxsdjjpootpzmhcvoeyvdspktyjzadkfwcdulsuktottgp"
        "vptjfydvpdxoznzhbkmitaiywqklwrktmzsyndnqmtapaaadzkynfxiwqxtekcbkmcwhww"
        "dylvoxosxcexeceavpfptdlkyinhdobrnxfdbtuomjojmzeytlntkundrydqmkiayounnb"
        "hfxrlriuatzumgfcyniicwhtsaffhnxamwjtgbxvewtgovvrjvblrlvrghyoiicgvyorzj"
        "gecmxqeiwpuubfrnkmpynwywqczqdpeinebgfyrhouvifthoaariadurpbrexbfnuwgkbm"
        "gowjuaysnmidptzetckscxvxttdogpywxdvaktmkispgyghfazxyxslyjhqorndzpjepmw"
        "iuisfhvacnpkthbfrasndrfkfuhpetlnfugmqhqpvtvlwumhxduxxmugstcbksvqholoth"
        "hftzungtxdysudnixkzekpdlgddnvyfuitcedxvjfsjxhbcrenufafxzdrumeavumdbvvg"
        "podgtsjzznxkpbfltchmogigordwcpcanomjznfmsxpzqgxigjpybooxsgyiuxskowkdpy"
        "pnzpgebowqefomcpmfilixgzvoffvmcypgyrwhwaelfpclzaoldlaimtnszckziyqewrte"
        "wpfyhphxruytifwtodznvxmxwoibqvtmynpqshnmiymrayaenoiknjqzwoltqhaganjdwz"
        "kncathqrgcigaguimqgznupmsikurxjltfydqiozmddxydgtsvwoloqtlqhryfqmcsfetv"
        "tjkauyjgillobotqfhzsyjtcjsiqxhwoaucluagbltdwroayydlwzytpqlsxkbrgcavvaq"
        "vlggewskeflsejklqexjvcudzaanxrgnkwygokcuxkvypsh");

    cout << "*************output*************" << endl;
    cout << output << endl;
    cout << output1 << endl;
    cout << output2 << endl;
    cout << output3 << endl;

    return 0;
}
