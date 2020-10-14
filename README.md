## 1. Two Sum
1.Build a hash table(key is the value of input array, value is the index of input array)\
2.Traverse the input array and use the hash table to search for the second number

## 3. Longest Substring Without Repeating Characters
1.Use headIndex and endIndex to indicate current substring\
2.Use hash table curSubstr to store all characters in current substring\
3.
```
Increase endIndex by 1 until the end
    if s[endIndex] is in the hash table
        duplicatedCharIndex = curSubstr[s[endIndex]] remove all the elements from headIndex to duplicatedCharIndex in curSubstr
        move headIndex to the right of the duplicated character (headIndex = duplicatedCharIndex + 1)
    else
        add [s[endIndex]]endIndex to curSubstr

    if length of the current substring is longer than maxSubstrLen, update maxSubstrLen.Otherwise continue
```

## 4. Median of Two Sorted Arrays
Gist of the algorithm.
Use binary search to find the boundry that separate both arrays into left and right part.
Make sure all the elemnts in the left part of the first array are smaller than the elements in the right part of the second array, and the elements in the left part of the second array are smaller than the elements in the right part of the first array.

## 7. Reverse Integer
The solution is quite straightforward.
What if we can not use a larger integer(int64) to store the intermediate result?
How do we check the overflow for the add and multiple operation?
In golang, it seems there is no way to do that, because compiler will complain once it finds an overflow result.
However, in C++, the overflow behavior for uint32 is well defined, we can use following tricks to detect an overflow.
```
x = a * b;
if (a != 0 && x / a != b) {
    // overflow handling
}

x = a + b;
if (x < a) {
    // overflow handling
}
```

## 21. Merge Two Sorted Lists

## 27. Remove Element

## 28. Implement strStr()

## 48. Rotate Image
The new coordinate rotating 90 degrees clockwisely can be get through the following formula
```
x' = y
y' = len - 1 - x
```
The major challenge is that allocating another matrix is forbidden.
We can rotate the matrix by the following steps.
For example, the maxtrix length is 6.
| |0|1|2|3|4|5|
|---|---|---|---|---|---|---|
|0|*|*|*|*|*| |
|1| |*|*|*| | |
|2| | |*| | | |
|3| | | | | | |
|4| | | | | | |
|5| | | | | | |

For each starred grid in the above matrix, swap the all four related coordinates. For example{{0,0},{0,5},{5,5},{5,0}}
Beware of the matrix of odd length, it needs to skip this process when it hits the central grid.

## 62. Unique Paths
Typical DP problem.
The robot can only move to either right or down, if it moves right, all the left grids are unavailabe, so the problem turns into a smaller scale one (m-1,n).
Similar case we can get when it moves down.
Based on these findings we can define our recursive solution as follows.
```
findPaths(1, 1) = 1
findPaths(1, 2) = 1 
findPaths(2, 1) = 1
findPaths(m, n) = findPaths(m-1,n) + findPaths(m,n-1)
```
Beware of the edge case (1,1), needs to be checked before running the recursive function.

## 70. Climbing Stairs
```
f(1) = 1
f(2) = 2
f(n) = f(n-2) + f(n-1)
```
## 78. Subsets
define recursive function getCompositions that can get all the compositions of selecting s nums from total t nums.
```
getCompositions(t, s)
    for each num i in t 
        combine i before each composition in getCompositions(t-1, s-1)


utilize this function to get all the compositions s = 1, 2, 3,... len(t)
```


## 79. Word Search
1.Define the subtask that checks the existence of subword with a given starting grid.
2.Set reached flag to true when start checking a grid, but needs to set the flag back to false if the check fails at the grid.

## 94. Binary Tree Inorder Traversal
The recursive solution is quite straightforward, but the iterative solution is a little trickier.
```
// iterative solution
set curNode = root
for curNode != nil
    if curNode.Left is nil or reached
        insert curNode.Val into output list
        flag the curNode as reached

        if curNode.Right is not nil
            set curNode = curNode.Right
        else
            if stackPendingParentNodes is not empty
                set curNode = the top element of stackPendingParentNodes
                remove the top element of stackPendingParentNodes
            else
                curNode = nil // the end of traversal
    else 
        push curNode into stackPendingParentNodes
        set curNode = curNode.Left
```

## 102. Binary Tree Level Order Traversal
```
func calcLayer(parentLayer int, curNode *TreeNode)
    add curNode's value into (parentLayer+1) layer

    //recursively calculate layer for its left and right child node
    if curNode.Left != nil
        calcLayer(parentLayer+1, curNode.Left)
    if curNode.Right != nil
        calcLayer(parentLayer+1, curNode.Right)


//initial call
calcLayer(-1, root)
```


