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
func canJump(nums []int) bool {
	lenNum := len(nums)
	var curMaxReach, i int

	for curMaxReach < lenNum-1 {
		prevMaxReach := curMaxReach
		for ; i <= prevMaxReach; i++ {
			curMaxReach = max(curMaxReach, i+nums[i])
		}

		if prevMaxReach == curMaxReach {
			return false
		}
	}
	return true
}

func main() {
	output := canJump([]int{2, 3, 1, 1, 4})
	output1 := canJump([]int{3, 2, 1, 0, 4})

	fmt.Println("\n******** output *********\n", output, output1)
}
