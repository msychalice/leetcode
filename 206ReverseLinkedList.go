package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func (this *ListNode) printList() {
	cur := this
	for cur != nil {
		if cur.Next != nil {
			fmt.Print(cur.Val, "->")
		} else {
			fmt.Print(cur.Val)
		}
		cur = cur.Next
	}
}

func reverseList(head *ListNode) *ListNode {
	/*
		//iterative solution
		if head == nil {
			return nil
		}

		cur := head
		var prev *ListNode
		var next *ListNode

		for {
			next = cur.Next
			cur.Next = prev

			if next == nil {
				break
			}

			prev = cur
			cur = next
		}

		return cur
	*/

	//recursive solution
	var reverse func(*ListNode, *ListNode) *ListNode
	reverse = func(prev *ListNode, cur *ListNode) *ListNode {
		if cur == nil {
			return prev
		}

		next := cur.Next
		cur.Next = prev

		return reverse(cur, next)
	}
	return reverse(nil, head)

}

func main() {
	output := reverseList(&ListNode{Val: 1, Next: &ListNode{Val: 2, Next: &ListNode{Val: 4, Next: nil}}})

	fmt.Println("\n******** output *********\n", output)
	output.printList()

}
