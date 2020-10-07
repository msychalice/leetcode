package main

import (
	"fmt"
)

func lengthOfLongestSubstring(s string) int {
	strLen := len(s)
	fmt.Println(strLen)
	var maxSubstrLen int

	if strLen == 0 {
		return 0
	}

	curSubStr := make(map[byte]int)
	var headIndex, endIndex, curSubStrLen int

	for ; endIndex < strLen; endIndex++ {
		if charIndex, ok := curSubStr[s[endIndex]]; ok {
			for i := headIndex; i < charIndex+1; i++ {
				delete(curSubStr, s[i])
			}
			headIndex = charIndex + 1
		}

		curSubStr[s[endIndex]] = endIndex

		curSubStrLen = endIndex - headIndex + 1
		if curSubStrLen > maxSubstrLen {
			maxSubstrLen = curSubStrLen
		}
	}

	return maxSubstrLen
}

func main() {
	output := lengthOfLongestSubstring("abcabcbb")
	output1 := lengthOfLongestSubstring("bbbbb")
	output2 := lengthOfLongestSubstring("pwwkew")
	output3 := lengthOfLongestSubstring("")
	output4 := lengthOfLongestSubstring(" ")
	output5 := lengthOfLongestSubstring("a")

	fmt.Println("\n******** output *********\n",
		output, output1, output2, output3, output4, output5)

}
