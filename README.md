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

solution2.
Sliding window. The most important part is to find the place where to update the final result.


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


## 10. Regular Expression Matching
DP. 
The gist of the approach is to use recursion + memoization to handle infinite matching cases of '*'
Normally, there are infinite matching cases of '*' 0, 1, 2, 3, ...
In each step of recursion, we only need to take care of 0 and 1, call recursive dp function to get the answer of the rest cases


## 15. 3Sum
Sort the input vector, convert it to a 2sum problem and use two pointers algorithm.
Beware of skipping all the duplicate answers.
```
sort(nums)

for (i = 0; i < nums.size(); i++) 
    target = -nums[i]

    // convert the 3sum problem to 2sum problem
    low = i + 1
    high = nums.size() - 1

    while (low < high) 
        if (nums[low] + nums[high] == target)  // found an answer
            //skip all the duplicates by moving low rightwards and high leftwards
        else if (nums[low] + nums[high] < target)
            //move low rightwards
        else if (nums[low] + nums[high] > target)
            //move high leftwards


    //skip all the duplicates by moving i rightwards

```


## 18. 4Sum
Implement a recursive kSum solution.
When k == 2, use two pointers to solve it.


## 19. Remove Nth Node From End of List


## 20. Valid Parentheses


## 21. Merge Two Sorted Lists


## 22. Generate Parentheses
Backtracking


## 25. Reverse Nodes in k-Group


## 26. Remove Duplicates from Sorted Array


## 27. Remove Element


## 28. Implement strStr()


## 34. Find First and Last Position of Element in Sorted Array
Use binary search to find the first and last index.
It's worth noting that we can use the first index as min to optimize the process of finding the last index.


## 35. Search Insert Position


## 36. Valid Sudoku


## 37. Sudoku Solver
Backtracking.


## 42. Trapping Rain Water
```
leftMax[i] = max of height[0...i]                   // the max height of all left heights
rightMax[i] = max of height[i...height.size()-1]    // the max height of all right heights

for each height[i]
    the capacity of trapping water = min(leftMax[i], rightMax[i]) - height[i]
```

Take a closer look to the above algorithm, the capacity is only related to the minimum one of leftMax[i] and rightMax[i]
We can optimize the procedure by using two pointers to traverse the array once.
```
left = 0
right = height.size() - 1
output = 0

leftMax = height[0]
rightMax = height[height.size()-1]

while left <= right
    if leftMax < rightMax 
        output += leftMax - height[left]
        leftMax = max(leftMax, height[left])
        left++
    else
        output += rightMax - height[right]
        rightMax = max(rightMax, height[right])
        right--

return output;
```


## 43. Multiply Strings


## 44. Wildcard Matching
DP.
The approach is pretty the same as #10.


## 45. Jump Game II
```
4 0 3 4 1 4 2 1
---------
  - 
    -------
      ---------
```


## 46. Permutations
Typical backtracking problem.
Beware of updating both curPath and curSelection.


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


## 50. Pow(x, n)
```
base cases: n = 0, 1, -1, 2, -2

if n > 2 || n < -2
    if n is even
        Pow(x, n) = Pow(Pow(x, n/2), 2)

    if n is odd
        Pow(x, n) = Pow(x, n-1) * x
```


## 51. N-Queens
This is a similar problem with 46Permutations which can be solved by backtracking. \
The ith layer of the decision tree represents selected columns for ith row of the chessboard. \
The way of checking two queens are in same diagonal is by checking abs(row1-row2) == abs(col1-col2) \


## 53. Maximum Subarray
DP.
The definition of dp array is similar to #300.Longest Increasing Subsequence.
dp[i] is the max sum of the subarray ending with nums[i]
dp[0] = nums[0] // base case
dp[i] = max(dp[i-1] + nums[i], nums[i])

the final result is the maximum number of dp, not dp[nums.size()-1]


## 54. Spiral Matrix
See code


## 56. Merge Intervals


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
Need to check the hash table that caches all the intermediate results.
Beware of the edge case (1,1), needs to be checked before running the recursive function.


## 63. Unique Paths II
The solution is similar to #62


## 64. Minimum Path Sum
DP.
The 2D DP array can be compressed into 1D.


## 66. Plus One


## 70. Climbing Stairs
```
f(1) = 1
f(2) = 2
f(n) = f(n-2) + f(n-1)
```


## 72. Edit Distance
DP.
Given word1 "horse" and word2 "ros"
dp[i][j] means the min distance between the substring of word1 containing first i characters and the substring of word2 containing first j characters.
for example, dp[1][2] means the min distance between "h" and "ro"
```
//base case
dp[i][0] = i    0 <= i <= word1.size()
dp[0][j] = j    0 <= j <= word2.size()

//transition
if word1[i] == word2[j]
    // no operation is needed
    dp[i+1][j+1] = dp[i][j] 
else
    // starting from dp[i][j] means replacing, dp[i+1][j] means inserting, dp[i][j+1] means deleting
    dp[i+1][j+1] = min(dp[i][j], dp[i+1][j], dp[i][j+1]) + 1

return dp[word1.size()][word2.size()]
```

This problem may looks like 752, having begin and end state and asking minimum operations.
It seems that it can be solved by BFS as well, however the key difference is that the initial state of 72 can be shrinked into samller scale state.


## 76. Minimum Window Substring
Sliding window.
1. Use start and len to store the valid minimum substring.
2. Use left and right to store the window index [left, right).
3. Move right index until the end of source string.
4. Move left index only when there is a valid substring found in the window.
4. Only update the start and len when moving left index.


## 77. Combinations
Backtracking.


## 78. Subsets
define recursive function getCombinations that can get all the combinations of selecting s nums from total t nums.
```
getCombinations(t, s)
    for each num i in t 
        combine i before each combination in getCombinations(t-1, s-1)


utilize this function to get all the combinations s = 1, 2, 3,... len(t)
```


## 79. Word Search
1.Define the subtask that checks the existence of subword with a given starting grid.
2.Set reached flag to true when start checking a grid, but needs to set the flag back to false if the check fails at the grid.


## 83. Remove Duplicates from Sorted list
Similar to 26, use fast and slow pointers.
Beware of handling the last node that is a duplicate.


