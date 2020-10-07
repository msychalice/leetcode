package main

import (
	"fmt"
)

/**
 * Definition for singly-linked list.
 */
type ListNode struct {
	Val  int
	Next *ListNode
}

func (node *ListNode) print() {
	var strOutput string
	if node == nil {
		return
	}

	for {
		strOutput = fmt.Sprintf("%s%d", strOutput, node.Val)
		if node.Next != nil {
			node = node.Next
			strOutput = strOutput + "->"
		} else {
			break
		}
	}

	fmt.Println(strOutput)
}

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	curL1Node := l1
	curL2Node := l2

	var output ListNode
	var advancedNum bool
	curOutputNode := &output

	for curL1Node != nil || curL2Node != nil {
		var newNum int
		if curL1Node != nil {
			if curL2Node != nil {
				newNum = curL1Node.Val + curL2Node.Val
			} else {
				newNum = curL1Node.Val
			}
		} else {
			if curL2Node != nil {
				newNum = curL2Node.Val
			} else {
				break
			}
		}

		if advancedNum {
			newNum++
		}

		if newNum > 9 {
			advancedNum = true
			newNum = newNum - 10
		} else {
			advancedNum = false
		}

		curOutputNode.Val = newNum
		curOutputNode.Next = &ListNode{}

		if curL1Node != nil {
			curL1Node = curL1Node.Next
		}
		if curL2Node != nil {
			curL2Node = curL2Node.Next
		}
		if curL1Node != nil || curL2Node != nil {
			curOutputNode = curOutputNode.Next
		} else {
			if advancedNum {
				curOutputNode.Next = &ListNode{1, nil}
				advancedNum = false
			} else {
				curOutputNode.Next = nil
			}
		}
	}

	return &output
}

func main() {
	l1 := ListNode{9, &ListNode{9, &ListNode{9, &ListNode{9, &ListNode{9, &ListNode{9, &ListNode{9, nil}}}}}}}
	l2 := ListNode{9, &ListNode{9, &ListNode{9, &ListNode{9, nil}}}}
	l1.print()
	l2.print()

	output := addTwoNumbers(&l1, &l2)
	output.print()

	fmt.Println("\n******** output *********\n", output)
}
