package main

import (
	"container/heap"
	"fmt"
)

type IntHeap []int // max-heap

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] > h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntHeap) Push(x interface{}) {
	// Push and Pop use pointer receivers because they modify the slice's length,
	// not just its contents.
	*h = append(*h, x.(int))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func findKthLargest(nums []int, k int) int {
	maxHeap := IntHeap(nums)
	heap.Init(&maxHeap)

	var output int
	for i := 0; i < k; i++ {
		output = heap.Pop(&maxHeap).(int)
	}

	return output
}

func main() {
	output := findKthLargest([]int{3, 2, 1, 5, 6, 4}, 2)
	output1 := findKthLargest([]int{3, 2, 3, 1, 2, 4, 5, 5, 6}, 4)

	fmt.Println("\n******** output *********\n", output, output1)
}