## 84. Largest Rectangle in Histogram
Monotonic non-decreasing stack.
```
heights.push_back(0);  // add a padding 0 to faciliate the calculation of the real last height
stack stk
output = 0

for i from [0, heights.size()-1]
    while !stk.empty()
        if heights[i] < heights[stk.top()]
        else
            //heights[i] >= heights[stk.top()]
            //For the special case that these two heights are equal, there are identical heights in the stack.
            //This will lead to an error of calculating the area for the first one of the two identical heights,
            //but this won't affect the final result, since the calculation for the last one of the two identical heights is correct.
            break;

        stk.push(i)

return output
```


## 85. Maximal Rectangle
It looks like #221. Maximal Square, but the way to solve it is completely different.
The approach needs to use the function used in #84. Largest Rectangle in Histogram
```
Given the function largestRectangleInHistogram

row = matrix.size()
col = matrix[0].size()
heights[col+1]  //the last padding height[col] is used to faciliate the calculation of largestRectangleInHistogram

output = 0
for i from [0, row-1]   // for each histogram using ith row as its bottom
    for j from [0, col-1]
        heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0
        output = max(output, largestRectangleInHistogram(heights))

return output
```


## 90. Subsets II
We can use the similar algorithm to get all combinations in #78., but needs to check if the newly generated combination is duplicated.
Use hash table (key: number of elements, value: alll the combinations that have the same number of elements) to do the comparison.
Note that the newly generated combination needs to be sorted before inserting into the above hash table or doing the comparison.

---
The better and more offical solution is to use DFS and backtracking.
For an input s having n numbers, the solution is to DFS following tree.

```
                                                     []
                             /                        |                     \
                            [0]                      [1]         ...       [n-1]
               /             |      \             /   |       \              | 
          [0,1]            [0,2] ... [0,n-1]  [1,2]  [1,3] ... [1,n-1]      nil
        / | ... \           /|\
[0,1,2] [0,1,3] [0,1,n-1]   ...
```
Sort the input s
DFS the above tree and check the current node with its previous sibling node, if they are the same, we can skip the current node.
For exampe, if [s[1]] == [s[0]] we can skip the search for the subtree s[1].


## 91. Decode Ways
DP.
```
dp[i] means how many ways to decode substring [0...i]

if s[i] is '0' and needs to append to s[i-1]
    dp[i] == dp[i-2]
if s[i] is not '0' and can not append to s[i-1]
    dp[i] == dp[i-1]
if s[i] is not '0' and can append to s[i-1]
    dp[i] == dp[i-1] + dp[i-2]
```
However, there are several edge cases need to take care of.
1. "301" or "1001"  -- s[i] is '0' and s[i-1] is not '1' or '2'
2. "01" -- s[0] is '0'


## 92. Reverse Linked List II


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


## 97 Interleaving String
DP.
dp[i][j] represents whether first ith substring of s1 and first jth substring of s2 can form first (i+j) substring of s3
```
//base case
dp[0][0] = true
dp[i][0] = dp[i-1][0] && s1[i-1] == s3[i-1]         1 <= i <= s1.size()
dp[0][i] = dp[0][i-1] && s2[i-1] == s3[i-1]         1 <= i <= s2.size()

for i from [1, s1.size()]
    for j from [1, s2.size()]
        dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
                (dp[i][j-1] && s2[j-1] == s3[i+j-1])

return dp[s1.size()][s2.size()]
```


## 100. Same Tree


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


## 105. Construct Binary Tree from Preorder and Inorder Traversal
1. The first node of preorder array is the root.
2. Find the root index in inorder array.
    All the left nodes belong to the left subtree and right nodes are the right subtree.
    We can also know how many nodes the left subtree has.
3. Use the length of the left subtree, we can separate the preorder array into two parts,
    which represent the left subtree and the right subtree.

```
           root "left"  "    right   "
preorder = [3,    9,    20,   15,    7]

         "left"  root   "    right   "
inorder = [9,     3,    15,   20,    7]
```


## 111. Minimum Depth of Binary Tree
BFS


## 114. Flatten Binary Tree to Linked List


## 116. Populate Next Right Pointers in Each Node
Extra space is not allowed, so at first I ruled out using BFS which normally needs a queue.
But after trying to find out a recursive solution and failed, I rethink about the iterative solution.
Actually I can use the result of current level and traverse all the nodes at the same level from left to right.

Recursive solution can be done as follows, 
however it's slower than the iterative one, since there are lots of nodes(middle ones on each level) will be handled twice.
```
connectNode(cur, next)
    if cur == nullptr 
        return

    cur->next = next
    connectNode(cur->left, cur->right)
    connectNode(cur->right, next->left)     // cur->right is handled twice
    connectNode(next->left, next->right)    // next->left is handled twice

connectNode(root->left, root->right)
```


## 117. Populate Next Right Pointers in Each Node II
Similar idea to 116, but needs to change the way of finding the head of each level and the next non-nullptr sibling node.


## 121. Best Time to Buy and Sell Stock
DP.
```
1 <= i <= prices.size()  // ith day
1 <= k <= K             // max transaction

                                rest                    sell
dp[i][k][no_stock] = max(dp[i-1][k][no_stock], dp[i-1][k][has_stock] + prices[i-1])

                                rest                    buy
dp[i][k][has_stock] = max(dp[i-1][k][has_stock], dp[i-1][k-1][no_stock] - prices[i-1])

dp[0][k][no_stock] = 0                             // 0th day has no stock. The profit is 0.
dp[0][k][has_stock] = numeric_limits<int>::min()    // 0th day has stock, which is impossible. Set it to minus infinity.
dp[i][0][no_stock] = 0                             // transaction is not allowed and has no stock. The profit is 0.
dp[i][0][has_stock] = numeric_limits<int>::min()    // transaction is not allowd and has stock, which is impossible. Set it to minus infinity.

return dp[i][k][no_stock]  // ith day with k transaction and no stock
```


## 122. Best Time to Buy and Sell Stock II
Use the same algorithm in #121., except k is infinity.


## 123. Best Time to Buy and Sell Stock III
Use the same algorithm in #121., except 1 <= k <= 2.
We have to use 3 dimension dp, compression is not feasible.


## 127. Word Ladder
BFS. Same as #433.


## 130 Surrounded Regions
It's quite difficult to use DFS to select those surrounds regions, but it's pretty straightforward, if we use DFS in a different direction.
Every 'O' that links to a 'O' at border is not surrounded by 'X'.
1.For each 'O' at border, use DFS to mark all its linked 'O' grid.
2.All the unmarked 'O' are surrounded and need to be changed to 'X'


