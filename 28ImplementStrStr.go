package main

import (
	"fmt"
)

func strStr(haystack string, needle string) int {
	lenHeyStack := len(haystack)
	lenNeedle := len(needle)
	if lenHeyStack < lenNeedle {
		return -1
	}
	if lenNeedle == 0 {
		return 0
	}

	output := -1

result:
	for i := 0; i < lenHeyStack-(lenNeedle-1); i++ {
		for j := 0; j < lenNeedle; j++ {
			if haystack[i+j] == needle[j] {
				if j == lenNeedle-1 {
					output = i
					break result
				} else {
					continue
				}
			} else {
				break
			}
		}
	}

	return output
}

func main() {
	output := strStr("hello", "ll")
	output1 := strStr("aaaaa", "bba")
	output2 := strStr("", "")
	output3 := strStr("mississippi", "issipi")
	output4 := strStr("a", "a")

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4)
}
