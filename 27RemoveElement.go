package main

import (
	"fmt"
)

func removeElement(nums []int, val int) int {
	start := 0
	end := len(nums) - 1
	var output int

	for start <= end {
		if start == end {
			if nums[start] == val {
				output = start
			} else {
				output = start + 1
			}
			break
		}

		if nums[start] == val {
			tmp := nums[start]
			nums[start] = nums[end]
			nums[end] = tmp
			end--
		} else {
			start++
		}
	}

	return output
}

func main() {
	output := removeElement([]int{3, 2, 2, 3}, 3)
	output1 := removeElement([]int{0, 1, 2, 2, 3, 0, 4, 2}, 2)

	fmt.Println("\n******** output *********\n", output, output1)
}
