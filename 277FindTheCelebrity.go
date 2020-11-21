package main

import (
	"fmt"
)

func findCelebrity(matrix [][]int) int {
	knows := func(a, b int) bool {
		return matrix[a][b] == 1
	}

	var celebrityIndex int
	for i := 1; i < len(matrix); i++ {
		if knows(celebrityIndex, i) {
			celebrityIndex = i
		} else {
			// i is not a celebrity
			//empty
		}
	}

	for i := 0; i < len(matrix); i++ {
		if i == celebrityIndex {
			continue
		}

		if knows(celebrityIndex, i) || !knows(i, celebrityIndex) {
			return -1
		}
	}

	return celebrityIndex
}

func main() {
	output := findCelebrity([][]int{{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}})

	output1 := findCelebrity([][]int{{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}})

	output2 := findCelebrity([][]int{{0, 1, 0}, {0, 0, 0}, {0, 1, 0}})

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
