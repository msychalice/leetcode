package main

import (
	"fmt"
	"strconv"
	"strings"
)

func compareVersion(version1 string, version2 string) int {
	subStrings1 := strings.Split(version1, ".")
	subStrings2 := strings.Split(version2, ".")

	result := 0
	for i := 0; i < len(subStrings1) || i < len(subStrings2); i++ {
		var num1, num2 int
		if i < len(subStrings1) {
			num1, _ = strconv.Atoi(subStrings1[i])
		}
		if i < len(subStrings2) {
			num2, _ = strconv.Atoi(subStrings2[i])
		}

		if num1 > num2 {
			result = 1
			break
		}
		if num1 < num2 {
			result = -1
			break
		}
	}

	return result
}

func main() {
	output := compareVersion("1.01", "1.001")
	output1 := compareVersion("1.0", "1.0.0")
	output2 := compareVersion("0.1", "1.1")
	output3 := compareVersion("1.0.1", "1")
	output4 := compareVersion("7.5.2.4", "7.5.3")

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4)
}
