package main

import (
	"fmt"
)

func numIslands(grid [][]byte) int {
	mapReachedGrids := make(map[int]bool)

	combineCoordinate := func(x int, y int) int {
		return x*1000 + y
	}

	var searchIsland func(int, int) bool
	searchIsland = func(x int, y int) bool {
		if x < 0 || x >= len(grid) || y < 0 || y >= len(grid[0]) {
			return false
		}

		if _, ok := mapReachedGrids[combineCoordinate(x, y)]; !ok {
			mapReachedGrids[combineCoordinate(x, y)] = true

			if grid[x][y] == '1' {
				searchIsland(x-1, y)
				searchIsland(x+1, y)
				searchIsland(x, y-1)
				searchIsland(x, y+1)
				return true
			}
		}
		return false
	}

	var count int
	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[0]); j++ {
			if searchIsland(i, j) {
				count++
			}
		}
	}

	return count
}

func main() {
	output := numIslands([][]byte{
		{'1', '1', '1', '1', '0'},
		{'1', '1', '0', '1', '0'},
		{'1', '1', '0', '0', '0'},
		{'0', '0', '0', '0', '0'}})

	output1 := numIslands([][]byte{
		{'1', '1', '0', '0', '0'},
		{'1', '1', '0', '0', '0'},
		{'0', '0', '1', '0', '0'},
		{'0', '0', '0', '1', '1'}})
	fmt.Println("\n******** output *********\n", output, output1)
}
