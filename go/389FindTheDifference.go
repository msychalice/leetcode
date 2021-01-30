package main

import (
	"fmt"
)

func findTheDifference(s string, t string) byte {
	var output byte
	mapByteS := make(map[byte]int)
	mapByteT := make(map[byte]int)

	for _, char := range s {
		var charCount int
		if _, ok := mapByteS[byte(char)]; ok {
			charCount = mapByteS[byte(char)]
		}
		mapByteS[byte(char)] = charCount + 1
	}

	for _, char := range t {
		var charCount int
		if _, ok := mapByteT[byte(char)]; ok {
			charCount = mapByteT[byte(char)]
		}
		mapByteT[byte(char)] = charCount + 1
	}

	for char, countT := range mapByteT {
		if countS, ok := mapByteS[byte(char)]; ok {
			if countS != countT {
				output = char
			}
		} else {
			output = char
		}
	}

	return output
}

func main() {
	output := findTheDifference("abcd", "abcde")
	output1 := findTheDifference("", "y")
	output2 := findTheDifference("a", "aa")
	output3 := findTheDifference("ae", "aea")
	output4 := findTheDifference("abcdereed", "abcedereed")

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4)
}
