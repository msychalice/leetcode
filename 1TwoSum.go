package main

import (
	"fmt"
)

func twoSum(nums []int, target int) []int {
	mapNums := make(map[int][]int)
	for i := 0; i < len(nums); i++ {
		mapNums[nums[i]] = append(mapNums[nums[i]], i)
	}

	var firstNumIndex, secondNumIndex int
output:
	for curFirstNumIndex := 0; curFirstNumIndex < len(nums); curFirstNumIndex++ {
		secondNumCandidates, ok := mapNums[target-nums[curFirstNumIndex]]
		if ok {
			for _, curSecondNumIndex := range secondNumCandidates {
				if curSecondNumIndex != curFirstNumIndex {
					firstNumIndex = curFirstNumIndex
					secondNumIndex = curSecondNumIndex
					break output
				}
			}
		}
	}
	return []int{firstNumIndex, secondNumIndex}
}

func main() {
	output := twoSum([]int{3, 2, 4}, 6)

	fmt.Println("\n******** output *********\n", output)
}
