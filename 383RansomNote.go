package main

import (
	"fmt"
)

func canConstruct(ransomNote string, magazine string) bool {
	if len(ransomNote) > len(magazine) {
		return false
	}

	charCount := make([]int, 26)

	for i := 0; i < len(magazine); i++ {
		charCount[magazine[i]-'a']++
	}

	for i := 0; i < len(ransomNote); i++ {
		if charCount[ransomNote[i]-'a'] == 0 {
			return false
		} else {
			charCount[ransomNote[i]-'a']--
		}
	}
	return true
}

func main() {
	output := canConstruct("a", "b")
	output1 := canConstruct("aa", "ab")
	output2 := canConstruct("aa", "aab")

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
