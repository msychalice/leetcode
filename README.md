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


## 21. Merge Two Sorted Lists


## 25. Reverse Nodes in k-Group


## 26. Remove Duplicates from Sorted Array


## 27. Remove Element


## 28. Implement strStr()


## 34. Find First and Last Position of Element in Sorted Array
Use binary search to find the first and last index.
It's worth noting that we can use the first index as min to optimize the process of finding the last index.


## 35. Search Insert Position


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


## 51. N-Queens
This is a similar problem with 46Permutations which can be solved by backtracking.
The ith layer of the decision tree represents selected columns for ith row of the chessboard.
The way of checking two queens are in same diagonal is by checking abs(row1-row2) == abs(col1-col2)



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


## 66. Plus One


## 70. Climbing Stairs
```
f(1) = 1
f(2) = 2
f(n) = f(n-2) + f(n-1)
```


## 76. Minimum Window Substring
Sliding window.
1. Use start and len to store the valid minimum substring.
2. Use left and right to store the window index [left, right).
3. Move right index until the end of source string.
4. Move left index only when there is a valid substring found in the window.
4. Only update the start and len when moving left index.


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


## 90. Subsets II
We can use the similar algorithm to get all combinations in #78, but needs to check if the newly generated combination is duplicated.
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
Use the same algorithm in 121, except k is infinity.


## 123. Best Time to Buy and Sell Stock III
Use the same algorithm in 121, except 1 <= k <= 2.
We have to use 3 dimension dp, compression is not feasible.


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


## 188. Best Time to Buy and Sell Stock IV
Use the same algorithm in 121, except 1 <= k <= K.

Because every transaction needs days at least,
when k is greater or equal to prices.size()/2, we can treat k as infinity.
In such case, k == k - 1, and we can compress the dp to 2 dimension.
But when k is less than prices.size()/2, we can't apply this compression.


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


## 206. Reverse Linked List


## 213. House Robber II
DP.
The solution is similar to 198, but it needs to add a new state "firstrob/firstnotrob".
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


## 226. Invert Binary Tree


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


## 309. Best Time to Buy and Sell Stock with Cooldown
Use the same algorithm in 121, except k is infinity and has cooldown limit.
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


## 383. Ransom Note


## 389. Find the Difference


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


## 438. Find All Anagrams in a String
It's a similar problem to #567, except it needs to collect all the permutations.


## 480. Sliding Window Median
Use multiset in C++ to store the sliding window, which is a binary search tree.
The tricky is to maintain the iterator of the left mid, which is the median for a odd window and left median for an even window.

It is worth noting that inserting a value that is already existed in the multiset will add the new value *after* those existed values.
1 2 3 3 *3(new)* 4 4
However, using erase(lower_bound()) will remove the front of those existed values.
1 2 *3(removed)* 3 3 4 4


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


## 547. Friend Circles
Typical disjoint sets problem, use union find to solve it.
Use -1 as the initial root value for each node.
-2 means it's a root node and there are 2 nodes in the set.
We can utilize this to merge smaller sets into larger sets when performing union operation.
This will reduce overall cost of find operation.
We also use path compression in find operation.


## 567. Permutation in String
Sliding window.
Beware that the target is to find a substring not a subset, so any incontinuous candidate in window needs to be ruled out.


## 654. Maximum Binary Tree


## 714. Best Time to Buy and Sell Stock with Transaction Fee
Use the same algorithm in 121, except k is infinity and fee will be deducted from profit for each sell.


## 733. Flood Fill
1. Cache all reached grids
2. Use DFS to recursively traverse all the neighbor grids until the grid is either invalid, ,of wrong color, or reached. 


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


## 994. Rotting Oranges
Define subtask that checks all the neighbor grids of the given rottedGrids(initial rottedGrids) and recursively call the subtask to check the newly rottedGrids.
Use a counter to store the current number of fresh oranges.


## 1288. Remove Covered Intervals


## 1351. Count Negative Numbers in a Sorted Matrix
Use binary search on the first num of all rows.
All the nums of the row that has a first negative num are negative.
Use binary search on each row that has a first non-negative num.

