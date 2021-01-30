package main

import (
	"fmt"
)

func longestCommonPrefix(strs []string) string {
	lenStrs := len(strs)
	if lenStrs == 0 {
		return ""
	}
	if lenStrs == 1 {
		return strs[0]
	}
	if lenStrs > 2 {
		return longestCommonPrefix([]string{longestCommonPrefix(strs[:lenStrs-1]), strs[lenStrs-1]})
	}

	output := []byte{}

	for i := 0; i < len(strs[0]) && i < len(strs[1]); i++ {
		if strs[0][i] == strs[1][i] {
			output = append(output, byte(strs[0][i]))
		} else {
			break
		}
	}

	return string(output)
}

func main() {
	output := longestCommonPrefix([]string{"flower", "flow", "flight"})
	output1 := longestCommonPrefix([]string{"dog", "racecar", "car"})
	output2 := longestCommonPrefix([]string{"cir", "car"})

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
