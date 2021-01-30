package main

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func invertTree(root *TreeNode) *TreeNode {
	if root != nil {
		root.Left, root.Right = root.Right, root.Left
		invertTree(root.Left)
		invertTree(root.Right)
	}

	return root
}

func main() {
	output := invertTree(
		&TreeNode{
			Val: 4,
			Left: &TreeNode{
				Val: 2,
				Left: &TreeNode{
					Val:   1,
					Left:  nil,
					Right: nil},
				Right: &TreeNode{
					Val:   3,
					Left:  nil,
					Right: nil},
			},
			Right: &TreeNode{
				Val: 7,
				Left: &TreeNode{
					Val:   6,
					Left:  nil,
					Right: nil},
				Right: &TreeNode{
					Val:   9,
					Left:  nil,
					Right: nil},
			},
		})

	fmt.Println("\n******** output *********\n", output)
}
