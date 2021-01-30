package main

import (
	"fmt"
)

func climbStairs(n int) int {
	waysFor2Less := 1
	waysFor1Less := 2
	var curWays int
	if n == 1 {
		curWays = waysFor2Less
	} else if n == 2 {
		curWays = waysFor1Less
	} else {
		for i := 3; i <= n; i++ {
			curWays = waysFor1Less + waysFor2Less
			waysFor2Less = waysFor1Less
			waysFor1Less = curWays
		}
	}
	return curWays
}

func main() {
	output := climbStairs(3)
	output1 := climbStairs(4)

	fmt.Println("\n******** output *********\n", output, output1)
}
