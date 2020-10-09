package main

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func isSubtree(s *TreeNode, t *TreeNode) bool {
	var isSameTree func(*TreeNode, *TreeNode) bool
	isSameTree = func(t1 *TreeNode, t2 *TreeNode) bool {
		if t1 == nil && t2 == nil {
			return true
		}

		if (t1 == nil && t2 != nil) || (t1 != nil && t2 == nil) {
			return false
		}

		if t1.Val == t2.Val {
			return isSameTree(t1.Left, t2.Left) && isSameTree(t1.Right, t2.Right)
		} else {
			return false
		}
	}

	return isSameTree(s, t) || (s.Left != nil && isSubtree(s.Left, t)) || (s.Right != nil && isSubtree(s.Right, t))
}

func main() {
	output := isSubtree(
		&TreeNode{Val: 3, Left: &TreeNode{Val: 4, Left: &TreeNode{Val: 1, Left: nil, Right: nil}, Right: &TreeNode{Val: 2, Left: nil, Right: nil}}, Right: &TreeNode{Val: 5, Left: nil, Right: nil}},
		&TreeNode{Val: 4, Left: &TreeNode{Val: 1, Left: nil, Right: nil}, Right: &TreeNode{Val: 2, Left: nil, Right: nil}})

	output1 := isSubtree(
		&TreeNode{Val: 3, Left: &TreeNode{Val: 4, Left: &TreeNode{Val: 1, Left: nil, Right: nil}, Right: &TreeNode{Val: 2, Left: &TreeNode{Val: 0, Left: nil, Right: nil}, Right: nil}}, Right: &TreeNode{Val: 5, Left: nil, Right: nil}},
		&TreeNode{Val: 4, Left: &TreeNode{Val: 1, Left: nil, Right: nil}, Right: &TreeNode{Val: 2, Left: nil, Right: nil}})

	fmt.Println("\n******** output *********\n", output, output1)
}
