package main

import (
	"fmt"
)

func subsets(nums []int) [][]int {
	output := [][]int{{}}
	lenNums := len(nums)

	var getCombinations func(int, int) [][]int
	getCombinations = func(totalNum int, selectNum int) [][]int {
		combinations := [][]int{}
		if selectNum == 0 || selectNum > totalNum {
			return combinations
		}

		for i := 0; i <= totalNum-selectNum; i++ {
			combinationsOfAllRightNums := getCombinations(totalNum-i-1, selectNum-1)
			if len(combinationsOfAllRightNums) == 0 {
				combinations = append(combinations, []int{i})
				continue
			}

			for _, combOfAllRightNums := range combinationsOfAllRightNums {
				comb := []int{}
				comb = append(comb, i)
				for _, selectNums := range combOfAllRightNums {
					comb = append(comb, selectNums+i+1)
				}
				combinations = append(combinations, comb)
			}
		}
		return combinations
	}

	for i := 1; i <= lenNums; i++ {
		combinations := getCombinations(lenNums, i)
		for _, comb := range combinations {
			finalComb := []int{}
			for _, index := range comb {
				finalComb = append(finalComb, nums[index])
			}
			output = append(output, finalComb)
		}
	}

	return output
}

func main() {
	output := subsets([]int{1, 2, 3})

	fmt.Println("\n******** output *********\n", output)
}
