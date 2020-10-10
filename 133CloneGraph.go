package main

import (
	"fmt"
)

type Node struct {
	Val       int
	Neighbors []*Node
}

func cloneGraph(node *Node) *Node {
	mapClonedNode := make(map[int]*Node)

	var funcCloneNode func(*Node) *Node
	funcCloneNode = func(originalNode *Node) *Node {
		if originalNode == nil {
			return nil
		}

		if clonedNode, ok := mapClonedNode[originalNode.Val]; ok {
			return clonedNode
		}

		clonedNode := &Node{}
		clonedNode.Val = originalNode.Val
		mapClonedNode[clonedNode.Val] = clonedNode

		for _, neighborNode := range originalNode.Neighbors {
			clonedNode.Neighbors = append(clonedNode.Neighbors, funcCloneNode(neighborNode))
		}
		return clonedNode
	}

	return funcCloneNode(node)
}

func main() {
	node1 := &Node{Val: 1, Neighbors: nil}
	node2 := &Node{Val: 2, Neighbors: nil}
	node3 := &Node{Val: 3, Neighbors: nil}
	node4 := &Node{Val: 4, Neighbors: nil}
	node1.Neighbors = []*Node{node2, node4}
	node2.Neighbors = []*Node{node1, node3}
	node3.Neighbors = []*Node{node2, node4}
	node4.Neighbors = []*Node{node1, node3}
	output := cloneGraph(node1)

	node1 = &Node{Val: 1, Neighbors: nil}
	output1 := cloneGraph(node1)

	output2 := cloneGraph(nil)

	node1 = &Node{Val: 1, Neighbors: nil}
	node2 = &Node{Val: 2, Neighbors: nil}
	node1.Neighbors = []*Node{node2}
	node2.Neighbors = []*Node{node1}
	output3 := cloneGraph(node1)

	fmt.Println("\n******** output *********\n", output, output1, output2, output3)
}
