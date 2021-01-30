package main

import (
	"container/list"
	"fmt"
)

type MinStack struct {
	min  int
	data *list.List
}

/** initialize your data structure here. */
func Constructor() MinStack {
	return MinStack{min: 0, data: list.New()}
}

func (this *MinStack) Push(x int) {
	if this.data.Len() == 0 {
		this.data.PushFront(x)
		this.min = x
	} else {
		if this.min >= x {
			this.data.PushFront(this.min) // cache the second minimum number, this is the key to retrieve min in constant time
			this.min = x
		}
		this.data.PushFront(x)
	}
}

func (this *MinStack) Pop() {
	if this.data.Front().Value.(int) == this.min {
		this.data.Remove(this.data.Front())
		if this.data.Front() != nil {
			this.min = this.data.Front().Value.(int)
			this.data.Remove(this.data.Front())
		}
	} else {
		this.data.Remove(this.data.Front())
	}
}

func (this *MinStack) Top() int {
	return this.data.Front().Value.(int)
}

func (this *MinStack) GetMin() int {
	return this.min
}

/**
 * Your MinStack object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * obj.Pop();
 * param_3 := obj.Top();
 * param_4 := obj.GetMin();
 ["MinStack","push","push","push","top","pop","getMin","pop","getMin","pop","push","top","getMin","push","top","getMin","pop","getMin"]
[[],[2147483646],[2147483646],[2147483647],[],[],[],[],[],[],[2147483647],[],[],[-2147483648],[],[],[],[]]
*/

func main() {
	obj := Constructor()
	obj.Push(2147483646)
	obj.Push(2147483646)
	obj.Push(2147483647)
	fmt.Println("top", obj.Top())
	obj.Pop()
	fmt.Println("min", obj.GetMin())
	obj.Pop()
	fmt.Println("min", obj.GetMin())
	obj.Pop()
	obj.Push(2147483647)
	fmt.Println("top", obj.Top())
	fmt.Println("min", obj.GetMin())
	obj.Push(-2147483648)
	fmt.Println("top", obj.Top())
	fmt.Println("min", obj.GetMin())
	obj.Pop()
	fmt.Println("min", obj.GetMin())

}