## 133. Clone Graph
1. Use Depth First Search to traverse the connected and undirected graph
2. Cache all reached node

## 144. Binary Tree Preorder Traversal
The recursive solution is quite straightforward, but the iterative solution is a little trickier.
```
// iterative solution
set curNode = root
for curNode != nil
    insert curNode.Val into output list

    if curNode has left child
        push curNode.Right into stackPendingRightNodes
        set curNode = curNode.Left
    else
        if curNode has right child
            set curNode = curNode.Right
        else
            if stackPendingRightNodes is not empty
                set curNode = the top element of stackPendingRightNodes
                remove the top element of stackPendingRightNodes
            else
                curNode = nil // the end of traversal

```

## 145. Binary Tree Postorder Traversal
The recursive solution is quite straightforward, but the iterative solution is a little trickier.
```
// iterative solution
set curNode = root
for curNode != nil
    if both children of curNode are nil or reached 
        insert curNode.Val into output list
        flag curNode as reached

        if stackPendingParentNodes is not empty
            set curNode = the top element of stackPendingParentNodes
            remove the top element of stackPendingParentNodes
        else
            curNode = nil // the end of traversal
    else if curNode.Left is not nil and not reached
        push curNode into stackPendingParentNodes
        set curNode = curNode.Left
    else if curNode.Right is not nil and not reached
        push curNode into stackPendingParentNodes
        set curNode = curNode.Right
```

## 155. Min Stack
It's pretty easy to implement a stack except the GetMin() which requires in constant time as well.
The idea is to cache all the previous min number in the stack.
``` 
Push(x)
    if min >= x         // beware of the equal case which also needs to be cached
        PushInStack(min)
        min = x
    PushInStack(x)

Pop()
    if Top() == min     // if Pop the min number, needs to restore the cached min number
        PopFromStack()
        if Stack is not empty
            min = PopFromStack()
    else
        PopFromStack()
```

## 215. Kth Largest Element in an Array
The first attempt is to sort the input array and then find the Kth largest element. The time complexity is O(nlogn).

A better way is to use max heap. Build the max heap is O(n), and pop the top element and rebuild the heap is O(logn).
The overall time complexity is O(n + Klogn)

## 278. First Bad Version
Typical binary search problem.
If n is bad and n-1 is good, n is the first bad version.
Use binary search to find the first bad version.
A possible optimization is to store all intermediate return results of calling isBadVersion Api.

## 322. Coin Change
This is a typical task that can use the result of smaller scale task.
Note that when get a new solution, need to compare to the existing solution, only update it if the new one is smaller.

## 389. Find the Difference

## 733. Flood Fill
1. Cache all reached grids
2. Use DFS to recursively traverse all the neighbor grids until the grid is either invalid, ,of wrong color, or reached. 

## 763. Partition Labels
```
for each characters in the input string
    create a new partition for the character
    if the character exists in one of the existing partitions
        combine the found partition with all the following partitions
        combine the new partition as well
    else
        add the new partition into the partition list

```

## 767. Reorganize String
```
type charInfo struct {
    character   byte
    count       int
}

for each characters in the input string
    build the max heap of charInfo, the top element of the heap has the largest count

for len(heap) > 0
    move the character of the top element and the second top element alternately into the output string

    if len(heap) == 1 && the last character of output is equal to the character of the only element in the heap
        can not reorganize the input string, break
```

## 909. Snakes and Ladders
Do not use DFS to calculate the steps needed to reach the destination grid for each next grid(+1,+2,+3,+4,+5,+6), this may end up having an infinite loop.
Use BFS to calculate the distance to the start grid for each next gird until hit the destination.

## 973. K Closest Points to Origin
Intuitively, we can calculate the distance for all the points (O(n)), sort (O(nlog n)) and get the first K points.
However, we can optimize the previous procedure by using max heap instead of sorting all the points. Since updating an element in max heap is O(log n).
We can initiate a max heap with the first K points (O(K)) and update the max heap ((n-K)O(log K)).

## 994. Rotting Oranges
Define subtask that checks all the neighbor grids of the given rottedGrids(initial rottedGrids) and recursively call the subtask to check the newly rottedGrids.
Use a counter to store the current number of fresh oranges.

## 1351. Count Negative Numbers in a Sorted Matrix
Use binary search on the first num of all rows.
All the nums of the row that has a first negative num are negative.
Use binary search on each row that has a first non-negative num.

