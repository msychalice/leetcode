package main

import (
	"fmt"
)

func plusOne(digits []int) []int {
	advancedNum := 0 //store the advanced number
	for i := len(digits) - 1; i >= 0; i-- {
		var sum int
		if i == len(digits)-1 {
			sum = digits[i] + 1
		} else {
			sum = digits[i] + advancedNum
		}

		if sum == 10 {
			digits[i] = 0
			advancedNum = 1

			if i == 0 {
				digits = append([]int{advancedNum}, digits...)
				break
			}
		} else {
			digits[i] = sum
			advancedNum = 0
			break
		}
	}

	return digits
}

func main() {
	output := plusOne([]int{1, 2, 3})
	output1 := plusOne([]int{4, 3, 2, 1})
	output2 := plusOne([]int{0})
	output3 := plusOne([]int{9, 9})

	fmt.Println("\n******** output *********\n", output, output1, output2, output3)
}
