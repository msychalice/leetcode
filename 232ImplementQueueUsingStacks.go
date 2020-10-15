package main

import (
	"container/list"
	"fmt"
)

type MyQueue struct {
	stackPush *list.List
	stackPop  *list.List
}

/** Initialize your data structure here. */
func Constructor() MyQueue {
	que := MyQueue{stackPush: list.New(), stackPop: list.New()}
	return que
}

/** Push element x to the back of queue. */
func (this *MyQueue) Push(x int) {
	// 1. move all the elements from stackPop to stackPush
	// 2. push the new element to stackPush
	// 3. move all the elements back from stackPush to stackPop
	for this.stackPop.Front() != nil {
		this.stackPush.PushFront(this.stackPop.Front().Value)
		this.stackPop.Remove(this.stackPop.Front())
	}

	this.stackPush.PushFront(x)

	for this.stackPush.Front() != nil {
		this.stackPop.PushFront(this.stackPush.Front().Value)
		this.stackPush.Remove(this.stackPush.Front())
	}
}

/** Removes the element from in front of queue and returns that element. */
func (this *MyQueue) Pop() int {
	var result int
	if this.stackPop.Front() != nil {
		result = this.stackPop.Front().Value.(int)
		this.stackPop.Remove(this.stackPop.Front())
	}

	return result
}

/** Get the front element. */
func (this *MyQueue) Peek() int {
	var result int
	if this.stackPop.Front() != nil {
		result = this.stackPop.Front().Value.(int)
	}

	return result
}

/** Returns whether the queue is empty. */
func (this *MyQueue) Empty() bool {
	if this.stackPop.Front() != nil {
		return false
	}
	return true
}

/**
 * Your MyQueue object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * param_2 := obj.Pop();
 * param_3 := obj.Peek();
 * param_4 := obj.Empty();
 */

func main() {
	obj := Constructor()
	obj.Push(1)
	output := obj.Pop()
	output1 := obj.Peek()
	output2 := obj.Empty()

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
