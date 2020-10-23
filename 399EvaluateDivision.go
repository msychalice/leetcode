package main

import (
	"fmt"
)

func calcEquation(equations [][]string, values []float64, queries [][]string) []float64 {
	var output []float64

	mapStr2Int := make(map[string]int)

	var curIndex int
	for _, edge := range equations {
		startName := edge[0]
		endName := edge[1]

		if _, ok := mapStr2Int[startName]; !ok {
			mapStr2Int[startName] = curIndex
			curIndex++
		}
		if _, ok := mapStr2Int[endName]; !ok {
			mapStr2Int[endName] = curIndex
			curIndex++
		}
	}

	calcResult := make([][]float64, len(mapStr2Int))
	for i := 0; i < len(calcResult); i++ {
		calcResult[i] = make([]float64, len(mapStr2Int))
	}
	for i, edge := range equations {
		startName := edge[0]
		endName := edge[1]
		startIndex := mapStr2Int[startName]
		endIndex := mapStr2Int[endName]

		calcResult[startIndex][endIndex] = values[i]
		calcResult[endIndex][startIndex] = 1 / values[i]
	}
	for i := 0; i < len(calcResult); i++ {
		calcResult[i][i] = 1
	}

	var dfsCalc func(int, int, map[int]bool) float64
	dfsCalc = func(startIndex, endIndex int, mapVisited map[int]bool) float64 {
		if calcResult[startIndex][endIndex] != 0 {
			return calcResult[startIndex][endIndex]
		}

		for neighborIndex, neighborResult := range calcResult[startIndex] {
			if (startIndex != neighborIndex) && (neighborResult != 0) {
				if _, ok := mapVisited[neighborIndex]; !ok {
					mapVisited[startIndex] = true
					result := dfsCalc(neighborIndex, endIndex, mapVisited)
					if result > 0 {
						result *= calcResult[startIndex][neighborIndex]
						calcResult[startIndex][endIndex] = result
						calcResult[endIndex][startIndex] = 1 / result
						return result
					}
				}
			}
		}

		return -1
	}
	fmt.Println(mapStr2Int)
	fmt.Println(calcResult)

	for _, query := range queries {
		startIndex := -1
		endIndex := -1
		if _, ok := mapStr2Int[query[0]]; ok {
			startIndex = mapStr2Int[query[0]]
		}
		if _, ok := mapStr2Int[query[1]]; ok {
			endIndex = mapStr2Int[query[1]]
		}

		if startIndex == -1 || endIndex == -1 {
			output = append(output, -1)
			continue
		}

		output = append(output, dfsCalc(startIndex, endIndex, make(map[int]bool)))
	}

	return output
}

func main() {
	output := calcEquation([][]string{{"a", "b"}, {"b", "c"}}, []float64{2.0, 3.0}, [][]string{{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}})
	output1 := calcEquation([][]string{{"a", "b"}, {"b", "c"}, {"bc", "cd"}}, []float64{1.5, 2.5, 5.0}, [][]string{{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}})
	output2 := calcEquation([][]string{{"a", "b"}}, []float64{0.5}, [][]string{{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}})
	output3 := calcEquation([][]string{{"x1", "x2"}, {"x2", "x3"}, {"x3", "x4"}, {"x4", "x5"}}, []float64{3.0, 4.0, 5.0, 6.0}, [][]string{{"x1", "x5"}, {"x5", "x2"}, {"x2", "x4"}, {"x2", "x2"}, {"x2", "x9"}, {"x9", "x9"}})

	fmt.Println("\n******** output *********\n", output, output1, output2, output3)
}
