package main

import (
	"fmt"
)

func canPartition(nums []int) bool {
	var sum int
	for _, i := range nums {
		sum += i
	}

	if sum%2 != 0 {
		return false
	}

	sum = sum / 2

	cachedResult := make([]bool, sum+1)

	for i := 1; i <= len(nums); i++ {
		curNum := nums[i-1]
		for j := sum; j >= curNum; j-- {
			if j == curNum {
				cachedResult[j] = true
			} else {
				cachedResult[j] = cachedResult[j] || cachedResult[j-curNum]
			}
		}
	}

	return cachedResult[sum]
}

func main() {
	output := canPartition([]int{1, 5, 11, 5})
	output1 := canPartition([]int{1, 2, 3, 5})

	fmt.Println("\n******** output *********\n", output, output1)
}
