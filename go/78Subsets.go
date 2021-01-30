package main

import (
	"fmt"
)

func subsets(nums []int) [][]int {
	var output [][]int
	output = append(output, []int{})

	var curPath []int

	var backtrack func([]int)
	backtrack = func(curChoice []int) {
		for i := 0; i < len(curChoice); i++ {
			curPath = append(curPath, curChoice[i])
			tmp := make([]int, len(curPath))
			copy(tmp, curPath)
			output = append(output, tmp)
			backtrack(curChoice[i+1:])
			curPath = curPath[:len(curPath)-1]
		}
	}

	backtrack(nums)

	return output
}

func main() {
	output := subsets([]int{1, 2, 3})

	fmt.Println("\n******** output *********\n", output)
}
