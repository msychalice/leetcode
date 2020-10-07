package main

import (
	"fmt"
)

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	fmt.Println(nums1, nums2)
	var median float64
	lenArray1 := len(nums1)
	lenArray2 := len(nums2)

	if lenArray1 == 0 {
		medianIndex := lenArray2 / 2
		if lenArray2%2 == 0 {
			median = float64(nums2[medianIndex-1]+nums2[medianIndex]) / 2
		} else {
			median = float64(nums2[medianIndex])
		}
		return median
	} else if lenArray2 == 0 {
		medianIndex := lenArray1 / 2
		if lenArray1%2 == 0 {
			median = float64(nums1[medianIndex-1]+nums1[medianIndex]) / 2
		} else {
			median = float64(nums1[medianIndex])
		}
		return median
	}

	var array1RightMinIndex, array2RightMinIndex int

	bsStartIndex := 0
	bsEndIndex := lenArray1 - 1

	for {
		array1RightMinIndex = (bsStartIndex + bsEndIndex + 1) / 2
		array2RightMinIndex = (lenArray1+lenArray2+1)/2 - array1RightMinIndex
		fmt.Println(array1RightMinIndex, array2RightMinIndex)

		if array2RightMinIndex < 0 {
			array1RightMinIndex -= 0 - array2RightMinIndex
			array2RightMinIndex = 0
		}

		if array2RightMinIndex > lenArray2 {
			array1RightMinIndex += array2RightMinIndex - lenArray2
			array2RightMinIndex = lenArray2
		}

		if array1RightMinIndex == 0 {
			if nums2[array2RightMinIndex-1] <= nums1[array1RightMinIndex] {
				break
			} else {
				bsStartIndex = array1RightMinIndex
				if bsStartIndex == lenArray1-1 {
					bsStartIndex++
				}
				continue
			}
		}
		if array1RightMinIndex == lenArray1 {
			if nums1[array1RightMinIndex-1] <= nums2[array2RightMinIndex] {
				break
			} else {
				bsEndIndex = array1RightMinIndex - 1
				continue
			}
		}
		if array2RightMinIndex == 0 {
			if nums1[array1RightMinIndex-1] <= nums2[array2RightMinIndex] {
				break
			} else {
				bsEndIndex = array1RightMinIndex - 1
				continue
			}
		}
		if array2RightMinIndex == lenArray2 {
			if nums2[array2RightMinIndex-1] <= nums1[array1RightMinIndex] {
				break
			} else {
				bsStartIndex = array1RightMinIndex
				if bsStartIndex == lenArray1-1 {
					bsStartIndex++
				}
				continue
			}
		}
		if nums1[array1RightMinIndex-1] <= nums2[array2RightMinIndex] &&
			nums2[array2RightMinIndex-1] <= nums1[array1RightMinIndex] {
			break
		}

		if nums1[array1RightMinIndex-1] > nums2[array2RightMinIndex] {
			bsEndIndex = array1RightMinIndex - 1
			continue
		}
		if nums2[array2RightMinIndex-1] > nums1[array1RightMinIndex] {
			bsStartIndex = array1RightMinIndex
			if bsStartIndex == lenArray1-1 {
				bsStartIndex++
			}
			continue
		}
	}

	if (lenArray1+lenArray2)%2 == 0 {
		var maxLeft, minRight int

		if array1RightMinIndex == 0 {
			maxLeft = nums2[array2RightMinIndex-1]
		} else if array2RightMinIndex == 0 {
			maxLeft = nums1[array1RightMinIndex-1]
		} else {
			if nums1[array1RightMinIndex-1] > nums2[array2RightMinIndex-1] {
				maxLeft = nums1[array1RightMinIndex-1]
			} else {
				maxLeft = nums2[array2RightMinIndex-1]
			}
		}

		if array1RightMinIndex == lenArray1 {
			minRight = nums2[array2RightMinIndex]
		} else if array2RightMinIndex == lenArray2 {
			minRight = nums1[array1RightMinIndex]
		} else {
			if nums1[array1RightMinIndex] < nums2[array2RightMinIndex] {
				minRight = nums1[array1RightMinIndex]
			} else {
				minRight = nums2[array2RightMinIndex]
			}
		}

		median = float64(maxLeft+minRight) / 2
	} else {
		if array1RightMinIndex == 0 {
			median = float64(nums2[array2RightMinIndex-1])
		} else if array2RightMinIndex == 0 {
			median = float64(nums1[array1RightMinIndex-1])
		} else {
			if nums1[array1RightMinIndex-1] > nums2[array2RightMinIndex-1] {
				median = float64(nums1[array1RightMinIndex-1])
			} else {
				median = float64(nums2[array2RightMinIndex-1])
			}
		}
	}

	return median
}

func main() {
	output := findMedianSortedArrays([]int{1, 3}, []int{2})
	output1 := findMedianSortedArrays([]int{1, 2}, []int{3, 4})
	output2 := findMedianSortedArrays([]int{0, 0}, []int{0, 0})
	output3 := findMedianSortedArrays([]int{}, []int{1})
	output4 := findMedianSortedArrays([]int{2}, []int{})
	output5 := findMedianSortedArrays([]int{1, 2}, []int{3})
	output6 := findMedianSortedArrays([]int{1}, []int{2, 3})
	output7 := findMedianSortedArrays([]int{2, 3, 4, 5}, []int{1})
	output8 := findMedianSortedArrays([]int{1, 2, 3, 5, 6}, []int{4})
	output9 := findMedianSortedArrays([]int{1, 2, 3, 4, 6, 7, 8}, []int{5})
	output10 := findMedianSortedArrays([]int{3, 4, 5, 6, 7, 8}, []int{1, 2})

	fmt.Println("\n******** output *********\n",
		output, output1, output2, output3, output4, output5, output6, output7, output8, output9, output10)
}