## 133. Clone Graph
1. Use Depth First Search to traverse the connected and undirected graph
2. Cache all reached node


## 136. Single Number
n ^ n = 0
n ^ 0 = n


## 139. Word Break
DP.
dp[i][j] is the result of s[i...j]
we can convert s[i...j] into two substrings s[i...n-1] and s[n...j]
dp[i][j] = dp[i][n-1] && dp[n][j]


## 141. Linked List Cycle
Fast slow pointers.


## 142. Linked List Cycle II
Fast slow pointers.
When slow == fast, set slow to head again, and move slow and fast pointers in the same slow speed.
When then meet again, the node is the beginning of the cycle.
```
| <--- s ---> | <--- m ---> |
1 ---> 2 ---> 3 ---> 4 ---> 5 ---> 6
              ^                    |
              |---------------------

At first, slow and fast pointer will meet at 5.
Suppose k is the length of cycle.
We can know the distance between slow and head dist(slow)=s+m, dist(fast)=s+m+k
We can know that if dist(fast) = dist(slow) + nk, fast and slow pointers will point to the same node.
Given dist(fast)=s+m+k, dist(slow)=0
dist(fast) + k-m means fast pointer will point to the beginning of the cycle.
dist(fast) = dist(fast) + k-m = s+m+k+k-m = s+2k
dist(slow) = 0 + s = s
dist(fast) = dist(slow) + 2k means they point to the same node, which is the beginning of the cycle.
```


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


## 146. LRU Cache
Need to implement the LinkedHashMap data structure.
Use the double linked list to keep the least recently used element at the front.
Use the hash map to access each elemnt in O(1) time.

Beware of handling the prev pointer of the double linked list while adding and removing element of the list.


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


## 167. Two Sum II
Low and high pointers.


## 172. Factorial Trailing Zeroes
answer = n / 5^1 + n / 5^2 + ... + 0


## 174. Dungeon Game
DP.
It's not right if we define dp[i][j] as the minimum damage the knight will get when he reaches dungeon[i][j]
We have to think it reversely and define the dp table as follows
dp[i][j] represents the minimum health the knight needs when he starts from dungeon[i][j]
```
row = dungeon.size()
col = dungeon[0].size()
dp[i][j] is initialized with INT_MAX        0 <= i <= row, 0 <= j <= col
dp[row][col-1] = dp[row-1][col] = 1         // faciliate the calculation of dp[row-1][col-1]

for i from [row-1, 0]
    for j from [col-1, 0]
        dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j])

return dp[0][0]
```


## 188. Best Time to Buy and Sell Stock IV
Use the same algorithm in #121., except 1 <= k <= K.

Because every transaction needs days at least,
when k is greater or equal to prices.size()/2, we can treat k as infinity.
In such case, k == k - 1, and we can compress the dp to 2 dimension.
But when k is less than prices.size()/2, we can't apply this compression.


## 191. Number of 1 Bits


## 198. House Robber
DP.
```
1 <= i <= nums.size()

dp[i][rob] = dp[i-1][notrob] + nums[i-1]
dp[i][notrob] = max(dp[i-1][notrob], dp[i-1][rob])

dp[0][rob] = -infinity // impossible
dp[0][notrob] = 0

return max(dp[nums.size()][rob], dp[nums.size()][notrob])
```


## 200. Number of Islands
Use DFS to search for an island.


## 204. Count Primes
Sieve of Eratosthenes.
```
Ruling out all the non primes.

 12 = 2 * 6
 12 = 3 * 4
 12 = sqrt(12) * sqrt(12)
 12 = 4 * 3
 12 = 6 * 2

 Only need to check those multiplier less than sqrt(n)
 For n = 12
 rule out
 2*2, 2*3, 2*4, 2*5
 3*2, 3*3   // 3*2 is already set, so actually we can start from 3^2
```


## 206. Reverse Linked List


## 207. Course Schedule
Topological sort. DFS.
```
build adjacency list

hasCircle(node)
    if node is visited 
        return false
    if node is visiting
        return true

    mark node as visiting

    for each neighbor node
        if hasCircle(neighbor)
            return true

    mark node as visited
    //add node at the head of ordered_list(topological sort)
    return false

for each node
    if node is not visited
        if hasCircle(node)
            return false
return true
```


## 210. Course Schedule II
Similar to #207.
Topological sort. DFS.
Note that needs to handle all the nodes, even if it is not connected with anyone else.


## 213. House Robber II
DP.
The solution is similar to #198., but it needs to add a new state "firstrob/firstnotrob".
The new state needs to be passed down all the way to the last one.
```
2 <= i <= nums.size()

// if the first one is robbed, the last one can not be robbed.
dp[i][rob][firstrob] = i == nums.size() ? -infinity : dp[i-1][notrob][firstrob] + nums[i-1] 
dp[i][notrob][firstrob] = max(dp[i-1][notrob][firstrob], dp[i-1][rob][firstrob])

dp[i][rob][firstnotrob] = dp[i-1][notrob][firstnotrob] + nums[i-1] 
dp[i][notrob][firstnotrob] = max(dp[i-1][notrob][firstnotrob], dp[i-1][rob][firstnotrob])

// base case
dp[1][rob][firstrob] = nums[0]
dp[1][notrob][firstrob] = -infinity // impossible
dp[1][rob][firstnotrob] = -infinity // impossible
dp[1][notrob][firstnotrob] = 0


//get the maximum one of the above four cases. 
//It is interesting that when i == 1, the result is dp[i][rob][firstrob], but when i > 1, dp[i][rob][firstrob] is -infinity
return max(dp[nums.size()][rob][firstrob], dp[nums.size()][notrob][firstrob], dp[nums.size()][rob][firstnotrob], dp[nums.size()][notrob][firstnotrob])
```


## 215. Kth Largest Element in an Array
The first attempt is to sort the input array and then find the Kth largest element. The time complexity is O(nlogn).

A better way is to use max heap. Build the max heap is O(n), and pop the top element and rebuild the heap is O(logn).
The overall time complexity is O(n + Klogn)

The most efficient algrithm is to use quick selection, which is similar to quick sort.
The average time complexity si O(n), but the worst cast of quick selection is O(n^2).
In order to avoid it, we need to randomize the input array.


