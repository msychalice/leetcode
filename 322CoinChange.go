package main

import (
	"fmt"
	"sort"
)

func coinChange(coins []int, amount int) int {
	if amount == 0 {
		return 0
	}

	sort.Ints(coins)
	coinCount := -1

	mapSolution := make(map[int]int)
	mapSolution[0] = 0

	for curAmount := 1; curAmount <= amount; curAmount++ {
		for n := 0; n < len(coins); n++ {
			if curAmount >= coins[n] {
				if solution, ok := mapSolution[curAmount-coins[n]]; ok {
					// need to compare with the existing solution, only update it if the new solution is smaller
					if _, ok := mapSolution[curAmount]; ok {
						if mapSolution[curAmount] > solution+1 {
							mapSolution[curAmount] = solution + 1
						}
					} else {
						mapSolution[curAmount] = solution + 1
					}
				}
			} else {
				break
			}
		}
	}

	fmt.Println(mapSolution)

	if solution, ok := mapSolution[amount]; ok {
		coinCount = solution
	}

	return coinCount
}

func main() {
	output := coinChange([]int{1, 2, 5}, 11)
	output1 := coinChange([]int{2}, 3)
	output2 := coinChange([]int{1}, 0)
	output3 := coinChange([]int{1}, 1)
	output4 := coinChange([]int{1}, 2)
	output5 := coinChange([]int{186, 419, 83, 408}, 6249)

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4, output5)
}
