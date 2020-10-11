package main

import (
	"container/list"
	"fmt"
)

type gridInfo struct {
	id   int // [1, len(board) * len(board[0])]
	dist int // distance to the start grid
}

func snakesAndLadders(board [][]int) int {
	boardWidth := len(board[0])
	boardHeight := len(board)
	destGridId := boardWidth * boardHeight

	mapReachedGrids := make(map[int]gridInfo)
	lstPendingGridIds := list.New() //store those grids that have been reached but their neighbors have not been checked

	var calcDist func(int, int)
	calcDist = func(gridId int, prevGridId int) {

		convertGridIdToCoordinate := func(id int) (int, int) {
			var x, y int
			x = boardHeight - 1 - (id-1)/boardHeight
			if x%2 == (boardHeight-1)%2 {
				y = (id - 1) % boardWidth
			} else {
				y = boardWidth - 1 - (id-1)%boardWidth
			}
			return x, y
		}

		x, y := convertGridIdToCoordinate(gridId)
		if board[x][y] != -1 { // hit a snake or a ladder
			gridId = board[x][y]
		}

		if _, ok := mapReachedGrids[gridId]; ok {
			return
		}

		newDist := mapReachedGrids[prevGridId].dist + 1
		reachedGrid := gridInfo{id: gridId, dist: newDist}
		mapReachedGrids[gridId] = reachedGrid
		lstPendingGridIds.PushBack(reachedGrid)
	}

	mapReachedGrids[1] = gridInfo{id: 1, dist: 0}
	for i := 1; i <= 6; i++ {
		if i+1 <= destGridId {
			calcDist(i+1, 1)
		}
	}

	for lstPendingGridIds.Len() > 0 {
		nextPendingGrid := lstPendingGridIds.Front().Value.(gridInfo)

		if nextPendingGrid.id == destGridId {
			break
		}

		for i := 1; i <= 6; i++ {
			if i+nextPendingGrid.id <= destGridId {
				calcDist(i+nextPendingGrid.id, nextPendingGrid.id)
			}
		}

		lstPendingGridIds.Remove(lstPendingGridIds.Front())
	}
	//fmt.Println(mapReachedGrids)

	if destGrid, ok := mapReachedGrids[destGridId]; ok {
		return destGrid.dist
	}
	return -1
}

func main() {
	output := snakesAndLadders([][]int{
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1},
		{-1, 35, -1, -1, 13, -1},
		{-1, -1, -1, -1, -1, -1},
		{-1, 15, -1, -1, -1, -1}})

	fmt.Println("\n******** output *********\n", output)
}
