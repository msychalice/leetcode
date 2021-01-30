package main

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func isSymmetric(root *TreeNode) bool {
	if root == nil {
		return true
	}

	var isMirror func(*TreeNode, *TreeNode) bool
	isMirror = func(node1, node2 *TreeNode) bool {
		if node1 == nil && node2 == nil {
			return true
		}

		if (node1 == nil && node2 != nil) || (node1 != nil && node2 == nil) || (node1.Val != node2.Val) {
			return false
		}

		return isMirror(node1.Left, node2.Right) && isMirror(node1.Right, node2.Left)
	}

	return isMirror(root.Left, root.Right)
}

func main() {
	output := isSymmetric(
		&TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val: 2,
				Left: &TreeNode{
					Val:   3,
					Left:  nil,
					Right: nil},
				Right: &TreeNode{
					Val:   4,
					Left:  nil,
					Right: nil},
			},
			Right: &TreeNode{
				Val: 2,
				Left: &TreeNode{
					Val:   4,
					Left:  nil,
					Right: nil},
				Right: &TreeNode{
					Val:   3,
					Left:  nil,
					Right: nil},
			},
		})
	output1 := isSymmetric(
		&TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val:  2,
				Left: nil,
				Right: &TreeNode{
					Val:   3,
					Left:  nil,
					Right: nil},
			},
			Right: &TreeNode{
				Val:  2,
				Left: nil,
				Right: &TreeNode{
					Val:   3,
					Left:  nil,
					Right: nil},
			},
		})

	fmt.Println("\n******** output *********\n", output, output1)
}
