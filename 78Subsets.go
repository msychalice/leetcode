package main

import (
	"fmt"
)

func subsets(nums []int) [][]int {
	output := [][]int{{}}
	lenNums := len(nums)

	var getCompositions func(int, int) [][]int
	getCompositions = func(totalNum int, selectNum int) [][]int {
		compositions := [][]int{}
		if selectNum == 0 || selectNum > totalNum {
			return compositions
		}

		for i := 0; i <= totalNum-selectNum; i++ {
			compositionsOfAllRightNums := getCompositions(totalNum-i-1, selectNum-1)
			if len(compositionsOfAllRightNums) == 0 {
				compositions = append(compositions, []int{i})
				continue
			}

			for _, compOfAllRightNums := range compositionsOfAllRightNums {
				comp := []int{}
				comp = append(comp, i)
				for _, selectNums := range compOfAllRightNums {
					comp = append(comp, selectNums+i+1)
				}
				compositions = append(compositions, comp)
			}
		}
		return compositions
	}

	for i := 1; i <= lenNums; i++ {
		compositions := getCompositions(lenNums, i)
		for _, comp := range compositions {
			finalComp := []int{}
			for _, index := range comp {
				finalComp = append(finalComp, nums[index])
			}
			output = append(output, finalComp)
		}
	}

	return output
}

func main() {
	output := subsets([]int{1, 2, 3})

	fmt.Println("\n******** output *********\n", output)
}
