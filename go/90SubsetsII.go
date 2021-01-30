package main

import (
	"fmt"
	"sort"
)

func subsetsWithDup(nums []int) [][]int {
	output := [][]int{{}}
	lenNums := len(nums)

	// (key: number of elements, value: alll the combinations that have the same number of elements)
	mapCombinations := make(map[int][][]int)

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

			isIdenticalSlice := func(sortedSlice1 []int, sortedSlice2 []int) bool {
				len1 := len(sortedSlice1)
				len2 := len(sortedSlice2)
				if len1 != len2 {
					return false
				}

				for i := 0; i < len1; i++ {
					if sortedSlice1[i] != sortedSlice2[i] {
						return false
					}
				}
				return true
			}

			numElements := len(finalComb)
			sort.Ints(finalComb) //sort before comparing for all the existing combinations
			if existingCombinations, ok := mapCombinations[numElements]; ok {
				isDuplicatedComb := false

				for _, existingComb := range existingCombinations {
					if isIdenticalSlice(existingComb, finalComb) {
						isDuplicatedComb = true
						break
					}
				}

				if !isDuplicatedComb {
					mapCombinations[numElements] = append(mapCombinations[numElements], finalComb)
				}
			} else {
				mapCombinations[numElements] = [][]int{finalComb}
			}
		}
	}

	for n := 1; n <= lenNums; n++ {
		for _, combination := range mapCombinations[n] {
			output = append(output, combination)
		}
	}
	return output
}

func main() {
	output := subsetsWithDup([]int{1, 2, 2})

	fmt.Println("\n******** output *********\n", output)
}
