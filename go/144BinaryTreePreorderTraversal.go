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

func preorderTraversal(root *TreeNode) []int {
	output := []int{}

	/*
		//recursive solution
		var traverse func(*TreeNode, *[]int)
		traverse = func(node *TreeNode, nodeVal *[]int) {
			if node == nil {
				return
			}

			*nodeVal = append(*nodeVal, node.Val)

			traverse(node.Left, nodeVal)
			traverse(node.Right, nodeVal)
		}

		traverse(root, &output)
	*/

	//iterative solution
	staPendingRightNodes := list.New()
	curNode := root

	for curNode != nil {
		output = append(output, curNode.Val)

		if curNode.Left != nil {
			if curNode.Right != nil {
				staPendingRightNodes.PushFront(curNode.Right)
			}
			curNode = curNode.Left
		} else {
			if curNode.Right != nil {
				curNode = curNode.Right
			} else {
				if staPendingRightNodes.Front() != nil {
					curNode = staPendingRightNodes.Front().Value.(*TreeNode)
					staPendingRightNodes.Remove(staPendingRightNodes.Front())
				} else { // the end of traversal
					curNode = nil
				}
			}
		}
	}

	return output
}

func main() {
	output := preorderTraversal(
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
	output1 := preorderTraversal(nil)
	output2 := preorderTraversal(
		&TreeNode{
			Val:   1,
			Left:  nil,
			Right: nil,
		})
	output3 := preorderTraversal(
		&TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
			Right: nil,
		})
	output4 := preorderTraversal(
		&TreeNode{
			Val:  1,
			Left: nil,
			Right: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
		})
	output5 := preorderTraversal(
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
