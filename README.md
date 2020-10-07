## 1. Two Sum

1.Build a hash table(key is the value of input array, value is the index of input array)\
2.Traverse the input array and use the hash table to search for the second number

## 3. Longest Substring Without Repeating Characters
1.Use headIndex and endIndex to indicate current substring\
2.Use hash table curSubstr to store all characters in current substring\
3.Increase endIndex by 1 until the end\
    >if s[endIndex] is in the hash table\
        >>duplicatedCharIndex = curSubstr[s[endIndex]]\
        >>remove all the elements from headIndex to duplicatedCharIndex in curSubstr\
        >>move headIndex to the right of the duplicated character (headIndex = duplicatedCharIndex + 1)\
    >else\
        >>add [s[endIndex]]endIndex to curSubstr\
\
    >if length of the current substring is longer than maxSubstrLen, update maxSubstrLen.Otherwise continue\




