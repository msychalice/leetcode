package main

import (
	"fmt"
	"math"
	"sort"
)

func kClosest(points [][]int, K int) [][]int {
	mapDist := make(map[float64]*[]int) //(distance, index)
	sliDist := []float64{}

	for i, point := range points {
		dist := math.Sqrt(float64(point[0]*point[0] + point[1]*point[1]))
		sliDist = append(sliDist, dist)
		if indices, ok := mapDist[dist]; ok {
			*indices = append(*indices, i)
		} else {
			mapDist[dist] = &[]int{i}
		}
	}
	sort.Float64s(sliDist)

	output := [][]int{}
	var curOutputNum int
result:
	for _, dist := range sliDist {
		indices := mapDist[dist]
		for _, index := range *indices {
			output = append(output, points[index])
			curOutputNum++
			if curOutputNum == K {
				break result
			}
		}
	}

	return output
}

func main() {
	output := kClosest([][]int{{1, 3}, {-2, 2}}, 1)
	output1 := kClosest([][]int{{3, 3}, {5, -1}, {-2, 4}}, 2)
	output2 := kClosest([][]int{{0, 1}, {1, 0}}, 2)

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
