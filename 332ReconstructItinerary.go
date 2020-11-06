package main

import (
	"fmt"
	"sort"
	"strings"
)

func findItinerary(tickets [][]string) []string {
	var output []string

	mapNodeEdge := make(map[string][]string)

	for _, ticket := range tickets {
		startNode := ticket[0]
		endNode := ticket[1]
		if _, ok := mapNodeEdge[startNode]; ok {
			mapNodeEdge[startNode] = append(mapNodeEdge[startNode], startNode+endNode)
		} else {
			mapNodeEdge[startNode] = []string{startNode + endNode}
		}
	}

	for _, edges := range mapNodeEdge {
		sort.Strings(edges)
	}

	getEndNode := func(edge string) string { //retrieve the end node of an edge
		var sb strings.Builder
		for i := 3; i < 6; i++ {
			sb.WriteByte(edge[i])
		}
		return sb.String()
	}
	fmt.Println(mapNodeEdge)

	mapUnvisitedEdges := make(map[string]int) //may have same tickets, here we need to store count

	for _, edges := range mapNodeEdge {
		for _, edge := range edges {
			if _, ok := mapUnvisitedEdges[edge]; ok {
				mapUnvisitedEdges[edge]++
			} else {
				mapUnvisitedEdges[edge] = 1
			}
		}
	}
	fmt.Println(mapUnvisitedEdges)

	var dfs func(string)
	dfs = func(startNode string) {
		fmt.Println(startNode)
		if _, ok := mapNodeEdge[startNode]; ok {
			for _, edge := range mapNodeEdge[startNode] {
				if _, ok := mapUnvisitedEdges[edge]; ok && mapUnvisitedEdges[edge] > 0 {
					mapUnvisitedEdges[edge]-- //mark the edge is visited
					dfs(getEndNode(edge))
				}
			}
		}

		//normally, we should push front, but golang slice doesn't support,
		//so we need to reverse the output in the end.
		output = append(output, startNode)
	}

	dfs("JFK")

	//reverse
	i := 0
	j := len(output) - 1
	for i < j {
		output[i], output[j] = output[j], output[i]
		i++
		j--
	}

	return output
}

func main() {
	output := findItinerary([][]string{{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}})
	output1 := findItinerary([][]string{{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}})
	output2 := findItinerary([][]string{{"EZE", "AXA"}, {"TIA", "ANU"}, {"ANU", "JFK"}, {"JFK", "ANU"}, {"ANU", "EZE"},
		{"TIA", "ANU"}, {"AXA", "TIA"}, {"TIA", "JFK"}, {"ANU", "TIA"}, {"JFK", "TIA"}})

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