## 221. Maximal Square
DP.
Similar to #174., we needs to think it reversely.
dp[i][j] means the area of the maximal square starting from (i,j) to (row, col)
```
row = matrix.size()
col = matrix[0].size()

//base case
dp[row-1][i] = martix[row-1][i] == '1' ? 1 : 0
dp[i][col-1] = martix[i][col-1] == '1' ? 1 : 0

for i from [row-2, 0]
    for j from [col-2, 0]
        dp[i][j] = matrix[i][j] == '1' ? 1 : 0
        
        if dp[i][j] == 1    // it's possible to form a larger square
            len_i1_j = sqrt(dp[i+1][j])
            len_i_j1 = sqrt(dp[i][j+1])
            len_i1_j1 = sqrt(dp[i+1][j+1])
            len = min(min(len_i1_j, len_i_j1), len_i1_j1) + 1
            dp[i][j] = len * len


//find the maximal square
output = 0
for i,j in dp
    output = max(output, dp[i][j])

return output
```


## 222. Count Complete Tree Nodes
```
CountNodes(root)
    height = the height of root
    leftHeight = height - 1
    rightHeight = the height of right subtree

    // left subtree is a full binary tree
    if leftHeight == rightHeight
        return pow(2, leftHeight) - 1 + CountNodes(root->right) + 1

    // right subtree is a full binary tree
    if leftHeight > rightHeight
        return pow(2, rightHeight) - 1 + CountNodes(root->left) + 1

    // leftHeight can not be smaller than rightHeight
```


## 224. Basic Calculator
See code


## 225. Implement stack using queues


## 226. Invert Binary Tree


## 227. Basic Calculator
See code


## 230. Kth Smallest Element In a BST


## 231. Power of Two
n <=0 return false
n is power of two when (n & (n-1)) == 0 


## 232. Implement Queue using Stacks
```
Given two stacks, stackPop and stackPush

For the Push operation:
    move all the elements from stackPop to stackPush
	push the new element to stackPush
	move all the elements back from stackPush to stackPop
```
See code for an optimized solution that can reduce the time complexity of Push operation from O(n) to O(1).


## 234. Palindrome Linked List
1. Calculate the length
2. Reverse the first length/2 nodes
3. Compare the first length/2 nodes with the last length/2 nodes


## 236. Lowest Common Ancestor of a Binary Tree
An intuitive solution is to find the ancestor path for each node and compare these two paths.

The better solution is to use postorder traversal to calculate the state(left, mid, right) for each node.
left/right == 1 means found a target in left/right subtree, mid == 1 means node is one of the target nodes
Whenever left+mid+right >= 2, the lowest common ancestor is found.


## 239. Sliding Window Maximum
Use monotonic decreasing queue to be the window.
The front of the queue is the max num.
Extend window: remove all the smaller nums before adding the new num.
Shrink window: remove the front only if the front is equal to its original num(nums[i-k+1])


## 241. Different Ways to Add Parentheses
Divide and conquer


## 276. Paint Fence
Locked.
DP.
The gist of the solution is to define the dp state properly.
If we define dp[i][j] as the ways of painting i fences with j colors, we can not get a state transition function.
We need to define dp[i][j] as follows
dp[i][j] is the ways of painting i fences with the last two fences painted with the same color or different colors.
0 <= i < n,  0 <= j <= 1, j == 0 means the last two fences painted with the same color, j == 1 means different colors, k is the number of colors
```
//base case
dp[0][0] = k            // one fence, there are k ways to paint it
dp[0][1] = 0            // one fence, impossible to paint it with different colors
dp[1][0] = k            // two fences, there are k ways to paint them with the same color
dp[1][1] = k * (k-1)    // two fences, there are k * (k-1) ways to paint them with two different colors

dp[i][0] = dp[i-1][1]                                   // x y (y)
dp[i][1] = dp[i-1][0] * (k-1) + dp[i-1][1] * (k-1)      // x x (not x)  or  x y (not y)

return dp[i][0] + dp[i][1]  // x x and x y
```


## 277. Find the Celebrity
By calling knows(i,j) we can identify i or j is not a celebrity.
If i knows j, i is not a celebrity. If i doesn't know j, j is not a celebrity.
We can use two passes to find the celebrity.
1.Find a celebrity candidate by ruling out those who can be identified not a celebrity.
2.Make sure the candidate doesn't know anyone and is known by all the others.


## 278. First Bad Version
Typical binary search problem.
If n is bad and n-1 is good, n is the first bad version.
Use binary search to find the first bad version.
A possible optimization is to store all intermediate return results of calling isBadVersion Api.


## 279. Perfect Squares
DP.
dp[i] is the least number perfect square numbers that sum to i.
dp[0] is used for padding only.

```
// base case
dp[i*i] = 1     1 <= i <= sqrt(n)
dp[0] = 0

for i from [2, n]
    for j from [1, sqrt(i)]
        dp[i] = min(dp[i], dp[i-j*j] + 1)

return dp[n]
```


## 283. Move Zeroes
Similar to 27
Fast and slow pointers.
Make sure [0...slow-1] doesn't include 0


## 295. Find Median From Data Stream
Similar to 480. Use multiset to store the stream data and maintain the leftmid iterator in the add function.


## 297. Serialize and Deserialize Binary Tree
Serialize:
    Use preorder traversal to serialize the binary tree.
    Use ',' to separate each node and '#' to indicate a null child node.

Deserialize:
    Given only a preorder result, we normally can not build a binary tree.
    But here we have a full binary tree(null child nodes are filled by '#'), we can build a binary tree in preorder.


## 300. Longest Increasing Subsequence
The first approach is to use DP.
dp[i] means the LIS of the subarray ending with ith element.
if we can find an element nums[j] that is less than nums[i], j ranges from 0 to i-1,
we can know that nums[i] can be appended to the LIS of dp[j] and form a new LIS with length of dp[j]+1

The second approach that uses binary search is quicker than the above one.
<https://leetcode.com/problems/longest-increasing-subsequence/solution/>


## 309. Best Time to Buy and Sell Stock with Cooldown
Use the same algorithm in #121., except k is infinity and has cooldown limit.
Since k is infinity, we can ignore it.
Since we have cooldown limit, we need to introduce the third state "in_cooldown"

