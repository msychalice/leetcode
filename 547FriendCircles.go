package main

import (
	"fmt"
)

func findCircleNum(M [][]int) int {
	disjointSets := make([]int, len(M))

	for i := 0; i < len(disjointSets); i++ {
		disjointSets[i] = -1
	}

	var findRoot func(int) int
	findRoot = func(node int) int {
		if disjointSets[node] < 0 {
			return node
		} else {
			root := findRoot(disjointSets[node])
			disjointSets[node] = root
			return root
		}
	}

	var union func(int, int)
	union = func(node1, node2 int) {
		if node1 == node2 {
			return
		}

		parent1 := disjointSets[node1]
		parent2 := disjointSets[node2]
		if parent1 < 0 && parent2 < 0 { // both are root nodes, merge smaller set into bigger set.
			if parent1 < parent2 {
				disjointSets[node1] = parent1 + parent2
				disjointSets[node2] = node1
			} else if parent1 == parent2 {
				if node1 < node2 {
					disjointSets[node1] = parent1 + parent2
					disjointSets[node2] = node1
				} else {
					disjointSets[node2] = parent1 + parent2
					disjointSets[node1] = node2
				}
			} else if parent1 > parent2 {
				disjointSets[node2] = parent1 + parent2
				disjointSets[node1] = node2
			}
		} else if parent1 >= 0 && parent2 < 0 {
			union(findRoot(node1), node2)
		} else if parent1 < 0 && parent2 >= 0 {
			union(node1, findRoot(node2))
		} else if parent1 >= 0 && parent2 >= 0 {
			union(findRoot(node1), findRoot(node2))
		}
	}

	for i := 0; i < len(M); i++ {
		for j := i + 1; j < len(M); j++ {
			if M[i][j] == 1 {
				union(i, j)
			}
		}
	}

	var output int
	for _, parent := range disjointSets {
		if parent < 0 {
			output++
		}
	}

	return output
}

func main() {
	output := findCircleNum([][]int{{1, 1, 0}, {1, 1, 0}, {0, 0, 1}})
	output1 := findCircleNum([][]int{{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 1, 1}})

	fmt.Println("\n******** output *********\n", output, output1)
}
