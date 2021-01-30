package main

import (
	"container/list"
	"fmt"
)

type partition struct {
	startIndex    int
	length        int
	mapCharacters map[byte]bool
}

func (p *partition) hasCharacter(b byte) bool {
	if _, ok := p.mapCharacters[b]; ok {
		return true
	}
	return false
}

func (p *partition) combinePartition(adjacentPartition *partition) {
	p.length += adjacentPartition.length

	for byte, _ := range adjacentPartition.mapCharacters {
		p.mapCharacters[byte] = true
	}
}

func partitionLabels(S string) []int {
	lstPartitions := list.New()

	for i := 0; i < len(S); i++ {
		var foundPartition *list.Element

		//iterate all partitions
		for e := lstPartitions.Front(); e != nil; e = e.Next() {
			if e.Value.(*partition).hasCharacter(S[i]) {
				foundPartition = e
				break
			}
		}

		//fmt.Println("check char", S[i], i)
		newPartition := partition{startIndex: i, length: 1, mapCharacters: map[byte]bool{S[i]: true}}
		if foundPartition != nil {
			//find the character in one of the existing partitions,
			//need to combine the partition with all the following ones, including the new created one

			//fmt.Println("foundPartition", foundPartition.Value.(*partition).startIndex,
			//	foundPartition.Value.(*partition).length, foundPartition.Value.(*partition).mapCharacters)

			for e := foundPartition.Next(); e != nil; e = e.Next() {
				foundPartition.Value.(*partition).combinePartition(e.Value.(*partition))
			}
			foundPartition.Value.(*partition).combinePartition(&newPartition)

			//remove all the elements after foundPartition
			for backEle := lstPartitions.Back(); backEle != foundPartition; {
				prevBackEle := backEle.Prev()
				lstPartitions.Remove(backEle)
				backEle = prevBackEle
			}
		} else {
			//fmt.Println("new partition")
			lstPartitions.PushBack(&newPartition)
		}
	}

	output := []int{}

	for e := lstPartitions.Front(); e != nil; e = e.Next() {
		output = append(output, e.Value.(*partition).length)
	}

	return output
}

func main() {
	output := partitionLabels("ababcbacadefegdehijhklij")

	fmt.Println("\n******** output *********\n", output)
}
