package main

import (
	"errors"
	"fmt"
)

//binary search tree
type TreeNode struct {
	Val   int
	Len   int // empty node if Len == 0
	Left  *TreeNode
	Right *TreeNode
}

func (t *TreeNode) Insert(value int) *TreeNode {
	//fmt.Println("insert", value, "at", t.Val)
	if t.Len == 0 {
		t.Val = value
		t.Len = 1
		return t
	}

	if t.Val >= value {
		if t.Left != nil {
			t.Left = t.Left.Insert(value)
		} else {
			t.Left = &TreeNode{value, 1, nil, nil}
		}
	} else {
		if t.Right != nil {
			t.Right = t.Right.Insert(value)
		} else {
			t.Right = &TreeNode{value, 1, nil, nil}
		}
	}

	t.Len++

	//fmt.Println("before balance")
	//t.Print()

	//balance the tree, otherwise the top node won't be the median
	newRoot := t.Balance()
	//fmt.Println("after balance")
	//newRoot.Print()

	return newRoot
}

func (t *TreeNode) Balance() *TreeNode {
	var leftLen, rightLen int
	if t.Left != nil {
		leftLen = t.Left.Len
	}
	if t.Right != nil {
		rightLen = t.Right.Len
	}
	newRoot := t
	if leftLen > rightLen && leftLen-rightLen > 1 {
		//find the largest node in the left child tree, and use it as the new root
		maxInLeft := t.Left.Max()
		t.Left = t.Left.Remove(maxInLeft)
		t.Len-- //update length of t as well
		newLeftNode := t.Left
		t.Len -= t.Left.Len
		t.Left = nil
		newRightNode := t
		newRoot = &TreeNode{maxInLeft, newLeftNode.Len + newRightNode.Len + 1, newLeftNode, newRightNode}
	} else if rightLen > leftLen && rightLen-leftLen > 1 {
		//find the largest node in the right child tree, and use it as the new root
		minInRight := t.Right.Min()
		t.Right = t.Right.Remove(minInRight)
		t.Len-- //update length of t as well
		newRightNode := t.Right
		t.Len -= t.Right.Len
		t.Right = nil
		newLeftNode := t
		newRoot = &TreeNode{minInRight, newLeftNode.Len + newRightNode.Len + 1, newLeftNode, newRightNode}
	}

	return newRoot
}

func (t *TreeNode) InsertNode(mergingNode *TreeNode) *TreeNode {
	if mergingNode == nil || mergingNode.Len == 0 {
		return t
	}

	newRoot := t
	newRoot = t.Insert(mergingNode.Val)
	newRoot = t.InsertNode(mergingNode.Left)
	newRoot = t.InsertNode(mergingNode.Right)
	return newRoot
}

//return the new root
func (t *TreeNode) Remove(value int) *TreeNode {
	var leftLen, rightLen int
	if t.Left != nil {
		leftLen = t.Left.Len
	}
	if t.Right != nil {
		rightLen = t.Right.Len
	}

	if t.Val == value { // find the node and remove
		if leftLen == 0 && rightLen == 0 {
			t.Val = 0
			t.Len = 0
			return t
		}

		if leftLen <= rightLen { //right child is deeper
			minInRight := t.Right.Min()
			t.Right = t.Right.Remove(minInRight)
			t.Val = minInRight
			t.Len--
			return t
		} else { //left child is deeper
			maxInLeft := t.Left.Max()
			t.Left = t.Left.Remove(maxInLeft)
			t.Val = maxInLeft
			t.Len--
			return t
		}
	} else if t.Val > value {
		t.Left = t.Left.Remove(value)
		t.Len = t.Left.Len + rightLen + 1
	} else if t.Val < value {
		t.Right = t.Right.Remove(value)
		t.Len = t.Right.Len + leftLen + 1
	}

	//balance the tree, otherwise the top node won't be the median
	newRoot := t.Balance()
	return newRoot
}

func (t *TreeNode) Median() (float64, error) {
	if t.Len <= 0 {
		return 0, errors.New("empty tree")
	}

	var median float64
	if t.Len%2 == 0 {
		var leftLen, rightLen int
		if t.Left != nil {
			leftLen = t.Left.Len
		}
		if t.Right != nil {
			rightLen = t.Right.Len
		}

		if leftLen > rightLen {
			maxInLeft := t.Left.Max()
			median = (float64(maxInLeft) + float64(t.Val)) / 2
		} else {
			minInRight := t.Right.Min()
			median = (float64(minInRight) + float64(t.Val)) / 2
		}
	} else {
		median = float64(t.Val)
	}
	return median, nil
}

func (t *TreeNode) Max() int {
	if t.Right != nil && t.Right.Len != 0 {
		return t.Right.Max()
	}
	return t.Val
}
func (t *TreeNode) Min() int {
	if t.Left != nil && t.Left.Len != 0 {
		return t.Left.Min()
	}
	return t.Val
}

func (t *TreeNode) Print() {
	fmt.Println("val, len", t.Val, t.Len)
	if t.Left != nil {
		fmt.Println("left begin", t.Val)
		t.Left.Print()
		fmt.Println("left end", t.Val)
	}
	if t.Right != nil {
		fmt.Println("right begin", t.Val)
		t.Right.Print()
		fmt.Println("right end", t.Val)
	}
}

func medianSlidingWindow(nums []int, k int) []float64 {
	var output []float64
	//fmt.Println(nums, k)

	var bstRoot *TreeNode

	//build BST
	for i := 0; i < k; i++ {
		if i == 0 {
			bstRoot = &TreeNode{nums[i], 1, nil, nil}
			continue
		}

		bstRoot = bstRoot.Insert(nums[i])
		//fmt.Println("after insert", nums[i])
		//bstRoot.Print()
	}

	if median, err := bstRoot.Median(); err == nil {
		output = append(output, median)
		//fmt.Println(median)
	}

	for i := 1; i <= len(nums)-k; i++ {
		//fmt.Println("    ")
		//fmt.Println("i", i)
		bstRoot = bstRoot.Remove(nums[i-1])
		//fmt.Println("after remove", nums[i-1])
		//bstRoot.Print()
		bstRoot = bstRoot.Insert(nums[i+k-1])
		//fmt.Println("after insert", nums[i+k-1])
		//bstRoot.Print()
		if median, err := bstRoot.Median(); err == nil {
			output = append(output, median)
			//fmt.Println(median)
		}
	}

	return output
}

func main() {
	output := medianSlidingWindow([]int{1, 3, -1, -3, 5, 3, 6, 7}, 3)
	output1 := medianSlidingWindow([]int{1, 4, 2, 3}, 4)
	output2 := medianSlidingWindow([]int{5, 2, 2, 7, 3, 7, 9, 0, 2, 3}, 9)
	output3 := medianSlidingWindow([]int{1, 8, 8, 3, 5, 2, 2, 6, 6, 7}, 8)

	fmt.Println("\n******** output *********\n", output, output1, output2, output3)
}
