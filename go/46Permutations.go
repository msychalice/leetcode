package main

import (
	"fmt"
)

func permute(nums []int) [][]int {
	var output [][]int
	var curPath []int

	var backtrack func()
	backtrack = func() {
		if len(nums) == 0 {
			//copy curPath to ouput, don't directly append curPath into ouput
			path := make([]int, len(curPath))
			copy(path, curPath)
			output = append(output, path)
			return
		}

		for i := len(nums) - 1; i >= 0; i-- {
			curSelection := nums[i]
			curPath = append(curPath, curSelection)
			nums = append(nums[:i], nums[i+1:]...)
			backtrack()
			// add it back at the original index
			nums = append(nums[:i+1], nums[i:]...)
			nums[i] = curSelection
			curPath = curPath[:len(curPath)-1]
		}
	}

	backtrack()

	return output
}

func main() {
	output := permute([]int{1, 2, 3})
	output1 := permute([]int{0, 1})
	output2 := permute([]int{1})

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