```
dp[i][in_cooldown] = dp[i-1][has_stock] + prices[i-1]                       //sell
dp[i][no_stock] = max(dp[i-1][no_stock], dp[i-1][in_cooldown])              //rest
dp[i][has_stock] = max(dp[i-1][has_stock], dp[i-1][no_stock] - prices[i-1]) //rest or buy

dp[0][in_cooldown] = numeric_limits<int>::min()
dp[0][no_stock] = 0
dp[0][has_stock] = numeric_limits<int>::min()

return max(dp[i][k][no_stock], dp[i][k][in_cooldown])
```


##  310. Minimum Height Trees
1.Tree is a special graph with n vertices and n-1 edges.
2.Use adjacency sets to store the graph data
3.Use BFS to trim the leaf nodes until there are at most two nodes left.
4.The reason why there are at most two centroids, see <https://leetcode.com/problems/minimum-height-trees/solution/>


## 312. Burst Balloon
DP.
Add two virtual balloon at the beginning and at the end of nums
dp[i][j] represents the max coins we can get by shooting balloons from (i,j)  0 <= i,j <= nums.size()+1
if we choose k as the last bursted balloon between i and j, we can get following transition function
```
//base case 
dp[i][i+1] = 0   0 <= i <= nums.size()

for k from (i,j)
    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + nums[i-1] * nums[k-1] * nums[j-1])

return dp[0][nums.size()+1]
```


## 316. Remove Duplicate Letters
The basic idea is to use monotonic increasing stack which is used at #496.
We can use deque and operate at the back of the deque and output characters from the front.

```
for each input character c
    if c is already pushed into deque
        ignore c
        continue

    while deque.back() > c and deque.back() will appear later
        deque.pop_back()

    deque.push_back(c)

string(deque.begin(), deque.end())
```


## 322. Coin Change
This is a typical task that can use the result of smaller scale task.
Note that when get a new solution, need to compare to the existing solution, only update it if the new one is smaller.


## 332. Reconstruct Itinerary
1. build graph
2. for each vertices, sort its edges
3. DFS(root)

```
listPath

DFS(u):
    while u has unvisited edge(u,v)
        mark edge(u,v) visited
        DFS(v)

    listPath.push_front(u)
```

We can also optimize the above algorithm by using min heap, so we can save the sort in step 2.

It's worth noting that we can have multiple identical tickets.


## 337. House Robber III
DP.
Set the root node as the target, and the bottom up procedure is to use postorder traversal.
```
postorder(root)
    if root == nullptr 
        return 0,0

    leftRob, leftNotRob = postorder(root.left)
    rightRob, rightNotRob = postorder(root.right)

    rob = root.val + lefNotRob + rightNotRob
    notRob = max(leftNotRob, leftRob) + max(rightNotRob, rightRob)

    return rob,notRob

rootRob, rootNotRob = postorder(root)
return max(rootRob, rootNotRob)
```


## 341. Flatten Nested List Iterator


## 344. Reverse String
Low and high pointers


## 354. Russian Doll Envelopes
The gist of the solution is to sort the input properly and the original problem can be converted into finding Longest Increasing Subsequence.
Sort the input by width in ascending order and by height in descending order if two widths are the same.
Then we can find LIS in the sequence of heights.


## 355. Design Twitter
The gist of the solution is to use priority_queue to get the 10 most latest tweets.
All the tweets of a user are stored in a single-linked list, which is very convenient to get the next tweet.

Algorithm for getNewsFeed
1.Get the latest tweet of all the followees, including itself,
    and push those tweets into a priority_queue which is a max heap.
2.Pop the top tweet of the priority_queue, and get the next tweet of it.


