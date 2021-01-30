package main

import (
	"fmt"
)

func max(a int, b int) int {
	if a < b {
		return b
	}
	return a
}

func jump(nums []int) int {
	lenNum := len(nums)
	var curMaxReach, i, jump int

	for curMaxReach < lenNum-1 {
		jump++

		prevMaxReach := curMaxReach
		for ; i <= prevMaxReach; i++ {
			curMaxReach = max(curMaxReach, i+nums[i])
		}
	}

	return jump
}

func main() {
	output := jump([]int{2, 3, 1, 1, 4})
	output1 := jump([]int{2, 3, 0, 1, 4})
	output2 := jump([]int{4, 0, 3, 4, 1, 4, 2, 1})

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
