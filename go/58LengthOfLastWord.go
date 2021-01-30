package main

import (
	"fmt"
	"strings"
	"unicode"
)

func lengthOfLastWord(s string) int {
	cur := strings.LastIndexFunc(s, unicode.IsLetter)

	if cur == -1 {
		return 0
	}

	var lenLastWord int
	for ; cur >= 0; cur-- {
		if s[cur] != ' ' {
			lenLastWord++
		} else {
			break
		}
	}

	return lenLastWord
}

func main() {
	output := lengthOfLastWord("Hello World")
	output1 := lengthOfLastWord("a")

	fmt.Println("\n******** output *********\n", output, output1)
}