## 363. Max Sum of Rectangle No Larger Than K
1. Compress the matrix into 1D array, 
2. Given the 1D array, the original problem is now converted to finding the max subarray sum no larger than k
3. Similar to finding the subarray sum equals K(#560), we can use prefix sum, but cannot use hashmap, since we have to find the sum no larger than k.
The following is how to find the sum no larger than k
```
sumRectangle == preSum[j] - preSum[i]        // j >= i
preSum[j] - sumRectangle == preSum[i]

res = INT_MIN   // preSum can be negative
for each preSum[j]
    // lower_bound is the value in set no larger than preSum[j] - k
    lower_bound = set.lower_bound(preSum[j]- k)

    // (preSum[j] - lower_bound) is a candidate sum of rectangle
    res = max(res, preSum[j] - lower_bound);

return res
```
In step1, different than #85, here we need to compress rows from [i,j]  0 <= i, j <= row.
And if row is larger than col, we need to compress the matrix horizontally, not vertically.


## 372. Super Pow
```
(a * b) % base = (a % base) * (b % base) % base

a^k % base = (a % base) * (a^(k-1) % base) % base   // recursive
```


## 375. Guess Number Higher or Lower II
DP.
dp[i][j] is the minimum money to win a game with number [i, j]
```
//padding dp[0][j] dp[i][0]
//base case
dp[i][i] = 0

for i from [n-1, 1]
    for j from [i+1, n]
        dp[i][j] = INT_MAX

        for x from [i, j]
            left = x > i ? dp[i][x-1] : 0   //boundary check
            right = x < j ? dp[x+1][j] : 0  //boundary check
            dp[i][j] = min(dp[i][j], max(left, right) + x)

return dp[1][n]
```


## 380. Insert Delete GetRandom O(1)
It's intuitive to think of using hashset to achieve O(1) insert and delete, but hashset cannot getRandom at O(1).
The only way to make getRandom at O(1) is to use array, but how can we guarantee O(1) insert and delete on an array?
The trick is to insert at the back of the array, and swap the element that needs to be deleted with the last one and then delete it.


## 382. Linked List Random Node
GetRandom over a list of unknown size with constant space, we need to use reservoir sampling algorithm.


## 383. Ransom Note


## 384. Shuffle an Array
Fisher-Yates Algorithm


## 389. Find the Difference


## 392. Is Subsequence
The simple solution is to use two pointers. Time O(n)

For the follow up question.
Use a map to store all the indices of a character in ascending order


## 398. Random Pick Index
Reservoir sampling


## 399. Evaluate Division
1. convert all variable names into int index.
2. build a two dimension array calcResult to store division results.

calcResult[v0][v1] = v0 / v1
calcResult[v1][v0] = 1 / calcResult[v0][v1]
calcResult[v0][v0] = 1

```
DFS(u, v, mapVisited):
    if calcResult[u][v] != 0
        return calcResult[u][v]

    while u has unvisited neighbor n
        mark u visited
        result = DFS(n, v, mapVisited)
        if result > 0 
            result = calcResult[u][n] * result
            calcResult[u][v] = result
            calcResult[v][u] = 1 / result
            return result

    return -1
```


## 416. Partition Equal Subset Sum
It is similar to the Knapsack problem and we can use DP to solve it as well.
1. Check if the totalSum is even or not. If it is not even, return false.
```
target = totalSum / 2
lenNums = size of the nums

cachedResult[lenNums+1][target+1]

for i = 1; i <= lenNums; i++   // first i nums
    curNum = nums[i-1]
    for j = 1; j<= target; j++  // possible target
        if j < curNum // newly added num is less than target, which mean the newly added num is useless.
            cachedResult[i][j] = cachedResult[i-1][j]
        if j == curNum // found an answer
            cachedResult[i][j] = true
        if j > curNum // 
            cachedResult[i][j] = cachedResult[i-1][j] || cachedResult[i-1][j-curNum]


return cachedResult[lenNums][target]
```

It is worth noting that cachedResult[i][j] is only related to cachedResult[i-1][j], so we can use 1D array to reduce space complexity.
```
cachedResult[target+1]

for i = 1; i <= lenNums; i++   // first i nums
    curNum = nums[i-1]
    for j = target; j>= curNum; j--  // update from right to left, so we don't overwrite the last results
        if j == curNum // found an answer
            cachedResult[j] = true
        if j > curNum // 
            cachedResult[j] = cachedResult[j] || cachedResult[j-curNum]


return cachedResult[target]
```


## 433. Minimum Genetic Mutation
BFS. Same as #127.


## 435. Non-overlapping Intervals
Greedy.
```
Sort all the intervals [lo, hi] by hi in ascending order

curHi = intervals[0][1] // hi of the first interval

for i from [2, intervals.size() -1]
    if intervals[i][0] < curHi
        // find an overlapping interval
    else 
        // jump to the next non-overlapping interval
        curHi = intervals[i][1]
```


## 438. Find All Anagrams in a String
It's a similar problem to #567, except it needs to collect all the permutations.


## 448. Find All Numbers Disappeared in an Array
Swap nums[i] to the right position, which is nums[i] - 1
For example, value 3 needs to be swapped to nums[2]
Beware of the case the nums[i] is duplicated and is already at the right position.


## 450. Delete Node in a BST


## 452. Minimum Number of Arrows to Burst Ballons
Greedy.
Similar to 435


## 460. LFU Cache


## 480. Sliding Window Median
Use multiset in C++ to store the sliding window, which is a binary search tree.
The tricky is to maintain the iterator of the left mid, which is the median for a odd window and left median for an even window.

It is worth noting that inserting a value that is already existed in the multiset will add the new value *after* those existed values.
1 2 3 3 *3(new)* 4 4
However, using erase(lower_bound()) will remove the front of those existed values.
1 2 *3(removed)* 3 3 4 4


## 494. Target Sum
DP.
It not difficult to summarize the definition of dp, but there are some details that we need to pay attention to.
1. '+0' and '-0' are two valid cases
2. S can be negative
3. the result of all possible choices are within [-sum, sum], here we need to shift it to [0, 2 * sum]
4. when we do space compression, dp[i][j] needs to be reset at first
5. recursion + memoization is faster than bottom up dp table, but it uses more space.

dp[i][j] represents how many ways to assign symbols of first i numbers to make a sum that equals to j(original sum is shifted from [-sum,sum] to [0, 2*sum]
```
//base case
// can not use =, have to use +=
// in case nums[0] == 0, dp[0][sum] needs to be set to 2
// the rest of dp[0][i]s are set to 0 by default
dp[0][sum - abs(nums[0])] += 1;
dp[0][sum + abs(nums[0])] += 1;

for i from [1, nums.size()-1]
    for j from [0, 2*sum]
        if j - nums[i] >= 0 && j - nums[i] <= 2 * sum
            // put '-' in front of nums[i]
            dp[i][j] += dp[i - 1][j - nums[i]]

        if j + nums[i] >= 0 && j + nums[i] <= 2 * sum
            // put '+' in front of nums[i]
            dp[i][j] += dp[i - 1][j + nums[i]]

return dp[nums.size()-1][S+sum] // shift by adding sum
```


## 496. Next Greater Element I
Use monotonic increase stack.


## 503. Next Greater Element II
Similar to 496.
Double the size of the input array, it's the common practice to address circular input array problem.


## 516. Longest Palindromic Subsequence
DP.
dp[i][j] represents the longest palindromic subsequence of s[i...j]
```
//base case
dp[i][i] = 1

for i from [s.size()-2, 0]          // iterate reversely
    for j from [i+1, s.size()-1]
        if s[i] == s[j]
            dp[i][j] = dp[i+1][j-1] + 2
        else
            dp[i][j] = max(dp[i+1][j], dp[i][j-1])

return dp[0][s.size()-1]
```


## 518. Coin Change 2
My first attempt is to use naive DP.
```
f[i][j] means using first i coins to make the changes for j amount.

f[0][...] = 0 // first row is assigned to 0
f[...][0] = 1 // first column is assigned to 0, if amount is 0, we only have one combination which is not using any coins.

for i=1; i<=coins.size(); i++
    for j=1; j<=amount; j++
        f[i][j] = f[i-1][j] + f[i-1][j-coins[i-1]] + f[i-1][j-coins[i-1]*2] + f[i-1][j-coins[i-1]*3] + ...
```

Take a closer look we can find out that the second part of f[i][j] is the case using coins[i-1], which is equal to f[i][j-coins[i-1]]
So we can optimize the above solution as follows
```
for i=1; i<=coins.size(); i++
    for j=1; j<=amount; j++
        f[i][j] = f[i-1][j] + f[i][j-coins[i-1]]
```
Furthermore, we can use the similar technique used in 0/1 Knapsack problem to reduce the f from 2D to 1D.

```
f[0] = 1 // if amount is 0, we only have one combination which is not using any coins.
f[1..] = 0

for i=1; i<=coins.size(); i++
    for j=coins[i-1]; j<=amount; j++
        f[j] = f[j] + f[j-coins[i-1]]
```


## 538. Convert BST to Greater Tree
Use reversed inorder traversal, time O(N), space O(N).
There is a better solution called Morris traversal which can reduce the space complexity to O(1).


## 547. Friend Circles
Typical disjoint sets problem, use union find to solve it.
Use -1 as the initial root value for each node.
-2 means it's a root node and there are 2 nodes in the set.
We can utilize this to merge smaller sets into larger sets when performing union operation.
This will reduce overall cost of find operation.
We also use path compression in find operation.


## 560. Subarray Sum Equals K
Cumulative sum.
```
cumSum.size() = nums.size() + 1
cumSum[0] = 0 // base case
cumSum[i] = sum of nums[0..i-1]
nums        1   2   3
cumSum  0   1   3   6

The sum of subarray nums[i...j] = cumSum[j+1] - cumSum[i]
k = cumSum[j+1] - cumSum[i]
cumSum[i] = cumSum[j+1] - k
The answer is to get how many elements which index are less than j+1 in the cumSum are equal to cumSum[i]
```


## 567. Permutation in String
Sliding window.
Beware that the target is to find a substring not a subset, so any incontinuous candidate in window needs to be ruled out.


## 583. Delete Operation for Two Strings
1.Get the length of LCS(longest common subsequence)
2.return word1.size() - lenLCS + word2.size() - lenLCS


## 645. Set Mismatch
Same as 448


## 652. Find Duplicate Subtrees
The gist of the solution is to use postorder traversal to serialize all subtrees, and use hashtable to find the duplicate ones.


## 654. Maximum Binary Tree


## 684. Redundant Connection
Union find.


## 685. Redundant Connection II
Union find.\
There are 2 major cases.
1. There isn't a vertex having two parents. In such case, it is the same problem as #684.
2. There is a vertex v having two parents p1 and p2. And there are two subcases.\
2.1 Adding one of these two edges will form a circle.\
2.2 Adding neither the first edge nor the second edge will form a circle.\
We still need to use union find, but delete the second edge (p2, v) before using the union find.\
If we find a circle by adding all the edges except the deleted one, return the first edge.\
Otherwise, return the second edge. Because if adding the second edge form a circle, we should return the second edge.\
If not form a circle, which means adding one of these two edges won't form a circle, in such case return the second edge as well.


## 710. Random Pick with Blacklist
The blacklist convert the array into an inconsecutive array.
How can we convert it back to a consecutive array?
The solution is to use hashmap to map the nums in the blacklist to the ones that at the back of the original array.

It's worth noting that those nums in the blacklist and greater or equal than N-blacklist.size() will never be selected.
When we find a candidate from the back of the original array, we have to make sure it is not in the blacklist.


## 712. Minimum ASCII Delete Sum for Two Strings
DP.
Similar to 1143. find LCS(Longest Common Subsequence)
dp[i][j] represents the minimum ASCII delete sum of s1[0...i-1] and s2[0...j-1]
```
//base case 
dp[i][0] = dp[i-1][0] + s1[i-1]
dp[0][i] = dp[0][i-1] + s2[i-1] 

for i from [1, text1.size()]
    for j from [1, text2.size()]
        if text1[i-1] == text2[j-1] // text1[i-1] is in LCS, delete nothing
            dp[i][j] = dp[i-1][j-1] 
        else                        // at least one of text1[i-1] and text2[j-1] is not in LCS
            dp[i][j] = min(dp[i-1][j] + s1[i-1], dp[i][j-1] + s2[j-1])

return dp[text1.size()][text2.size()]
```
Similarly, we can compress dp array, but the base case dp[i][0] needs to be moved in to the inner loop of text1. See code.


## 714. Best Time to Buy and Sell Stock with Transaction Fee
Use the same algorithm in 121, except k is infinity and fee will be deducted from profit for each sell.


## 733. Flood Fill
1. Cache all reached grids
2. Use DFS to recursively traverse all the neighbor grids until the grid is either invalid, ,of wrong color, or reached. 


## 739. Daily Temperatures
Similar to 496


## 752. Open the Lock
BFS. The start node is "0000" and it has 8 neighbors.


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


## 773. Sliding Puzzle
BFS


## 785. Is Graph Bipartite
Graph coloring + BFS \
Note that different with regular BFS, we have to traverse all the vertices to handle the isolated vertices.


## 793. Preimage Size of Factorial Zeroes Function
Use binary search to get the left and right bound of K


## 815. Bus Routes
BFS.\
For each stop s, the next layer contains all the stops that can be reached by taking all the buses going through stop s.\
Ignore visited stops and buses to speed up the BFS.


## 841. Keys and Rooms
Graph traversal. DFS/BFS


## 855. Exam Room
Use set to store line segments [a,b], all the segments will be sorted by their distance.
The definition of distance is (b - a + 1) / 2, which is the middle position, not b - a + 1
We need to add two virtual seats -1 and N, otherwise we will lose control of left-most and right-most segments.
The distance of left-most segment [-1, b] is b
The distance of right-most segment [a, N] is N-a-1


## 863. All Nodes Distance K in Binary Tree
BFS.\
The next layer contains all the child nodes and the parent node. \
When BFS reaches the target distance layer, stop searching for the next layer, and all the nodes in the queue are the result.


## 875. Koko eating bananas


## 886. Possible Bipartition
Graph coloring + BFS.
Similar to #785.

## 887. Super Egg Drop
This is a hard problem.
If we can have unlimited eggs, we definitely can use binary search to find the answer.
However now we only have K eggs, when K == 1, we have to use linear search to find the answer.
How about using binary search when K >= 1 and turn to linear search when K == 1?
Unfortunately this won't lead to the correct answer.
For example, given K == 2, N == 100, using the above algorithm we will get the answer 50, which is not correct.
A simple better answer, which is still not the optimal one, is to throw the first egg at 10,20,30,...90th floor, and this will only needs about 20 times.

So we have to use DP to solve this problem.
Define the state, base case, target case and state transition function as follows
```
//state transition function
K >= 2, N >=1
dp[K][N] = min(
    max(dp[K-1][0], dp[K][N-1]) + 1, // throw the egg at the 1th floor
    max(dp[K-1][1], dp[K][N-2]) + 1, // throw the egg at the 2th floor
    ...
    ...
    max(dp[K-1][N-1], dp[K][0]) + 1 // throw the egg at the Nth floor
)

//base case
dp[K][0] = 0
dp[1][N] = N

//target case
dp[K][N]
```

The above algorithm does give me the correct answer, but it exceeds the time limit...
The problem is the state transition function searches all the possible states linearly, which is not efficient.
dp[K][N] is related to dp[K-1][i] and dp[K][N-i-1], 0 <= i <= N-1
Given the monotonicity of both dp[K-1][i] and dp[K][N-i-1], we can use binary search to accelerate the searching.
It is worth noting that using binary search needs to jump to different states, so we can not use bottom-up technique that requires changing state sequentially.
```
K >= 2, N >=1

mem[K-1][N] // K >= 2, N >= 1, only needs K-1 rows, N columns

dp(K, N)
    //base case
    if K == 1
        return N
    if N == 0
        return 0

    //memoization
    if mem[K-2][N-1] has value
        return mem[K-2][N-1]

    result = infinity
    lo = 1
    hi = N + 1;
    // binary search, right-mid mode
    while (lo < hi)
        mid = (lo + hi) / 2
        broken = dp(K - 1, mid - 1)
        notBroken = dp(K, N - mid)
        if broken < notBroken // move mid rightwards
            lo = mid + 1
            result = min(result, notBroken + 1)
        else
            hi = mid
            result = min(result, broken + 1)

    mem[K - 2][N - 1] = result
    return result


//target case
return dp(K, N)
```


## 909. Snakes and Ladders
Do not use DFS to calculate the steps needed to reach the destination grid for each next grid(+1,+2,+3,+4,+5,+6), this may end up having an infinite loop.
Use BFS to calculate the distance to the start grid for each next grid until hit the destination.


## 973. K Closest Points to Origin
Intuitively, we can calculate the distance for all the points (O(n)), sort (O(nlog n)) and get the first K points.
However, we can optimize the previous procedure by using max heap instead of sorting all the points. Since updating an element in max heap is O(log n).
We can initiate a max heap with the first K points (O(K)) and update the max heap ((n-K)O(log K)).


## 986. Interval List Intersections


## 990. Satisfiability of Equality Equations
Union find.


## 994. Rotting Oranges
Define subtask that checks all the neighbor grids of the given rottedGrids(initial rottedGrids) and recursively call the subtask to check the newly rottedGrids.
Use a counter to store the current number of fresh oranges.


## 997. Find the Town Judge
Find the vertex with N-1 indegree and 0 outdegree.
Attention to the edge case with one vertex and zero edge.


## 1046. Last Stone Weight
Max heap.


## 1049. Last Stone Weight II
DP.
The gist of the approach is to convert the original problem into the minimum difference between two groups of numbers.
If we can find a way to separate those stones into two piles, s1 and s2 are the sum of their weights, and get the minimum value of |s1-s2|,
we find the answer for the original problem as well.
In another words, we need to find a subsequence of stones with a sum of weights close to sum/2

sum = the weights of all stones
target = sum / 2
dp[i][j] means we can find a sum weight of j by select a number of stones from first i stones.
```
//base case
dp[i][0] = true     0 <= i <= stones.size()
dp[0][i] = false    1 <= i <= target

dp[i][j] = dp[i-1][j] || dp[i-1][j - stones[i-1]]   //if j < stones[i-1] return false

for i from [target, 0]
    if dp[stones.size()][i]  // i is the minimum difference
        return sum - 2 * i
```


## 1109. Corporate Flight Bookings
Diff array.
```
diffArr.size() = nums.size()
diffArr[0] = nums[0] // base case
diffArr[i] = nums[i] - nums[i-1]
nums    10  55  45  25  25
diffArr 10  45  -10 -20 0

Given diffArr, we can revert it back to nums
nums[0] = diffArr[0]    //base case
nums[i] = nums[i-1] + diffArr[i]

If we want add n to a range of numbers nums[i...j]
diffArr[i] += n
diffArr[j+1] -= n   // if j+1 is invalid, ignore it
```


## 1011. Capacity To Ship Packages Within D Days


## 1129. Shortest Path with Alternating Colors
BFS, but with two queues storing the neighbors connected with red or blue edges separately


## 1143. Longest Common Subsequence
DP.
dp[i][j] represents the longest common subsequence of text1[0...i-1] and text2[0...j-1]
```
//base case 
dp[i][0] = 0
dp[0][i] = 0

for i from [1, text1.size()]
    for j from [1, text2.size()]
        if text1[i-1] == text2[j-1] // add a new char to LCS
            dp[i][j] = dp[i-1][j-1] + 1
        else                        // at least one of text1[i-1] and text2[j-1] is not in LCS
            dp[i][j] = max(dp[i-1][j], dp[i][j-1])

return dp[text1.size()][text2.size()]
```
dp[i][j] can be compressed into dp[2][j] which only needs O(N) space.


## 1202. Smallest String with Swaps
1. DFS find connected vertices.
2. Sort the vertices, which are the indices, and the character separately.
3. Make the final swaps


## 1263. Minimum Moves to Move a Box to Their Target Location
DFS/BFS/A*.
1. Define the node state that includes box's position and player's position.
2. Use DFS or BFS to find a path from current player's position to the position where player do the next push.\
BFS is faster than DFS, since the target position is around the start position in most cases.
3. Use BFS to find a valid path from box's original position to the target position.\
We can also use A* to speed up the searching process.

Note that before step 2, we need to update the box's position.


## 1288. Remove Covered Intervals


## 1312. Minimum Insertion Steps to Make a String Palindrome
DP.
dp[i][j] represents the minimum insertion steps for s[i...j]
```
//base case
dp[i][i] = 0

for i from [s.size() - 2, 0]
    for j from [i + 1, s.size() - 1]
        if s[i] == s[j]
            dp[i][j] = dp[i+1][j-1]
        else
            dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1

return dp[0][s.size()-1]
```


## 1319. Number of Operations to Make Network Connected
Union find.\
circleCount represents the number of circle we find, which is the number of spare cables. \
disjointSetCount represents the number of disjoint sets after running union find. \
Therefore disjointSetCount-1 is the number of cables we need to use.


## 1351. Count Negative Numbers in a Sorted Matrix
Use binary search on the first num of all rows.
All the nums of the row that has a first negative num are negative.
Use binary search on each row that has a first non-negative num.

