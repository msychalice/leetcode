package main

import (
	"fmt"
)

func spiralOrder(matrix [][]int) []int {
	leftBoundry := -1
	topBoundry := -1
	bottomBoundry := len(matrix)
	rightBoundry := 0
	if bottomBoundry != 0 {
		rightBoundry = len(matrix[0])
	}

	const moveRight = 0
	const moveDown = 1
	const moveLeft = 2
	const moveUp = 3

	output := []int{}
	var curX, curY int

finalResult:
	for direction := 0; ; direction = (direction + 1) % 4 {
	changeDirection:
		for {
			switch direction {
			case moveRight:
				if curY < rightBoundry {
					output = append(output, matrix[curX][curY])
					curY++
				} else {
					curY--
					if curX+1 < bottomBoundry {
						topBoundry = curX
						curX++
						break changeDirection
					} else {
						break finalResult
					}
				}
			case moveDown:
				if curX < bottomBoundry {
					output = append(output, matrix[curX][curY])
					curX++
				} else {
					curX--
					if curY-1 > leftBoundry {
						rightBoundry = curY
						curY--
						break changeDirection
					} else {
						break finalResult
					}
				}
			case moveLeft:
				if curY > leftBoundry {
					output = append(output, matrix[curX][curY])
					curY--
				} else {
					curY++
					if curX-1 > topBoundry {
						bottomBoundry = curX
						curX--
						break changeDirection
					} else {
						break finalResult
					}
				}
			case moveUp:
				if curX > topBoundry {
					output = append(output, matrix[curX][curY])
					curX--
				} else {
					curX++
					if curY+1 < rightBoundry {
						leftBoundry = curY
						curY++
						break changeDirection
					} else {
						break finalResult
					}
				}
			}
		}

	}

	return output
}

func main() {
	output := spiralOrder([][]int{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}})
	output1 := spiralOrder([][]int{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}})
	output2 := spiralOrder([][]int{{1}})
	output3 := spiralOrder([][]int{{1, 2}, {3, 4}})
	output4 := spiralOrder([][]int{})

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4)
}
