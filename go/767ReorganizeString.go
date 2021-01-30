package main

import (
	"container/heap"
	"fmt"
)

type charInfo struct {
	char  byte
	count int
}

type CharInfoHeap []charInfo

func (h CharInfoHeap) Len() int           { return len(h) }
func (h CharInfoHeap) Less(i, j int) bool { return h[i].count > h[j].count }
func (h CharInfoHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *CharInfoHeap) Push(x interface{}) {
	// Push and Pop use pointer receivers because they modify the slice's length,
	// not just its contents.
	*h = append(*h, x.(charInfo))
}

func (h *CharInfoHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func reorganizeString(S string) string {
	heapCharInfo := &CharInfoHeap{}
	heap.Init(heapCharInfo)

	for _, char := range S {
		findChar := false
		for i := 0; i < (*heapCharInfo).Len(); i++ {
			if byte(char) == (*heapCharInfo)[i].char {
				(*heapCharInfo)[i].count++
				heap.Fix(heapCharInfo, i)
				findChar = true
				break
			}
		}
		if !findChar {
			heap.Push(heapCharInfo, charInfo{char: byte(char), count: 1})
		}
	}

	//fmt.Println(heapCharInfo)

	output := []byte{}
	pOutput := &output

	funcAppendChar := func(heapIndex int) {
		if heapIndex >= heapCharInfo.Len() {
			return
		}
		*pOutput = append(*pOutput, (*heapCharInfo)[heapIndex].char)
		(*heapCharInfo)[heapIndex].count--

		if (*heapCharInfo)[heapIndex].count == 0 {
			heap.Remove(heapCharInfo, heapIndex)
		} else {
			heap.Fix(heapCharInfo, heapIndex)
		}
	}

	for heapCharInfo.Len() > 0 {
		if len(output) == 0 {
			funcAppendChar(0)
		} else {
			if (*heapCharInfo)[0].char != output[len(output)-1] {
				funcAppendChar(0)
			} else {
				if heapCharInfo.Len() > 1 {
					funcAppendChar(1)
				} else { // no different character in the heap
					break
				}
			}
		}
	}

	if heapCharInfo.Len() > 0 {
		return ""
	}

	return string(output)
}

func main() {
	output := reorganizeString("aab")
	output1 := reorganizeString("aaab")
	output2 := reorganizeString("vvvlo")

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
