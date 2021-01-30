package main

import (
	"fmt"
)

func countNegatives(grid [][]int) int {
	var binarySearchForTheFirstNegative func([]int, int, int) int
	binarySearchForTheFirstNegative = func(nums []int, beginIndex int, endIndex int) int {
		if beginIndex >= endIndex {
			return -1
		}
		if endIndex-beginIndex == 1 {
			if nums[beginIndex] < 0 {
				return beginIndex
			}
			return -1
		}

		mid := (endIndex-beginIndex)/2 + beginIndex
		curNum := nums[mid]
		prevNum := nums[mid-1]
		if curNum < 0 {
			if prevNum >= 0 {
				return mid
			} else {
				return binarySearchForTheFirstNegative(nums, beginIndex, mid)
			}
		} else {
			return binarySearchForTheFirstNegative(nums, mid+1, endIndex)
		}
	}

	gridWidth := len(grid[0])
	gridHeight := len(grid)

	firstNums := []int{}
	for i := 0; i < len(grid); i++ {
		firstNums = append(firstNums, grid[i][0])
	}
	//fmt.Println("first num", firstNums)

	var negativeCount int
	firstNegativeRow := binarySearchForTheFirstNegative(firstNums, 0, gridHeight)
	//fmt.Println("firstNegativeRow", firstNegativeRow)
	if firstNegativeRow != -1 {
		negativeCount = (gridHeight - firstNegativeRow) * gridWidth
	} else {
		firstNegativeRow = gridHeight
	}

	for j := 0; j < firstNegativeRow; j++ {
		firstNegativeColumn := binarySearchForTheFirstNegative(grid[j], 0, gridWidth)
		if firstNegativeColumn != -1 {
			negativeCount += gridWidth - firstNegativeColumn
		}
	}

	return negativeCount
}

func main() {
	output := countNegatives([][]int{{4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}})
	output1 := countNegatives([][]int{{3, 2}, {1, 0}})
	output2 := countNegatives([][]int{{1, -1}, {-1, -1}})
	output3 := countNegatives([][]int{{-1}})
	output4 := countNegatives([][]int{{3, 3}, {3, -1}, {3, -2}, {-3, -3}, {-3, -3}})

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4)
}
