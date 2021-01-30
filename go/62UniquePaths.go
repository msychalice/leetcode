package main

import (
	"fmt"
)

func uniquePaths(m int, n int) int {
	if m == 1 && n == 1 {
		return 1
	}

	// m and n are both less or equal to 100,
	// we can combine them into one integer that can be used as the key of the map of intermediate results
	funcCombineCoordinate := func(x int, y int) int {
		return x*1000 + y
	}

	mapIntermediateResult := make(map[int]int)

	var findPaths func(int, int) int
	findPaths = func(gridWidth int, gridHeight int) int {
		if gridWidth == 0 || gridHeight == 0 { //invalid grid
			return 0
		}
		if (gridWidth == 1 && gridHeight == 2) ||
			(gridWidth == 2 && gridHeight == 1) { // adjacent to the end
			return 1
		}

		var combinedCoordinate = funcCombineCoordinate(gridWidth, gridHeight)
		if cachedResult, ok := mapIntermediateResult[combinedCoordinate]; ok {
			return cachedResult
		}

		result := findPaths(gridWidth-1, gridHeight) + findPaths(gridWidth, gridHeight-1)
		mapIntermediateResult[combinedCoordinate] = result

		return result
	}

	return findPaths(m, n)
}

func main() {
	output := uniquePaths(3, 7)
	output1 := uniquePaths(3, 2)
	output2 := uniquePaths(7, 3)
	output3 := uniquePaths(3, 3)

	fmt.Println("\n******** output *********\n", output, output1, output2, output3)
}
