package main

import (
	"fmt"
)

func rotate(matrix [][]int) {
	matrixLen := len(matrix)
	halfMatixLen := (matrixLen - 1) / 2
	isEvenLen := matrixLen%2 == 0

	for x := 0; x <= halfMatixLen; x++ {
		if x == halfMatixLen && !isEvenLen { // reach the center grid
			break
		}

		for y := x; y < matrixLen-x-1; y++ {

			x1 := y
			y1 := matrixLen - 1 - x
			x2 := y1
			y2 := matrixLen - 1 - x1
			x3 := y2
			y3 := matrixLen - 1 - x2

			//fmt.Println(y, x, y1, x1, y2, x2, y3, x3)

			tmp1 := matrix[x1][y1]
			matrix[x1][y1] = matrix[x][y]
			tmp2 := matrix[x2][y2]
			matrix[x2][y2] = tmp1
			tmp3 := matrix[x3][y3]
			matrix[x3][y3] = tmp2
			matrix[x][y] = tmp3
		}
	}
}

func main() {
	output := [][]int{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
	rotate(output)
	output1 := [][]int{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}}
	rotate(output1)
	output2 := [][]int{{1}}
	rotate(output2)
	output3 := [][]int{{1, 2}, {3, 4}}
	rotate(output3)

	fmt.Println("\n******** output *********\n", output, output1, output2, output3)
}
