package main

import (
	"fmt"
)

/**
 * Forward declaration of isBadVersion API.
 * @param   version   your guess about first bad version
 * @return 	 	      true if current version is bad
 *			          false if current version is good
 */
func isBadVersion(version int) bool {
	if version >= 1 {
		return true
	}
	return false
}

func firstBadVersion(n int) int {
	isFirstBadVersion := func(num int) bool {
		if isBadVersion(num) && (num == 1 || !isBadVersion(num-1)) {
			return true
		}
		return false
	}

	var binarySearch func(int, int) int
	binarySearch = func(start int, end int) int {
		if start > end {
			return -1
		}
		if start == end {
			if isFirstBadVersion(start) {
				return start
			} else {
				return -1
			}
		}

		mid := ((end+1)-start)/2 + start

		if isFirstBadVersion(mid) {
			return mid
		} else {
			if isBadVersion(mid) {
				return binarySearch(start, mid-1)
			} else {
				return binarySearch(mid+1, end)
			}
		}
	}
	return binarySearch(1, n)
}

func main() {
	output := firstBadVersion(1)

	fmt.Println("\n******** output *********\n", output)
}
