package main

import (
	//"container/list"
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func levelOrder(root *TreeNode) [][]int {
	output := [][]int{}
	pOutput := &output

	var calculateChildrenLayer func(int, *TreeNode)
	calculateChildrenLayer = func(parentLayer int, curNode *TreeNode) {
		if curNode == nil {
			return
		}

		curLayer := parentLayer + 1
		if curLayer < len(*pOutput) {
			(*pOutput)[curLayer] = append((*pOutput)[curLayer], curNode.Val)
		} else if curLayer == len(*pOutput) {
			*pOutput = append(*pOutput, []int{curNode.Val})
		}

		if curNode.Left != nil {
			calculateChildrenLayer(curLayer, curNode.Left)
		}
		if curNode.Right != nil {
			calculateChildrenLayer(curLayer, curNode.Right)
		}
	}

	calculateChildrenLayer(-1, root)

	return output
}

func main() {
	output := levelOrder(
		&TreeNode{
			Val: 3,
			Left: &TreeNode{
				Val:   9,
				Left:  nil,
				Right: nil,
			},
			Right: &TreeNode{
				Val: 20,
				Left: &TreeNode{
					Val:   15,
					Left:  nil,
					Right: nil,
				},
				Right: &TreeNode{
					Val:   7,
					Left:  nil,
					Right: nil,
				},
			},
		})
	output1 := levelOrder(nil)
	output2 := levelOrder(
		&TreeNode{
			Val:   1,
			Left:  nil,
			Right: nil,
		})
	output3 := levelOrder(
		&TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
			Right: nil,
		})
	output4 := levelOrder(
		&TreeNode{
			Val:  1,
			Left: nil,
			Right: &TreeNode{
				Val:   2,
				Left:  nil,
				Right: nil,
			},
		})
	output5 := levelOrder(
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
