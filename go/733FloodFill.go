package main

import (
	"fmt"
)

func combineCoordinate(x, y int) int {
	return x*100 + y
}

func floodFill(image [][]int, sr int, sc int, newColor int) [][]int {
	oldColor := image[sr][sc]
	if oldColor == newColor {
		return image
	}

	mapReachedGrids := make(map[int]bool)

	var funcFillGrid func(int, int)
	funcFillGrid = func(x, y int) {
		if x < 0 || y < 0 || x >= len(image) || y >= len(image[0]) {
			return
		}
		if image[x][y] != oldColor {
			return
		}
		if _, ok := mapReachedGrids[combineCoordinate(x, y)]; ok {
			return
		}

		image[x][y] = newColor
		mapReachedGrids[combineCoordinate(x, y)] = true
		funcFillGrid(x-1, y)
		funcFillGrid(x+1, y)
		funcFillGrid(x, y+1)
		funcFillGrid(x, y-1)
	}

	funcFillGrid(sr, sc)

	return image
}

func main() {
	output := floodFill([][]int{{1, 1, 1}, {1, 1, 0}, {1, 0, 1}}, 1, 1, 2)

	fmt.Println("\n******** output *********\n", output)
}
