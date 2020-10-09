package main

import (
	"fmt"
)

func exist(board [][]byte, word string) bool {
	reachedGrid := make([][]bool, len(board))
	for index := range reachedGrid {
		reachedGrid[index] = make([]bool, len(board[0]))
	}

	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[0]); j++ {
			//find the word
			var funcFindWord func(int, int, int) bool
			funcFindWord = func(x, y, startIndexOfSubString int) bool {
				if x >= 0 && x < len(board) && y >= 0 && y < len(board[x]) &&
					!reachedGrid[x][y] && board[x][y] == word[startIndexOfSubString] {
					//fmt.Println(x, y, board[x][y], startIndexOfSubString, word[startIndexOfSubString])
					reachedGrid[x][y] = true

					if startIndexOfSubString == len(word)-1 {
						return true
					}

					// check all neighbor grids
					if funcFindWord(x-1, y, startIndexOfSubString+1) ||
						funcFindWord(x+1, y, startIndexOfSubString+1) ||
						funcFindWord(x, y-1, startIndexOfSubString+1) ||
						funcFindWord(x, y+1, startIndexOfSubString+1) {
						return true
					} else {
						reachedGrid[x][y] = false
						return false
					}
				}

				return false
			}

			if funcFindWord(i, j, 0) {
				return true
			}
		}
	}

	return false
}

func main() {
	output := exist([][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCCED")
	output1 := exist([][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "SEE")
	output2 := exist([][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCB")

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
