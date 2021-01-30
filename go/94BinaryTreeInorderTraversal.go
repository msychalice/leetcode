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

func inorderTraversal(root *TreeNode) []int {
	output := []int{}

	/*
			//recursive solution
			var traverse func(*TreeNode, *[]int)
			traverse = func(node *TreeNode, nodeVal *[]int) {
				if node == nil {
					return
				}

				traverse(node.Left, nodeVal)
				*nodeVal = append(*nodeVal, node.Val)
				traverse(node.Right, nodeVal)
			}

		traverse(root, &output)
	*/

	//iterative solution
	staPendingParentNodes := list.New()
	mapReachedNode := make(map[*TreeNode]bool)
	curNode := root

	for curNode != nil {
		leftNodeIsEmptyOrReached := false
		if curNode.Left == nil {
			leftNodeIsEmptyOrReached = true
		}
		if _, ok := mapReachedNode[curNode.Left]; ok {
			leftNodeIsEmptyOrReached = true
		}

		if leftNodeIsEmptyOrReached {
			output = append(output, curNode.Val)
			mapReachedNode[curNode] = true

			if curNode.Right != nil {
				curNode = curNode.Right
			} else {
				if staPendingParentNodes.Front() != nil {
					curNode = staPendingParentNodes.Front().Value.(*TreeNode)
					staPendingParentNodes.Remove(staPendingParentNodes.Front())
				} else { // the end of traversal
					curNode = nil
				}
			}
		} else {
			staPendingParentNodes.PushFront(curNode)
			curNode = curNode.Left
		}
	}

	return output
}

func main() {
	output := inorderTraversal(
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
	output1 := inorderTraversal(nil)
	output2 := inorderTraversal(
		&TreeNode{
			Val:   1,
			Left:  nil,
			Right: nil,
		})
	output3 := inorderTraversal(
		&TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
			Right: nil,
		})
	output4 := inorderTraversal(
		&TreeNode{
			Val:  1,
			Left: nil,
			Right: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
		})
	output5 := inorderTraversal(
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
