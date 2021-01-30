package main

import (
	"fmt"
)

type Grid struct {
	X int
	Y int
}

func orangesRotting(grid [][]int) int {
	rottedGrid := []Grid{}
	var freshGridCount int

	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[i]); j++ {
			gridValue := grid[i][j]
			if gridValue == 2 {
				rottedGrid = append(rottedGrid, Grid{X: i, Y: j})
			} else if gridValue == 1 {
				freshGridCount++
			}
		}
	}

	var funcChangeOrange func([]Grid) int
	funcChangeOrange = func(rottedGrid []Grid) int {
		if freshGridCount == 0 {
			return 0
		}

		newRottedGrid := []Grid{}

		for _, g := range rottedGrid {
			neighborGrids := []Grid{Grid{X: g.X - 1, Y: g.Y}, Grid{X: g.X + 1, Y: g.Y}, Grid{X: g.X, Y: g.Y - 1}, Grid{X: g.X, Y: g.Y + 1}}
			for _, neighborGrid := range neighborGrids {
				if neighborGrid.X >= 0 && neighborGrid.X < len(grid) &&
					neighborGrid.Y >= 0 && neighborGrid.Y < len(grid[neighborGrid.X]) &&
					grid[neighborGrid.X][neighborGrid.Y] == 1 { // neighbor grid is a fresh orange
					grid[neighborGrid.X][neighborGrid.Y] = 2
					freshGridCount--
					newRottedGrid = append(newRottedGrid, Grid{X: neighborGrid.X, Y: neighborGrid.Y})
				}
			}
		}

		if len(newRottedGrid) == 0 { // no orange is rotted
			if freshGridCount == 0 {
				return 0
			} else {
				return -1
			}
		} else {
			result := funcChangeOrange(newRottedGrid)
			if result == -1 {
				return -1
			} else {
				return result + 1
			}
		}
	}

	return funcChangeOrange(rottedGrid)
}

func main() {
	output := orangesRotting([][]int{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}})
	output1 := orangesRotting([][]int{{2, 1, 1}, {0, 1, 1}, {1, 0, 1}})
	output2 := orangesRotting([][]int{{0, 2}})

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
