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

## 79. Word Search
1.Define the subtask that checks the existence of subword with a given starting grid.
2.Set reached flag to true when start checking a grid, but needs to set the flag back to false if the check fails at the grid.


## 322. Coin Change
This is a typical task that can use the result of smaller scale task.
Note that when get a new solution, need to compare to the existing solution, only update it if the new one is smaller.


## 973. K Closest Points to Origin
Intuitively, we can calculate the distance for all the points (O(n)), sort (O(nlog n)) and get the first K points.
However, we can optimize the previous procedure by using max heap instead of sorting all the points. Since updating an element in max heap is O(log n).
We can initiate a max heap with the first K points (O(K)) and update the max heap ((n-K)O(log K)).


## 994. Rotting Oranges
Define subtask that checks all the neighbor grids of the given rottedGrids(initial rottedGrids) and recursively call the subtask to check the newly rottedGrids.
Use a counter to store the current number of fresh oranges.

