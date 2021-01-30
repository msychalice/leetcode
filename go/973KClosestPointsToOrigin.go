package main

import (
	"container/heap"
	"fmt"
)

type Point struct {
	dist  int // do not need to apply the sqrt operation.
	index int
}

//
type IntHeap []Point // max-heap

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i].dist > h[j].dist }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntHeap) Push(x interface{}) {
	// Push and Pop use pointer receivers because they modify the slice's length,
	// not just its contents.
	*h = append(*h, x.(Point))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func kClosest(points [][]int, K int) [][]int {
	sliPoint := []Point{}
	for i, point := range points {
		sliPoint = append(sliPoint, Point{index: i, dist: point[0]*point[0] + point[1]*point[1]})
	}

	var curHeapLen int
	pHeapDist := &IntHeap{}
	heap.Init(pHeapDist)
	for _, point := range sliPoint {
		if curHeapLen >= K {
			if []Point(*pHeapDist)[0].dist > point.dist {
				[]Point(*pHeapDist)[0] = point
				heap.Fix(pHeapDist, 0)
			}
		} else {
			heap.Push(pHeapDist, point)
			curHeapLen++
		}
	}

	fmt.Println(*pHeapDist)

	output := [][]int{}
	for _, point := range []Point(*pHeapDist) {
		output = append(output, points[point.index])
	}

	return output
}

func main() {
	output := kClosest([][]int{{1, 3}, {-2, 2}}, 1)
	output1 := kClosest([][]int{{3, 3}, {5, -1}, {-2, 4}}, 2)
	output2 := kClosest([][]int{{0, 1}, {1, 0}}, 2)
	output3 := kClosest([][]int{{1, 3}, {-2, 2}, {2, -2}}, 2)

	fmt.Println("\n******** output *********\n", output, output1, output2, output3)
}
