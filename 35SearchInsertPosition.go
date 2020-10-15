package main

import (
	"fmt"
)

func searchInsert(nums []int, target int) int {
	var binarySearch func(int, int) int
	binarySearch = func(start int, end int) int {
		if start >= end {
			if nums[start] >= target {
				return start
			} else if nums[start] < target {
				return start + 1
			}
		}

		mid := (start + end) / 2 //mid is possibly equal to start
		if nums[mid] == target {
			return mid
		} else if nums[mid] > target {
			return binarySearch(start, mid-1) //mid -1 is possibly smaller than start
		} else {
			return binarySearch(mid+1, end)
		}
	}

	return binarySearch(0, len(nums)-1)
}

func main() {
	output := searchInsert([]int{1, 3, 5, 6}, 5)
	output1 := searchInsert([]int{1, 3, 5, 6}, 2)
	output2 := searchInsert([]int{1, 3, 5, 6}, 7)
	output3 := searchInsert([]int{1, 3, 5, 6}, 0)
	output4 := searchInsert([]int{1}, 0)
	output5 := searchInsert([]int{1, 3}, 0)

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4, output5)
}
