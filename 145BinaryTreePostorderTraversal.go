package main

import (
	"container/list"
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func postorderTraversal(root *TreeNode) []int {
	output := []int{}

	/*
			//recursive solution
			var traverse func(*TreeNode, *[]int)
			traverse = func(node *TreeNode, nodeVal *[]int) {
				if node == nil {
					return
				}

				traverse(node.Left, nodeVal)
				traverse(node.Right, nodeVal)
				*nodeVal = append(*nodeVal, node.Val)
			}

		traverse(root, &output)
	*/

	//iterative solution
	staPendingParentNodes := list.New()
	mapReachedNode := make(map[*TreeNode]bool)
	curNode := root

	for curNode != nil {
		leftNodeIsNilOrReached := false
		if curNode.Left == nil {
			leftNodeIsNilOrReached = true
		}
		if _, ok := mapReachedNode[curNode.Left]; ok {
			leftNodeIsNilOrReached = true
		}

		rightNodeIsNilOrReached := false
		if curNode.Right == nil {
			rightNodeIsNilOrReached = true
		}
		if _, ok := mapReachedNode[curNode.Right]; ok {
			rightNodeIsNilOrReached = true
		}

		if leftNodeIsNilOrReached && rightNodeIsNilOrReached {
			output = append(output, curNode.Val)
			mapReachedNode[curNode] = true

			if staPendingParentNodes.Front() != nil {
				curNode = staPendingParentNodes.Front().Value.(*TreeNode)
				staPendingParentNodes.Remove(staPendingParentNodes.Front())
			} else { // the end of traversal
				curNode = nil
			}
		} else if !leftNodeIsNilOrReached {
			staPendingParentNodes.PushFront(curNode)
			curNode = curNode.Left
		} else if !rightNodeIsNilOrReached {
			staPendingParentNodes.PushFront(curNode)
			curNode = curNode.Right
		}
	}

	return output
}

func main() {
	output := postorderTraversal(
		&TreeNode{
			Val:  1,
			Left: nil,
			Right: &TreeNode{
				Val: 2,
				Left: &TreeNode{
					Val:   3,
					Left:  nil,
					Right: nil,
				},
				Right: nil,
			},
		})
	output1 := postorderTraversal(nil)
	output2 := postorderTraversal(
		&TreeNode{
			Val:   1,
			Left:  nil,
			Right: nil,
		})
	output3 := postorderTraversal(
		&TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
			Right: nil,
		})
	output4 := postorderTraversal(
		&TreeNode{
			Val:  1,
			Left: nil,
			Right: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
		})
	output5 := postorderTraversal(
		&TreeNode{
			Val: 3,
			Left: &TreeNode{
				Val:   1,
				Left:  nil,
				Right: nil,
			},
			Right: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
		})

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4, output5)
}
