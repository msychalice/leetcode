package main

import (
	"container/list"
	"fmt"
	"math"
)

func reverse(x int) int {
	if x == 0 {
		return 0
	}

	var abs int
	var sign int
	if x >= 0 {
		abs = x
		sign = 1
	} else {
		abs = x * -1
		sign = -1
	}

	lstByte := list.New()
	for ; abs != 0; abs = abs / 10 {
		lstByte.PushBack(abs % 10)
	}

	var output int
	for e := lstByte.Front(); e != nil; e = e.Next() {
		output = output*10 + e.Value.(int)
		if (sign < 0 && output > math.MaxInt32+1) ||
			(sign > 0 && output > math.MaxInt32) {
			return 0
		}
	}

	return output * sign
}

func main() {
	output := reverse(123)
	output1 := reverse(-123)
	output2 := reverse(120)
	output3 := reverse(0)
	output4 := reverse(1534236469)

	fmt.Println("\n******** output *********\n", output, output1, output2, output3, output4)
}
