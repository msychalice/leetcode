package main

import (
	"fmt"
)

func uniquePathsWithObstacles(obstacleGrid [][]int) int {
	gridWidth := len(obstacleGrid[0])
	gridHeight := len(obstacleGrid)

	if obstacleGrid[gridHeight-1][gridWidth-1] == 1 { // the destination has obstacle
		return 0
	}

	if gridHeight == 1 && gridWidth == 1 { // there is only one grid
		return 1
	}

	// gridWidth and gridHeight are both less or equal to 100,
	// we can combine them into one integer that can be used as the key of the map of intermediate results
	funcCombineCoordinate := func(x int, y int) int {
		return x*1000 + y
	}

	mapIntermediateResult := make(map[int]int)

	var findPaths func(int, int) int
	findPaths = func(startX int, startY int) int {
		if startX < 0 || startX >= gridHeight ||
			startY < 0 || startY >= gridWidth { //invalid grid
			return 0
		}

		if obstacleGrid[startX][startY] == 1 { // hit a obstacle
			return 0
		}

		if (startX == gridHeight-1 && startY == gridWidth-2) ||
			(startX == gridHeight-2 && startY == gridWidth-1) { // adjacent to the end
			return 1
		}

		var combinedCoordinate = funcCombineCoordinate(startX, startY)
		if cachedResult, ok := mapIntermediateResult[combinedCoordinate]; ok {
			return cachedResult
		}

		result := findPaths(startX+1, startY) + findPaths(startX, startY+1)
		mapIntermediateResult[combinedCoordinate] = result

		return result
	}

	return findPaths(0, 0)
}

func main() {
	output := uniquePathsWithObstacles([][]int{
		{0, 0, 0},
		{0, 1, 0},
		{0, 0, 0},
	})

	output1 := uniquePathsWithObstacles([][]int{
		{0, 1},
	})

	fmt.Println("\n******** output *********\n", output, output1)
}
