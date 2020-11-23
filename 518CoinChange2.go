package main

import (
	"fmt"
)

func change(amount int, coins []int) int {
	cachedResult := make([]int, amount+1)
	cachedResult[0] = 1

	for i := 1; i <= len(coins); i++ {
		curCoin := coins[i-1]
		for j := curCoin; j <= amount; j++ {
			cachedResult[j] += cachedResult[j-curCoin]
		}
	}

	return cachedResult[amount]
}

func main() {
	output := change(5, []int{1, 2, 5})
	output1 := change(3, []int{2})
	output2 := change(10, []int{10})
	output3 := change(0, []int{})

	fmt.Println("\n******** output *********\n", output, output1, output2, output3)
}
