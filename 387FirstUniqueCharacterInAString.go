package main

import (
	"fmt"
)

func firstUniqChar(s string) int {
	mapFoundChars := make(map[byte]int)
	sliFoundChars := []byte{}
	mapNonUniqueChars := make(map[byte]bool)
	firstUniqCharIndex := -1

	for i, c := range s {
		if _, ok := mapFoundChars[byte(c)]; ok {
			mapNonUniqueChars[byte(c)] = true
		} else {
			mapFoundChars[byte(c)] = i
			sliFoundChars = append(sliFoundChars, byte(c))
		}
	}

	fmt.Println(mapFoundChars)
	fmt.Println(sliFoundChars)
	fmt.Println(mapNonUniqueChars)

	for _, char := range sliFoundChars {
		if _, ok := mapNonUniqueChars[char]; ok {
			continue
		} else {
			firstUniqCharIndex = mapFoundChars[char]
			break
		}
	}

	return firstUniqCharIndex
}

func main() {
	output := firstUniqChar("leetcode")
	output1 := firstUniqChar("loveleetcode")

	fmt.Println("\n******** output *********\n", output, output1)
}
