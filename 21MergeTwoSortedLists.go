package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
	var output *ListNode
	curNodeL1 := l1
	curNodeL2 := l2
	curNodeOutput := output

	if curNodeL1 != nil || curNodeL2 != nil {
		output = &ListNode{}
		curNodeOutput = output
	}

	for {
		if curNodeL1 != nil && curNodeL2 != nil {
			if curNodeL1.Val <= curNodeL2.Val {
				curNodeOutput.Val = curNodeL1.Val
				curNodeL1 = curNodeL1.Next
			} else {
				curNodeOutput.Val = curNodeL2.Val
				curNodeL2 = curNodeL2.Next
			}
		} else if curNodeL1 == nil && curNodeL2 != nil {
			curNodeOutput.Val = curNodeL2.Val
			curNodeL2 = curNodeL2.Next
		} else if curNodeL1 != nil && curNodeL2 == nil {
			curNodeOutput.Val = curNodeL1.Val
			curNodeL1 = curNodeL1.Next
		} else {
			break
		}

		if curNodeL1 != nil || curNodeL2 != nil {
			curNodeOutput.Next = &ListNode{}
			curNodeOutput = curNodeOutput.Next
		}
	}

	return output
}

func main() {
	output := mergeTwoLists(&ListNode{Val: 1, Next: &ListNode{Val: 2, Next: &ListNode{Val: 4, Next: nil}}},
		&ListNode{Val: 1, Next: &ListNode{Val: 3, Next: &ListNode{Val: 4, Next: nil}}})
	output1 := mergeTwoLists(&ListNode{}, &ListNode{})
	output2 := mergeTwoLists(&ListNode{}, &ListNode{Val: 0, Next: nil})

	fmt.Println("\n******** output *********\n", output, output1, output2)
}
