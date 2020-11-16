package main

import (
	"fmt"
)

func removeDuplicates(nums []int) int {
	if len(nums) == 0 {
		return 0
	}

	cur := nums[0]
	nextIndex := 1
	curDuplicates := 0

	for i := 1; i < len(nums); i++ {
		if nums[i] != cur {
			nums[nextIndex] = nums[i]
			nextIndex++
			cur = nums[i]
			curDuplicates = 0
		} else {
			curDuplicates++
			if curDuplicates <= 1 {
				nums[nextIndex] = nums[i]
				nextIndex++
				cur = nums[i]
			} else {
				// empty
			}
		}
	}

	return nextIndex
}

func main() {
	output := removeDuplicates([]int{1, 1, 1, 2, 2, 3})
	output1 := removeDuplicates([]int{0, 0, 1, 1, 1, 2, 3, 3})

	fmt.Println("\n******** output *********\n", output, output1)
}
